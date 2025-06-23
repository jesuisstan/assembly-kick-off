NAME = libasm.a
CC = gcc
NASM = nasm
CFLAGS = -Wall -Wextra -Werror
SRCS = src/ft_strlen.s src/ft_strcpy.s src/ft_strcmp.s src/ft_write.s src/ft_read.s src/ft_strdup.s
OBJS = $(SRCS:.s=.o)
INCLUDES = -Iinc

# The -no-pie flag is used ONLY for test binaries, not for the library itself.
# This is required to link NASM objects with modern GCC (see: https://stackoverflow.com/a/57421917)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.s
	$(NASM) -f elf64 $< -o $@

test_strlen: $(NAME) test/strlen.c
	$(CC) $(CFLAGS) -no-pie test/strlen.c -L. -lasm $(INCLUDES) -o $@

test_strcpy: $(NAME) test/strcpy.c
	$(CC) $(CFLAGS) -no-pie test/strcpy.c -L. -lasm $(INCLUDES) -o $@

test_strcmp: $(NAME) test/strcmp.c
	$(CC) $(CFLAGS) -no-pie test/strcmp.c -L. -lasm $(INCLUDES) -o $@

test_write: $(NAME) test/write.c
	$(CC) $(CFLAGS) -no-pie test/write.c -L. -lasm $(INCLUDES) -o $@

test_read: $(NAME) test/read.c
	$(CC) $(CFLAGS) -no-pie test/read.c -L. -lasm $(INCLUDES) -o $@

test_strdup: $(NAME) test/strdup.c
	$(CC) $(CFLAGS) -no-pie test/strdup.c -L. -lasm $(INCLUDES) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) test_strlen test_strcpy test_strcmp test_write test_read test_strdup

re: fclean all

.PHONY: all clean fclean re test_strlen test_strcpy test_strcmp test_write test_read test_strdup
