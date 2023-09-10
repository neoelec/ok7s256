#ifndef __SLL_H__
#define __SLL_H__

#include <stddef.h>
#include <stdlib.h>

struct sll_head {
    struct sll_head *next;
};

#define sll_to_entry(ptr, type, member) \
    ((type *)(((char *)ptr) - offsetof(type, member)))

extern void sll_init(struct sll_head *head);
extern void sll_append(struct sll_head *head, struct sll_head *node);
extern void sll_insert(struct sll_head *curr, struct sll_head *node);
extern void sll_delete(struct sll_head *head, struct sll_head *node);

#endif /* __SLL_H__ */
