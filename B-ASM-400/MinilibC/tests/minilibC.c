/*
** EPITECH PROJECT, 2024
** minilibC
** File description:
** minilibC
*/

#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Test(minilibC, strlen)
{
    int (*fptr)(char *str);
    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    fptr = dlsym(handle, "strlen");
    cr_assert_eq(fptr(""), 0);
    cr_assert_eq(fptr("a"), 1);
    cr_assert_eq(fptr("Hello, world!"), 13);
    cr_assert_eq(fptr("    \t\n"), 6);
    cr_assert_eq(fptr("1234567890"), 10);
    dlclose(handle);
}

Test(minilibC, strchr)
{
    char *(*fptr)(char *str, int c);
    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    fptr = dlsym(handle, "strchr");
    char *test = fptr("", 0);
    cr_assert_str_eq(test, "");
    char *test1 = fptr("test", 't');
    cr_assert_str_eq(test1, "test");
    char *test2 = fptr("    \t\n", 'a');
    cr_assert_null(test2);
    char *test3 = fptr("hello world", 'w');
    cr_assert_str_eq(test3, "world");
    dlclose(handle);
}

Test(minilibC, strrchr)
{
    char *(*fptr)(char *str, int c);
    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    fptr = dlsym(handle, "strrchr");
    char *test = fptr("", 0);
    cr_assert_str_eq(test, "");
    char *test1 = fptr("test", 't');
    cr_assert_str_eq(test1, "t");
    char *test2 = fptr("    \t\n", 'a');
    cr_assert_null(test2);
    char *test3 = fptr("hello world", 'w');
    cr_assert_str_eq(test3, "world");
    dlclose(handle);
}

Test(minilibC, index)
{
    char *(*fptr)(char *str, int c);
    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    fptr = dlsym(handle, "index");
    char *test = fptr("", 0);
    cr_assert_str_eq(test, "");
    char *test1 = fptr("test", 't');
    cr_assert_str_eq(test1, "test");
    char *test2 = fptr("    \t\n", 'a');
    cr_assert_null(test2);
    char *test3 = fptr("hello world", 'w');
    cr_assert_str_eq(test3, "world");
    dlclose(handle);
}

Test(minilibC, rindex)
{
    char *(*fptr)(char *str, int c);
    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    fptr = dlsym(handle, "rindex");
    char *test = fptr("", 0);
    cr_assert_str_eq(test, "");
    char *test1 = fptr("test", 't');
    cr_assert_str_eq(test1, "t");
    char *test2 = fptr("    \t\n", 'a');
    cr_assert_null(test2);
    char *test3 = fptr("hello world", 'w');
    cr_assert_str_eq(test3, "world");
    dlclose(handle);
}

Test(minilibC, strcmp)
{
    int (*fptr)(const char *str1, const char *str2);
    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    fptr = dlsym(handle, "strcmp");
    
    int result = fptr("hello", "hello");
    cr_assert_eq(result, 0);
    result = fptr("hello", "world");
    cr_assert_lt(result, 0);
    result = fptr("", "");
    cr_assert_eq(result, 0);
    result = fptr("", "hello");
    cr_assert_lt(result, 0);
    result = fptr("hello", "");
    cr_assert_gt(result, 0);
    dlclose(handle);
}

Test(minilibC, strncmp)
{
    int (*fptr)(const char *str1, const char *str2, size_t n);
    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    fptr = dlsym(handle, "strncmp");

    int result = fptr("hello", "hello", 5);
    cr_assert_eq(result, 0);
    result = fptr("hello", "world", 5);
    cr_assert_lt(result, 0);
    result = fptr("", "", 0);
    cr_assert_eq(result, 0);
    result = fptr("", "hello", 1);
    cr_assert_lt(result, 0);
    result = fptr("hello", "", 1);
    cr_assert_gt(result, 0);
    result = fptr("hello", "hel", 3);
    cr_assert_eq(result, 0);
    result = fptr("hello", "helx", 3);
    cr_assert_eq(result, 0);
    dlclose(handle);
}

Test(minilibC, strcspn)
{
    size_t (*fptr)(const char *str1, const char *str2);
    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    fptr = dlsym(handle, "strcspn");

    size_t result = fptr("", "world");
    cr_assert_eq(result, 0);
    result = fptr("hello", "");
    cr_assert_eq(result, 5);
    result = fptr("", "");
    cr_assert_eq(result, 0);
    result = fptr("hello", "aeiou");
    cr_assert_eq(result, 1);
    dlclose(handle);
}

Test(minilibC, strpbrk)
{
    char *(*fptr)(const char *str1, const char *str2);
    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    fptr = dlsym(handle, "strpbrk");

    char *result = fptr("hello", "world");
    cr_assert_str_eq(result, "llo");
    result = fptr("", "world");
    cr_assert_null(result);
    result = fptr("hello", "");
    cr_assert_null(result);
    result = fptr("", "");
    cr_assert_null(result);
    result = fptr("hello", "aeiou");
    cr_assert_str_eq(result, "ello");
    dlclose(handle);
}

Test(minilibC, strstr)
{
    char *(*fptr)(const char *str1, const char *str2);
    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    fptr = dlsym(handle, "strstr");
    
    char *result = fptr("hello world", "world");
    cr_assert_str_eq(result, "world");
    result = fptr("", "world");
    cr_assert_null(result);
    result = fptr("hello world", "");
    cr_assert_str_eq(result, "hello world");
    result = fptr("", "");
    cr_assert_str_eq(result, "");
    result = fptr("hello world", "notfound");
    cr_assert_null(result);

    dlclose(handle);
}

Test(minilibC, strcasecmp)
{
    int (*fptr)(const char *str1, const char *str2);
    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    fptr = dlsym(handle, "strcasecmp");

    int result = fptr("hello", "HELLO");
    cr_assert_eq(result, 0);
    result = fptr("hello", "hello world");
    cr_assert_lt(result, 0);
    result = fptr("", "hello");
    cr_assert_lt(result, 0);
    result = fptr("", "");
    cr_assert_eq(result, 0);
    result = fptr("hello", "world");
    cr_assert_lt(result, 0);

    dlclose(handle);
}

Test(minilibC, memset)
{
    void *(*fptr)(void *ptr, int value, size_t num);
    void *handle = dlopen("./libasm.so", RTLD_LAZY);
    fptr = dlsym(handle, "memset");

    char str[6] = "hello";
    char *result = fptr(str, 'a', 3);
    cr_assert_str_eq(result, "aaalo");
    result = fptr(str, 0, 2);
    cr_assert_str_eq(result, "\0\0alo");
    char empty[1] = "";
    result = fptr(empty, 'a', 1);
    cr_assert_str_eq(result, "a");
    dlclose(handle);
}
