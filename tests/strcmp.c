#include "../inc/libasm.h"
#include <stdio.h>
#include <string.h>

void test_strcmp(const char *desc, const char *s1, const char *s2, int is_valid) {
    int my = 0, std = 0;
    if (is_valid) {
        my = ft_strcmp(s1, s2);
        std = strcmp(s1, s2);
        printf("%s | s1: '%s' | s2: '%s' | ft_strcmp: %d | strcmp: %d | %s\n", desc, s1, s2, my, std, ((my == 0 && std == 0) || (my < 0 && std < 0) || (my > 0 && std > 0)) ? "OK" : "FAIL");
    } else {
        my = ft_strcmp(s1, s2);
        printf("%s | s1: %s | s2: %s | ft_strcmp: %d | (expected: 0, no crash; standard strcmp would segfault or cause UB)\n", desc, s1 ? "not NULL" : "NULL", s2 ? "not NULL" : "NULL", my);
    }
}

int main(void) {
    printf("\n====================\n");
    printf("TESTING FT_STRCMP\n");
    printf("====================\n\n");
    test_strcmp("Both empty", "", "", 1);
    test_strcmp("Equal short", "42", "42", 1);
    test_strcmp("Equal long", "Hello, world!", "Hello, world!", 1);
    test_strcmp("Diff at start", "abc", "xbc", 1); // 'a' (ASCII 97) vs 'x' (ASCII 120)
    test_strcmp("Diff at end", "abc", "abd", 1); // 'c' (ASCII 99) vs 'd' (ASCII 100)
    test_strcmp("s1 < s2", "abc", "bcd", 1);
    test_strcmp("s1 > s2", "bcd", "abc", 1);
    test_strcmp("s1 empty, s2 not", "", "abc", 1);
    test_strcmp("s1 not empty, s2 empty", "abc", "", 1);
    // The following two tests would cause segfault or undefined behavior in standard strcmp
    test_strcmp("NULL s1", NULL, "test", 0); // standard strcmp would segfault or cause UB
    test_strcmp("NULL s2", "test", NULL, 0); // standard strcmp would segfault or cause UB
    return 0;
} 