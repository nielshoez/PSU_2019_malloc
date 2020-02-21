/*
** EPITECH PROJECT, 2020
** tests
** File description:
** unit_tests
*/

#include "my_malloc.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/time.h>
#include <sys/resource.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_stdout()
{
    cr_redirect_stdout();
}

Test(my_malloc, basic_malloc)
{
    char *test = my_malloc(12);

    cr_assert_neq(test, NULL);
    test = strcpy(test, "test");
    cr_assert_str_eq(test, "test");
}

Test(calloc, basic_calloc)
{
    char *test = my_calloc(5, sizeof(char));

    cr_assert_neq(test, NULL);
    cr_assert_str_eq(test, "\0\0\0\0\0");
    test = strcpy(test, "test");
    cr_assert_str_eq(test, "test");
}

Test(realloc, basic_realloc, .init=redirect_stdout)
{
    char *test = my_malloc(5);

    cr_assert_neq(test, NULL);
    test = strcpy(test, "test");
    cr_assert_str_eq(test, "test");
    test = my_realloc(test, 20);
    test = strcat(test, "issou");
    cr_assert_str_eq(test, "testissou");
    write(1, test, strlen(test));
    cr_assert_stdout_eq_str("testissou");
}

Test(malloc, mutliple_malloc)
{
    char **test_array = my_malloc(sizeof(char *) * 5);

    cr_assert_neq(test_array, NULL);
    for (int i = 0; i < 4; i++)
        test_array[i] = my_malloc(20);
    for (int i = 0; i < 4; i++)
        cr_assert_neq(test_array[i], NULL);
    for (int i = 0; i < 4; i++) {
        test_array[i] = strcpy(test_array[i], "test123");
        cr_assert_str_eq(test_array[i], "test123");
        my_free(test_array[i]);
    }
    my_free(test_array);
}

Test(malloc, big_boi_malloc)
{
    int **test = my_malloc(sizeof(int *) * 1000);
    cr_assert_neq(test, NULL);
    for (int i = 0; i < 1000; i++) {
        test[i] = my_malloc(sizeof(int) * 200);
        cr_assert_neq(test[i], NULL);
        for (int y = 0; y < 200; y++) {
            test[i][y] = y;
        }
    }
    for (int i = 0; i < 1000; i++) {
        for (int y = 0; y < 200; y++) {
            cr_assert_eq(test[i][y], y);
        }
    }
}

Test(malloc, very_big_boi_malloc_calloc_etc_issou, .init=redirect_stdout)
{
    char **lopes = my_malloc(20 * sizeof(char *));
    size_t size = 30;

    cr_assert_neq(lopes, NULL);
    for (int i = 0; i < 20; i++, size += 10) {
        lopes[i] = my_calloc(size, sizeof(char));
        cr_assert_neq(lopes[i], NULL);
        lopes[i] = strcpy(lopes[i], "ceci est un test");
        cr_assert_str_eq(lopes[i], "ceci est un test");
    }
    lopes = my_realloc(lopes, sizeof(char *) * 40);
    for (int i = 0; i < 20; i++, size += 10) {
        cr_assert_str_eq(lopes[i], "ceci est un test");
    }
    for (int i = 20; i < 40; i++, size += 10) {
        lopes[i] = my_calloc(size, sizeof(char));
        cr_assert_neq(lopes[i], NULL);
        lopes[i] = strcpy(lopes[i], "ceci est un test");
        cr_assert_str_eq(lopes[i], "ceci est un test");
    }
    for (int i = 0; i < 40; i++) {
        cr_assert_str_eq(lopes[i], "ceci est un test");
    }
}

Test(malloc, fat_test_long)
{
    int **wtf = malloc(sizeof(int *) * 2000);
    int rdm;

    for (int i = 0; i < 2000; i++) {
        wtf[i] = malloc(sizeof(int) * 999);
        for (int j = 0; j < 999; j++) {
            rdm = rand();
            wtf[i][j] = rdm;
            cr_assert_eq(wtf[i][j], rdm);
        }
    }
}

Test(realloc, basic_under_realloc, .init=redirect_stdout)
{
    char *test = my_malloc(10);

    cr_assert_neq(test, NULL);
    test = strcpy(test, "testissou");
    cr_assert_str_eq(test, "testissou");
    test = my_realloc(test, 4);
    cr_assert_str_eq(test, "test");
}

Test(malloc, fail_malloc)
{
    char *test;
    struct rlimit limit;

    getrlimit(RLIMIT_DATA, &limit);
    limit.rlim_cur = 0;
    limit.rlim_max = 0;
    setrlimit(RLIMIT_DATA, &limit);
    test = my_malloc(12);
    cr_assert_eq(test, NULL);
}

Test(reallocarray, simple_reallocarray)
{
    int **test_array = my_malloc(sizeof(int *) * 3);
    const int magic = 0x42069;

    cr_assert_neq(test_array, NULL);
    for (int i = 0; i < 3; i++) {
        test_array[i] = my_calloc(20, sizeof(int));
        cr_assert_neq(test_array[i], NULL);
        for (int y = 0; y < 20; y++) {
            test_array[i][y] = magic;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int y = 0; y < 20; y++) {
            cr_assert_eq(test_array[i][y], magic);
        }
    }
    test_array = my_reallocarray(test_array, 6, sizeof(int *));
    cr_assert_neq(test_array, NULL);
    for (int i = 3; i < 6; i++) {
        test_array[i] = my_calloc(20, sizeof(int));
        cr_assert_neq(test_array[i], NULL);
        for (int y = 0; y < 20; y++) {
            test_array[i][y] = magic;
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int y = 0; y < 20; y++) {
            cr_assert_eq(test_array[i][y], magic);
        }
    }
}

Test(reallocarray, reallocarray_overflow)
{
    int **test_array = my_malloc(sizeof(int *) * 10);

    cr_assert_neq(test_array, NULL);
    test_array = my_reallocarray(test_array, 5000000000, 5000000000);
    cr_assert_eq(test_array, NULL);
}

Test(malloc, fail_calloc)
{
    char *test;
    struct rlimit limit;

    getrlimit(RLIMIT_DATA, &limit);
    limit.rlim_cur = 0;
    limit.rlim_max = 0;
    setrlimit(RLIMIT_DATA, &limit);
    test = my_calloc(1, 12);
    cr_assert_eq(test, NULL);
}

Test(malloc, wrong_size)
{
    char *test = my_malloc((size_t)NULL);
    cr_assert_eq(test, NULL);
}

Test(realloc, null_realloc)
{
    char *test = my_realloc(NULL, 3);

    cr_assert_neq(test, NULL);

    test = strcpy(test, "AB");
    cr_assert_str_eq(test, "AB");
}