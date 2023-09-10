#include <board.h>
/* - */
#include <errno.h>
#include <pio/pio.h>
#include <pio/pio_it.h>

#include "delay.h"
#include "key.h"
#include "tick.h"

#define DEBOUNCE_TIME 250

static const Pin pinsBp[] = { PINS_PUSHBUTTONS };

static const unsigned int numBp = PIO_LISTSIZE(pinsBp);
static unsigned int lastPress[PIO_LISTSIZE(pinsBp)];
static unsigned int active;
static struct sll_head head;

static int __ISR_GetBpNum(const Pin * pin, unsigned int *number)
{
    unsigned int i;

    if ((!!PIO_Get(pin) != active))
        return -ENXIO;

    for (i = 0; i < numBp; i++) {
        if (pin == &pinsBp[i]) {
            *number = i;
            return 0;
        }
    }

    return -ENOENT;
}

static void __ISR_CallNotifiers(unsigned int number)
{
    unsigned int timestamp = TICK_GetTimestamp();
    struct sll_head *node;
    KeyNotifier *kn;

    if ((timestamp - lastPress[number]) <= DEBOUNCE_TIME)
        return;

    lastPress[number] = timestamp;

    node = head.next;
    while (node) {
        kn = sll_to_entry(node, KeyNotifier, node);
        kn->func(kn, number);
        node = node->next;
    }
}

static void ISR_Bp(const Pin * pin)
{
    unsigned int number;
    int err;

    err = __ISR_GetBpNum(pin, &number);
    if (err < 0)
        return;

    __ISR_CallNotifiers(number);
}

void KEY_Configure(unsigned activeValue)
{
    PIO_Configure(pinsBp, numBp);

    active = activeValue;
}

void KEY_ConfigureIt(unsigned activeValue)
{
    unsigned int i;

    KEY_Configure(activeValue);

    PIO_InitializeInterrupts(AT91C_AIC_PRIOR_LOWEST);

    for (i = 0; i < numBp; i++)
        PIO_ConfigureIt(&pinsBp[i], ISR_Bp);

    for (i = 0; i < numBp; i++)
        PIO_EnableIt(&pinsBp[i]);
}

static unsigned int __input(void)
{                                              /* input key KEY2 - KEY1 without debouncing */
    unsigned int keycode = 0;                  //   (no input = 0, KEY1 = 1, KEY2 = 2)
    unsigned int i;

    for (i = 0; i < numBp; i++) {
        if ((!!PIO_Get(&pinsBp[i])) == active)
            keycode |= 1 << i;
    }

    return keycode;
}

unsigned int KEY_Input(void)
{                                              /* input key KEY2 - KEY1 with debouncing */
    static unsigned char flag;
    unsigned int key;                          //   (no input = 0, KEY1 = 1, KEY2 = 2)

    key = __input();                           // any key pressed ?
    if (key == 0) {                            // if no key, check key off
        if (flag == 0)
            return key;
        else {
            DELAY_ms(20);
            flag = 0;
            return key;
        }
    } else {                                   // if key input, check continuous key
        if (flag != 0)                         // if continuous key, treat as no key input
            return 0;
        else {                                 // if new key, beep and delay for debounce
            flag = 1;
            return key;
        }
    }
}

void KEY_RegisterNotifier(KeyNotifier * kn)
{
    sll_append(&head, &kn->node);
}

void KEY_UnregisterNotifier(KeyNotifier * kn)
{
    sll_delete(&head, &kn->node);
}
