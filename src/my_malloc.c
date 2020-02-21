/*
** EPITECH PROJECT, 2020
** malloc
** File description:
** my_malloc
*/

#include "my_malloc.h"

#define align4(x) (((((x)-1)>>2)<<2)+4)

mem_t *best_fit(size_t size)
{
    mem_t *current = head;
    size_t space = size + sizeof(mem_t);
    mem_t *result = NULL;

    while (current != NULL) {
        if (current->free && space <= current->size ) {
            if (result && current->size < result->size || !result) {
                result = current;
            }
        }
        current = current->next;
    }
    if (result)
        result = split(result, size);
    if (!result) {
        return NULL;
    }
    return (result);
}

void *__malloc__(size_t size)
{
    mem_t *res;
    if (size <= 0)
        return (NULL);
    size = align4(size);
    if (!head) {
        if (!create_head(size))
            return (NULL);
        split(head, size);
        return (head->address);
    }
    else {
        res = best_fit(size);
        if (!res) {
            res = create_node(size);
            if (!res)
                return (NULL);
            res = split(res, size);
        }
    }
    return (res->address);
}
