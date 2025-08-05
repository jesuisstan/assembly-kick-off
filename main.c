#include "inc/libasm.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

// ==================== FT_STRLEN TESTS ====================
void test_strlen_comprehensive(void) {
    printf("=== FT_STRLEN COMPREHENSIVE TESTS ===\n\n");
    
    printf("Empty string: ft_strlen(\"\") = %zu (expected: 0)\n", ft_strlen(""));
    printf("Very long string: ft_strlen(\"A very very long string just to check the boundaries and see if everything works fine.\") = %zu\n", 
           ft_strlen("A very very long string just to check the boundaries and see if everything works fine."));
    
    printf("Short string: ft_strlen(\"42\") = %zu | strlen: %zu | %s\n", 
           ft_strlen("42"), strlen("42"), ft_strlen("42") == strlen("42") ? "OK" : "FAIL");
    printf("Hello world: ft_strlen(\"Hello, world!\") = %zu | strlen: %zu | %s\n", 
           ft_strlen("Hello, world!"), strlen("Hello, world!"), ft_strlen("Hello, world!") == strlen("Hello, world!") ? "OK" : "FAIL");
    printf("String with null in middle: ft_strlen(\"abc\\0def\") = %zu | strlen: %zu | %s\n", 
           ft_strlen("abc\0def"), strlen("abc\0def"), ft_strlen("abc\0def") == strlen("abc\0def") ? "OK" : "FAIL");
    printf("Single char: ft_strlen(\"A\") = %zu | strlen: %zu | %s\n", 
           ft_strlen("A"), strlen("A"), ft_strlen("A") == strlen("A") ? "OK" : "FAIL");
    printf("Whitespace: ft_strlen(\"   \") = %zu | strlen: %zu | %s\n", 
           ft_strlen("   "), strlen("   "), ft_strlen("   ") == strlen("   ") ? "OK" : "FAIL");
    printf("Non-ASCII: ft_strlen(\"💩\") = %zu | strlen: %zu | %s\n", 
           ft_strlen("💩"), strlen("💩"), ft_strlen("💩") == strlen("💩") ? "OK" : "FAIL");
    printf("NULL pointer: ft_strlen(NULL) = %zu (expected: 0, no crash)\n", ft_strlen(NULL));
    printf("\n");
}

// ==================== FT_STRCPY TESTS ====================
void test_strcpy_comprehensive(void) {
    printf("=== FT_STRCPY COMPREHENSIVE TESTS ===\n\n");
    
    char dst[128];
    
    ft_strcpy(dst, "");
    printf("Empty string: ft_strcpy(dst, \"\") = \"%s\" | strcpy: \"%s\" | %s\n", 
           dst, strcpy(dst, ""), strcmp(dst, "") == 0 ? "OK" : "FAIL");
    
    ft_strcpy(dst, "A very very long string just to check the boundaries and see if everything works fine.");
    printf("Very long string: ft_strcpy(dst, long_string) = \"%s\" | %s\n", 
           dst, strcmp(dst, "A very very long string just to check the boundaries and see if everything works fine.") == 0 ? "OK" : "FAIL");
    
    char buf1[128] = {0}, buf2[128] = {0};
    
    ft_strcpy(buf1, "42");
    strcpy(buf2, "42");
    printf("Short string: ft_strcpy = \"%s\" | strcpy = \"%s\" | %s\n", 
           buf1, buf2, strcmp(buf1, buf2) == 0 ? "OK" : "FAIL");
    
    ft_strcpy(buf1, "Hello, world!");
    strcpy(buf2, "Hello, world!");
    printf("Normal string: ft_strcpy = \"%s\" | strcpy = \"%s\" | %s\n", 
           buf1, buf2, strcmp(buf1, buf2) == 0 ? "OK" : "FAIL");
    
    ft_strcpy(buf1, "abc\0def");
    strcpy(buf2, "abc\0def");
    printf("String with null: ft_strcpy = \"%s\" | strcpy = \"%s\" | %s\n", 
           buf1, buf2, strcmp(buf1, buf2) == 0 ? "OK" : "FAIL");
    
    ft_strcpy(buf1, "A");
    strcpy(buf2, "A");
    printf("Single char: ft_strcpy = \"%s\" | strcpy = \"%s\" | %s\n", 
           buf1, buf2, strcmp(buf1, buf2) == 0 ? "OK" : "FAIL");
    
    ft_strcpy(buf1, "   ");
    strcpy(buf2, "   ");
    printf("Whitespace: ft_strcpy = \"%s\" | strcpy = \"%s\" | %s\n", 
           buf1, buf2, strcmp(buf1, buf2) == 0 ? "OK" : "FAIL");
    
    ft_strcpy(buf1, "💩");
    strcpy(buf2, "💩");
    printf("Non-ASCII: ft_strcpy = \"%s\" | strcpy = \"%s\" | %s\n", 
           buf1, buf2, strcmp(buf1, buf2) == 0 ? "OK" : "FAIL");
    
    printf("NULL src: ft_strcpy(dst, NULL) = %s (expected: NULL, no crash)\n", 
           ft_strcpy(dst, NULL) ? "not NULL" : "NULL");
    printf("NULL dst: ft_strcpy(NULL, src) = %s (expected: NULL, no crash)\n", 
           ft_strcpy(NULL, "test") ? "not NULL" : "NULL");
    printf("\n");
}

