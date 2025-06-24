NAME = libasm.a
CC = gcc
NASM = nasm
CFLAGS = -Wall -Wextra -Werror
SRCS = src/ft_strlen.s src/ft_strcpy.s src/ft_strcmp.s src/ft_write.s src/ft_read.s src/ft_strdup.s
SRCS_BONUS = src/bonus/ft_atoi_base.s src/bonus/ft_list_push_front.s src/bonus/ft_list_size.s src/bonus/ft_list_sort.s src/bonus/ft_list_remove_if.s
OBJS = $(SRCS:.s=.o)
OBJS_BONUS = $(SRCS_BONUS:.s=.o)
INCLUDES = -Iinc

# The -no-pie flag is used ONLY for test binaries, not for the library itself.
# This is required to link NASM objects with modern GCC (see: https://stackoverflow.com/a/57421917)

all: $(NAME)

bonus: $(NAME) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.s
	$(NASM) -f elf64 $< -o $@

src/bonus/%.o: src/bonus/%.s
	$(NASM) -f elf64 $< -o $@

test_strlen: $(NAME)
	$(CC) $(CFLAGS) -no-pie tests/strlen.c -L. -lasm $(INCLUDES) -o test_strlen

test_strcpy: $(NAME)
	$(CC) $(CFLAGS) -no-pie tests/strcpy.c -L. -lasm $(INCLUDES) -o test_strcpy

test_strcmp: $(NAME)
	$(CC) $(CFLAGS) -no-pie tests/strcmp.c -L. -lasm $(INCLUDES) -o test_strcmp

test_write: $(NAME)
	$(CC) $(CFLAGS) -no-pie tests/write.c -L. -lasm $(INCLUDES) -o test_write

test_read: $(NAME)
	$(CC) $(CFLAGS) -no-pie tests/read.c -L. -lasm $(INCLUDES) -o test_read

test_strdup: $(NAME)
	$(CC) $(CFLAGS) -no-pie tests/strdup.c -L. -lasm $(INCLUDES) -o test_strdup

test_atoi_base: bonus
	$(CC) $(CFLAGS) -no-pie tests/bonus/ft_atoi_base_test.c -L. -lasm $(INCLUDES) -o test_atoi_base

test_list_push_front: bonus
	$(CC) $(CFLAGS) -no-pie tests/bonus/ft_list_push_front_test.c -L. -lasm $(INCLUDES) -o test_list_push_front

test_list_size: bonus
	$(CC) $(CFLAGS) -no-pie tests/bonus/ft_list_size_test.c -L. -lasm $(INCLUDES) -o test_list_size

test_list_sort: bonus
	$(CC) $(CFLAGS) -no-pie tests/bonus/ft_list_sort_test.c -L. -lasm $(INCLUDES) -o test_list_sort

test_list_remove_if: bonus
	$(CC) $(CFLAGS) -no-pie tests/bonus/ft_list_remove_if_test.c -L. -lasm $(INCLUDES) -o test_list_remove_if

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) test_strlen test_strcpy test_strcmp test_write test_read test_strdup test_atoi_base test_list_push_front test_list_size test_list_sort test_list_remove_if

re: fclean all

.PHONY: all bonus clean fclean re test_strlen test_strcpy test_strcmp test_write test_read test_strdup test_atoi_base test_list_push_front test_list_size test_list_sort test_list_remove_if
