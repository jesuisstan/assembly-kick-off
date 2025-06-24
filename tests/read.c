#include "../inc/libasm.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

void test_read_stdin(void) {
    char buf1[32] = {0}, buf2[32] = {0};
    printf("--- Read from stdin (type something and press Enter) ---\n");
    printf("For correct comparison, please enter the SAME input twice (once for ft_read, once for read):\n");
    printf("Input for ft_read: ");
    fflush(stdout);
    errno = 0;
    ssize_t my = ft_read(0, buf1, 31);
    int my_errno = errno;
    printf("Input for read:    ");
    fflush(stdout);
    errno = 0;
    ssize_t std = read(0, buf2, 31);
    int std_errno = errno;
    printf("ft_read: %zd (errno: %d) | read: %zd (errno: %d)\n", my, my_errno, std, std_errno);
    printf("ft_read buf: '%s'\nread buf:    '%s'\n", buf1, buf2);
    printf("-----------------------------\n\n");
}

void test_read_file(void) {
    printf("--- Read from file ---\n");
    int fd1 = open("README.md", O_RDONLY);
    int fd2 = open("README.md", O_RDONLY);
    if (fd1 < 0 || fd2 < 0) {
        printf("File 'README.md' not found. Please add it to the test directory.\n");
        printf("-----------------------------\n");
        if (fd1 >= 0) close(fd1);
        if (fd2 >= 0) close(fd2);
        return;
    }
    char buf1[64] = {0}, buf2[64] = {0};
    errno = 0;
    ssize_t my = ft_read(fd1, buf1, 42);
    int my_errno = errno;
    errno = 0;
    ssize_t std = read(fd2, buf2, 42);
    int std_errno = errno;
    close(fd1);
    close(fd2);
    printf("ft_read: %zd (errno: %d) | read: %zd (errno: %d)\n", my, my_errno, std, std_errno);
    printf("ft_read buf: '%s'\nread buf:    '%s'\n", buf1, buf2);
    printf("-----------------------------\n\n");
}

void test_read_invalid_fd(void) {
    char buf1[32] = {0}, buf2[32] = {0};
    printf("--- Read from invalid fd ---\n");
    errno = 0;
    ssize_t my = ft_read(-1, buf1, 10);
    int my_errno = errno;
    errno = 0;
    ssize_t std = read(-1, buf2, 10);
    int std_errno = errno;
    printf("ft_read: %zd (errno: %d) | read: %zd (errno: %d)\n", my, my_errno, std, std_errno);
    printf("-----------------------------\n\n");
}

void test_read_null_buf(void) {
    printf("--- Read with NULL buf ---\n");
    errno = 0;
    ssize_t my = ft_read(0, NULL, 10);
    int my_errno = errno;
    printf("ft_read: %zd (errno: %d) | (expected: -1, errno=EFAULT; standard read would segfault or UB)\n", my, my_errno);
    printf("-----------------------------\n\n");
}

void test_read_zero_bytes(void) {
    char buf1[32] = {0}, buf2[32] = {0};
    printf("--- Read zero bytes ---\n");
    errno = 0;
    ssize_t my = ft_read(0, buf1, 0);
    int my_errno = errno;
    errno = 0;
    ssize_t std = read(0, buf2, 0);
    int std_errno = errno;
    printf("ft_read: %zd (errno: %d) | read: %zd (errno: %d)\n", my, my_errno, std, std_errno);
    printf("ft_read buf: '%s'\nread buf:    '%s'\n", buf1, buf2);
    printf("-----------------------------\n");
}

int main(void) {
    test_read_stdin();
    test_read_file();
    test_read_invalid_fd();
    test_read_null_buf();
    test_read_zero_bytes();
    return 0;
} 