// ==================== FT_STRCMP TESTS ====================
void test_strcmp_comprehensive(void) {
    printf("=== FT_STRCMP COMPREHENSIVE TESTS ===\n\n");
    
    printf("2 empty strings: ft_strcmp(\"\", \"\") = %d | strcmp = %d | %s\n", 
           ft_strcmp("", ""), strcmp("", ""), ft_strcmp("", "") == strcmp("", "") ? "OK" : "FAIL");
    printf("1 empty string as first: ft_strcmp(\"\", \"abc\") = %d | strcmp = %d | %s\n", 
           ft_strcmp("", "abc"), strcmp("", "abc"), (ft_strcmp("", "abc") < 0 && strcmp("", "abc") < 0) ? "OK" : "FAIL");
    printf("1 empty string as second: ft_strcmp(\"abc\", \"\") = %d | strcmp = %d | %s\n", 
           ft_strcmp("abc", ""), strcmp("abc", ""), (ft_strcmp("abc", "") > 0 && strcmp("abc", "") > 0) ? "OK" : "FAIL");
    
    printf("Multiple strings, equal: ft_strcmp(\"abc\", \"abc\") = %d | strcmp = %d | %s\n", 
           ft_strcmp("abc", "abc"), strcmp("abc", "abc"), ft_strcmp("abc", "abc") == strcmp("abc", "abc") ? "OK" : "FAIL");
    printf("Multiple strings, s1 < s2: ft_strcmp(\"abc\", \"bcd\") = %d | strcmp = %d | %s\n", 
           ft_strcmp("abc", "bcd"), strcmp("abc", "bcd"), (ft_strcmp("abc", "bcd") < 0 && strcmp("abc", "bcd") < 0) ? "OK" : "FAIL");
    printf("Multiple strings, s1 > s2: ft_strcmp(\"bcd\", \"abc\") = %d | strcmp = %d | %s\n", 
           ft_strcmp("bcd", "abc"), strcmp("bcd", "abc"), (ft_strcmp("bcd", "abc") > 0 && strcmp("bcd", "abc") > 0) ? "OK" : "FAIL");
    
    printf("Diff at start: ft_strcmp(\"abc\", \"xbc\") = %d | strcmp = %d | %s\n", 
           ft_strcmp("abc", "xbc"), strcmp("abc", "xbc"), (ft_strcmp("abc", "xbc") < 0 && strcmp("abc", "xbc") < 0) ? "OK" : "FAIL");
    printf("Diff at end: ft_strcmp(\"abc\", \"abd\") = %d | strcmp = %d | %s\n", 
           ft_strcmp("abc", "abd"), strcmp("abc", "abd"), (ft_strcmp("abc", "abd") < 0 && strcmp("abc", "abd") < 0) ? "OK" : "FAIL");
    
    printf("NULL s1: ft_strcmp(NULL, \"test\") = %d (expected: 0, no crash)\n", ft_strcmp(NULL, "test"));
    printf("NULL s2: ft_strcmp(\"test\", NULL) = %d (expected: 0, no crash)\n", ft_strcmp("test", NULL));
    printf("\n");
}

