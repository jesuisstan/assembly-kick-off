#include "../inc/libasm.h"
#include <stdio.h>
#include <string.h>

void test_strlen(const char *desc, const char *s, int is_valid) {
    size_t my = 0, std = 0;
    if (is_valid) {
        my = ft_strlen(s);
        std = strlen(s);
        printf("%s | Input: '%s' | ft_strlen: %zu | strlen: %zu | %s\n", desc, s, my, std, (my == std ? "OK" : "FAIL"));
    } else {
        my = ft_strlen(s);
        printf("%s | Input: %s | ft_strlen: %zu | (expected: 0, standard strlen would segfault)\n", desc, s == NULL ? "NULL" : "uninitialized pointer", my);
    }
}

int main(void) {
    printf("\n====================\n");
    printf("TESTING FT_STRLEN\n");
    printf("====================\n\n");
    test_strlen("Empty string", "", 1);
    test_strlen("Short string", "42", 1);
    test_strlen("Hello world", "Hello, world!", 1);
    test_strlen("String with null in middle", "abc\0def", 1);
    test_strlen("Long string", "A very very long string just to check the boundaries and see if everything works fine.", 1);
    test_strlen("Single char", "A", 1);
    test_strlen("Whitespace", "   ", 1);
    test_strlen("Non-ASCII", "\xF0\x9F\x92\xA9", 1);
    test_strlen("NULL pointer (UB)", NULL, 0);
    return 0;
}