#include "../inc/libasm.h"
#include <stdio.h>
#include <string.h>

void test_strcpy(const char *desc, char *dst, const char *src, int is_valid) {
    char buf1[128] = {0};
    char buf2[128] = {0};
    char *my = NULL;
    if (is_valid) {
        if (dst) buf1[0] = '\0';
        if (dst && src) {
            char *std = NULL;
            my = ft_strcpy(buf1, src);
            std = strcpy(buf2, src);
            printf("%s | src: '%s' | ft_strcpy: '%s' | strcpy: '%s' | %s\n", desc, src, buf1, buf2, (strcmp(buf1, buf2) == 0 && my == buf1 && std == buf2 ? "OK" : "FAIL"));
        }
    } else {
        my = ft_strcpy(dst, src);
        printf("%s | src: %s | dst: %s | ft_strcpy: %s | (expected: NULL, no crash; standard strcpy would segfault or cause UB)\n", desc, src ? "not NULL" : "NULL", dst ? "not NULL" : "NULL", my ? "not NULL" : "NULL");
    }
}

int main(void) {
    char buf[128];
    test_strcpy("Copy empty string", buf, "", 1);
    test_strcpy("Copy short string", buf, "42", 1);
    test_strcpy("Copy normal string", buf, "Hello, world!", 1);
    test_strcpy("Copy with null in middle", buf, "abc\0def", 1);
    test_strcpy("Copy long string", buf, "A very very long string just to check the boundaries and see if everything works fine.", 1);
    test_strcpy("Copy single char", buf, "A", 1);
    test_strcpy("Copy whitespace", buf, "   ", 1);
    test_strcpy("Copy non-ASCII", buf, "\xF0\x9F\x92\xA9", 1);
    test_strcpy("NULL src", buf, NULL, 0);
    test_strcpy("NULL dst", NULL, "test", 0);
    return 0;
} 