// ==================== FT_WRITE TESTS ====================
void test_write_comprehensive(void) {
    printf("=== FT_WRITE COMPREHENSIVE TESTS ===\n\n");
    
    errno = 0;

    ssize_t my_stdout = ft_write(1, "write test\n", 11);
    int my_errno = errno;
    errno = 0;
    ssize_t std_stdout = write(1, "write test\n", 11);
    int std_errno = errno;
    printf("Write to stdout: ft_write = %zd (errno: %d) | write = %zd (errno: %d) | %s\n", 
           my_stdout, my_errno, std_stdout, std_errno, (my_stdout == std_stdout) ? "OK" : "FAIL");
    
    int fd = open("write_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd != -1) {
        errno = 0;
        ssize_t my_file = ft_write(fd, "Test content\n", 13);
        my_errno = errno;
        errno = 0;
        ssize_t std_file = write(fd, "Test content\n", 13);
        std_errno = errno;
        close(fd);
        printf("Write to file: ft_write = %zd (errno: %d) | write = %zd (errno: %d) | %s\n", 
               my_file, my_errno, std_file, std_errno, (my_file == std_file) ? "OK" : "FAIL");
    }
    
    errno = 0;
    ssize_t my_bad = ft_write(-1, "Bad fd test\n", 12);
    my_errno = errno;
    printf("Write to wrong fd: ft_write = %zd (errno: %d) (expected: -1, errno set)\n", my_bad, my_errno);
    
    errno = 0;
    ssize_t my_stderr = ft_write(2, "error test\n", 11);
    my_errno = errno;
    errno = 0;
    ssize_t std_stderr = write(2, "error test\n", 11);
    std_errno = errno;
    printf("Write to stderr: ft_write = %zd (errno: %d) | write = %zd (errno: %d) | %s\n", 
           my_stderr, my_errno, std_stderr, std_errno, (my_stderr == std_stderr) ? "OK" : "FAIL");
    
    errno = 0;
    ssize_t my_empty = ft_write(1, "", 0);
    my_errno = errno;
    errno = 0;
    ssize_t std_empty = write(1, "", 0);
    std_errno = errno;
    printf("Write empty string: ft_write = %zd (errno: %d) | write = %zd (errno: %d) | %s\n", 
           my_empty, my_errno, std_empty, std_errno, (my_empty == std_empty) ? "OK" : "FAIL");
    
    errno = 0;
    ssize_t my_partial = ft_write(1, "partial", 7);
    my_errno = errno;
    errno = 0;
    ssize_t std_partial = write(1, "partial", 7);
    std_errno = errno;
    printf("Write partial string: ft_write = %zd (errno: %d) | write = %zd (errno: %d) | %s\n", 
           my_partial, my_errno, std_partial, std_errno, (my_partial == std_partial) ? "OK" : "FAIL");
    
    errno = 0;
    ssize_t my_closed = ft_write(100, "Closed fd test\n", 15);
    my_errno = errno;
    printf("Write to closed fd: ft_write = %zd (errno: %d) (expected: -1, errno set)\n", my_closed, my_errno);
    printf("\n");
}

