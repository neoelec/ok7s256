#include <stdlib.h>
#include <sys/types.h>

#include "sll.h"

void sll_init(struct sll_head *head)
{
    head->next = NULL;
}

void sll_append(struct sll_head *head, struct sll_head *node)
{
    struct sll_head *prev = head;
    struct sll_head *next = head->next;

    while (next) {
        struct sll_head *tmp = prev;
        prev = next;
        next = tmp->next;
    }

    prev->next = node;
}

void sll_insert(struct sll_head *curr, struct sll_head *node)
{
    node->next = curr->next;
    curr->next = node;
}

void sll_delete(struct sll_head *head, struct sll_head *node)
{
    struct sll_head *curr = head;

    while ((curr != NULL) && (curr->next != node))
        curr = curr->next;

    if (curr != NULL)
        curr->next = node->next;
}
