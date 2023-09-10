#ifndef __KEY_H__
#define __KEY_H__

#include "sll.h"

#define KEY_ACTIVE_HIGH 1
#define KEY_ACTIVE_LOW 0

typedef struct __KeyNotifier {
    struct sll_head node;
    void (*func)(struct __KeyNotifier *, unsigned int);
} KeyNotifier;

extern void KEY_Configure(unsigned activeValue);
extern void KEY_ConfigureIt(unsigned activeValue);
extern unsigned int KEY_Input(void);           /* input key KEY2 - KEY1 with debouncing */
extern void KEY_RegisterNotifier(KeyNotifier * kn);
extern void KEY_UnregisterNotifier(KeyNotifier * kn);

#endif /* __KEY_H__ */