// ==================== FT_READ TESTS ====================
void test_read_comprehensive(void) {
    printf("=== FT_READ COMPREHENSIVE TESTS ===\n\n");
    
    // check ft_read from stdin
    printf("ft_read-ing from stdin (type something and press Enter):\n");
    printf("Input for ft_read: ");
    fflush(stdout);
    char buf1[32] = {0};
    errno = 0;
    ssize_t my_stdin = ft_read(0, buf1, 31);
    int my_errno = errno;
    printf("ft_read from stdin: %zd (errno: %d)\n", my_stdin, my_errno);
    printf("--------------------------------\n");
    // check std::read from stdin
    printf("std::read-ing from stdin (type the same input as above and press Enter):\n");
    printf("Input for std::read: ");
    fflush(stdout);
    char buf_std[32] = {0};
    errno = 0;
    ssize_t stdin = read(0, buf_std, 31);
    int std_errno = errno;
    printf("std::read from stdin: %zd (errno: %d)\n", stdin, std_errno);
    
    int fd = open("read_test.txt", O_RDONLY);
    if (fd != -1) {
        char buf2[64] = {0};
        errno = 0;
        ssize_t my_file = ft_read(fd, buf2, 60);
        my_errno = errno;
        close(fd);
        printf("Read from file: ft_read = %zd (errno: %d) | First 60 chars: %s\n", my_file, my_errno, buf2);
    }
    
    errno = 0;
    ssize_t my_bad = ft_read(-1, buf1, 10);
    my_errno = errno;
    printf("Read from wrong fd: ft_read = %zd (errno: %d) (expected: -1, errno set)\n", my_bad, my_errno);
    
    errno = 0;
    ssize_t my_null = ft_read(0, NULL, 10);
    my_errno = errno;
    printf("Read with NULL buf: ft_read = %zd (errno: %d) (expected: -1, errno=EFAULT)\n", my_null, my_errno);
    
    errno = 0;
    ssize_t my_zero = ft_read(0, buf1, 0);
    my_errno = errno;
    printf("Read zero bytes: ft_read = %zd (errno: %d) (expected: 0)\n", my_zero, my_errno);
    printf("\n");
}

// ==================== FT_STRDUP TESTS ====================
void test_strdup_comprehensive(void) {
    printf("=== FT_STRDUP COMPREHENSIVE TESTS ===\n\n");
    
    char *my_empty = ft_strdup("");
    char *std_empty = strdup("");
    printf("Empty string: ft_strdup(\"\") = \"%s\" | strdup = \"%s\" | %s\n", 
           my_empty, std_empty, strcmp(my_empty, std_empty) == 0 ? "OK" : "FAIL");
    free(my_empty);
    free(std_empty);
    
    char *my_long = ft_strdup("A very very long string just to check the boundaries and see if everything works fine.");
    char *std_long = strdup("A very very long string just to check the boundaries and see if everything works fine.");
    printf("Very long string: ft_strdup = \"%s\" | strdup = \"%s\" | %s\n", 
           my_long, std_long, strcmp(my_long, std_long) == 0 ? "OK" : "FAIL");
    free(my_long);
    free(std_long);
    
    char *my_short = ft_strdup("42");
    char *std_short = strdup("42");
    printf("Short string: ft_strdup = \"%s\" | strdup = \"%s\" | %s\n", 
           my_short, std_short, strcmp(my_short, std_short) == 0 ? "OK" : "FAIL");
    free(my_short);
    free(std_short);
    
    char *my_normal = ft_strdup("Hello, world!");
    char *std_normal = strdup("Hello, world!");
    printf("Normal string: ft_strdup = \"%s\" | strdup = \"%s\" | %s\n", 
           my_normal, std_normal, strcmp(my_normal, std_normal) == 0 ? "OK" : "FAIL");
    free(my_normal);
    free(std_normal);
    
    char *my_unicode = ft_strdup("💩");
    char *std_unicode = strdup("💩");
    printf("Non-ASCII string: ft_strdup = \"%s\" | strdup = \"%s\" | %s\n", 
           my_unicode, std_unicode, strcmp(my_unicode, std_unicode) == 0 ? "OK" : "FAIL");
    free(my_unicode);
    free(std_unicode);
    
    char *my_null = ft_strdup(NULL);
    printf("NULL input: ft_strdup(NULL) = %s (expected: NULL, no crash)\n", my_null ? "not NULL" : "NULL");
    if (my_null) free(my_null);
    printf("\n");
}

// ==================== MAIN FUNCTION ====================
int main(void) {
    printf("libasm Library Comprehensive Testing\n");
    printf("====================================\n\n");
    
    test_strlen_comprehensive();
    test_strcpy_comprehensive();
    test_strcmp_comprehensive();
    test_write_comprehensive();
    test_read_comprehensive();
    test_strdup_comprehensive();
    
    printf("All comprehensive tests completed!\n");
    printf("Check the output above for any FAIL results.\n");
    return 0;
}
