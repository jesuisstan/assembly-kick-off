#include "../inc/libasm.h"
#include "../inc/libasm_bonus.h"
#include <stdio.h>

void test_atoi_base(const char *desc, char *str, char *base, int expected) {
    printf("--- %s ---\n", desc);
    int my = ft_atoi_base(str, base);
    printf("Input: str=\"%s\", base=\"%s\"\n", str, base);
    printf("ft_atoi_base: %d | expected: %d | %s\n", my, expected, (my == expected ? "OK" : "FAIL"));
    printf("-----------------------------\n\n");
}

int main(void) {
    printf("\n====================\n");
    printf("TESTING FT_ATOI_BASE\n");
    printf("====================\n\n");
    test_atoi_base("Base 2", "101010", "01", 42);
    test_atoi_base("Base 10", "-42", "0123456789", -42);
    test_atoi_base("Base 16", "2A", "0123456789abcdef", 42);
    test_atoi_base("Invalid base (size < 2)", "10", "0", 0);
    test_atoi_base("Invalid base (duplicates)", "10", "010", 0);
    test_atoi_base("Base 314 (invalid)", "10", "0123456789....", 0);
    return 0;
} 