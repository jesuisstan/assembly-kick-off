#include "../inc/libasm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void test_strdup(const char *desc, const char *src, int is_valid) {
    char *my = NULL;
    char *std = NULL;
    printf("--- %s ---\n", desc);
    if (is_valid) {
        my = ft_strdup(src);
        std = strdup(src);
        printf("src: '%s'\nft_strdup: '%s'\nstrdup:    '%s'\n", src, my, std);
        if (my && std && strcmp(my, std) == 0)
            printf("Result: OK\n");
        else
            printf("Result: FAIL\n");
        if (my) free(my);
        if (std) free(std);
    } else {
        my = ft_strdup(src);
        printf("src: %s\nft_strdup: %s | (expected: NULL, no crash; standard strdup would segfault or UB)\n", src ? "not NULL" : "NULL", my ? "not NULL" : "NULL");
        if (my) free(my);
    }
    printf("-----------------------------\n\n");
}

int main(void) {
    printf("\n====================\n");
    printf("TESTING FT_STRDUP\n");
    printf("====================\n\n");
    test_strdup("Empty string", "", 1);
    test_strdup("Short string", "42", 1);
    test_strdup("Long string", "A very very long string just to check the boundaries and see if everything works fine.", 1);
    test_strdup("NULL input", NULL, 0);
    test_strdup("Non-ASCII string", "\xF0\x9F\x92\xA9", 1);
    return 0;
} 