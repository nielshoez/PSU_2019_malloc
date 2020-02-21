/*
** EPITECH PROJECT, 2020
** complement
** File description:
** complement
*/

#include "my_malloc.h"
#include <string.h>
#include <stdlib.h>


mem_t *find(void *ptr);

void *__calloc__(size_t nmemb, size_t size)
{
    void *res = __malloc__(size * nmemb);

    if (res == NULL)
        return (NULL);
    res = memset(res, 0, size * nmemb);
    return (res);
}

void *__realloc__(void *ptr , size_t  size)
{
    void *res = __malloc__(size + 1);
    mem_t *tmp = find(ptr);

    if (res == NULL) {
        return (NULL);
    }
    if (tmp == NULL || head == NULL) {
        return res;
    }
    if (tmp->size > size) {
        res = memset(res, 0, size + 1);
        res = memmove(res, ptr, size);
    }
    else
        res = memmove(res, ptr, tmp->size);
    __free__(ptr);
    __free__(tmp);
    return (res);
}

mem_t *find(void *ptr)
{
    mem_t *current = head;

    for (; current && current->address != ptr; current = current->next);
    return (current);
}

void __free__(void *ptr)
{
    mem_t *current = head;

    while (current) {
        if (current->address == ptr) {
            current->free = true;
            return;
        }
        current = current->next;
    }
}

void *__reallocarray__(void *ptr , size_t  nmemb , size_t  size)
{
    return (__realloc__(ptr, nmemb * size));
}
