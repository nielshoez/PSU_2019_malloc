/*
** EPITECH PROJECT, 2020
** my_malloc
** File description:
** my_malloc
*/

#ifndef MY_MALLOC_H_
#define MY_MALLOC_H_
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>


#ifdef DEBUG
    #define __malloc__ my_malloc
#else
    #define __malloc__ malloc
#endif

#ifdef DEBUG
    #define __calloc__ my_calloc
#else
    #define __calloc__ calloc
#endif

#ifdef DEBUG
    #define __realloc__ my_realloc
#else
    #define __realloc__ realloc
#endif

#ifdef DEBUG
    #define __free__ my_free
#else
    #define __free__ free
#endif

#ifdef DEBUG
    #define __reallocarray__ my_reallocarray
#else
    #define __reallocarray__ reallocarray
#endif

typedef struct mem_s
{
    size_t size;
    struct mem_s *next;
    bool free;
    void *address;
} mem_t;

mem_t *head;
void *__malloc__(size_t size);
int my_printf(const char *str, ...);
void  __free__(void *ptr);
void *__calloc__(size_t  nmemb , size_t  size);
void *__realloc__(void *ptr , size_t  size);
void *__reallocarray__(void *ptr , size_t  nmemb , size_t  size);
mem_t *create_node(size_t size);
struct mem_t *init();
void *split(mem_t *current, size_t size);
mem_t *create_head(size_t size);
void dump_heap();

void put_n(unsigned long long nbr);

#endif /* !MY_MALLOC_H_ */
