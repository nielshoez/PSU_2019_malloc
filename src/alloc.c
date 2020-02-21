/*
** EPITECH PROJECT, 2020
** alloc
** File description:
** alloc
*/

#include "my_malloc.h"

mem_t *create_head(size_t size)
{
    size += sizeof(mem_t);
    size_t space = (size - 1) / (2 * getpagesize()) * (2 * getpagesize())
        + (2 * getpagesize());

    head = sbrk(space);
    if (head == (void *) -1)
        return (NULL);
    head->free = true;
    head->size = space - sizeof(mem_t);
    head->next = NULL;
    head->address = (void *)head + sizeof(mem_t);
    return (head);
}

mem_t *create_node(size_t size)
{
    mem_t *current = head;
    size += sizeof(mem_t);
    long int space = (size - 1) / (2 * getpagesize()) * (2 * getpagesize())
        + (2 * getpagesize());

    while (current != NULL && current->next != NULL)
        current = current->next;
    if (sbrk(space) == (void *) -1)
        return (NULL);
    current->size += space;
    return (current);
}

void *split(mem_t *current, size_t size)
{
    mem_t *new;

    new = (void *)current->address + size;
    new->size = current->size - size - sizeof(mem_t);
    new->next = current->next;
    new->address = (void *)new + sizeof(mem_t);
    new->free = true;
    current->free = false;
    current->size = size;
    current->next = new;

    return (current);
}
