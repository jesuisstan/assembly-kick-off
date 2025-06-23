#include "../inc/libasm.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

void test_write(const char *desc, int fd, const void *buf, size_t count, int is_valid) {
    ssize_t my = 0, std = 0;
    int saved_errno = 0;
    printf("--- %s ---\n", desc);
    if (is_valid) {
        errno = 0;
        my = ft_write(fd, buf, count);
        saved_errno = errno;
        errno = 0;
        std = write(fd, buf, count);
        printf("ft_write: %zd (errno: %d) | write: %zd (errno: %d) | %s\n",
               my, saved_errno, std, errno, (my == std && saved_errno == errno ? "OK" : "FAIL"));
    } else {
        errno = 0;
        my = ft_write(fd, buf, count);
        saved_errno = errno;
        printf("ft_write: %zd (errno: %d) | (expected: -1, errno set; standard write would segfault or error)\n", my, saved_errno);
    }
    printf("-----------------------------\n");
}

int main(void) {
    test_write("Write to stdout", 1, "Hello\n", 6, 1);
    test_write("Write to stderr", 2, "Error\n", 6, 1);
    test_write("Write empty string", 1, "", 0, 1);
    test_write("Write partial string", 1, "Partial", 4, 1);
    test_write("Write to invalid fd", -1, "Bad fd\n", 7, 0); // standard write would set errno
    test_write("Write to closed fd", 100, "Closed\n", 7, 0); // likely error
    //test_write("Write with NULL buf", 1, NULL, 5, 0); // standard write would segfault or set errno
    //test_write("Write with NULL buf and zero count", 1, NULL, 0, 0); // standard write may not segfault, but UB
    return 0;
}