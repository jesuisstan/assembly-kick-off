NAME = libasm.a
CC = gcc
NASM = nasm
NASMFLAGS = -f elf64 -DPIC
CFLAGS = -Wall -Wextra -Werror
SRCS = src/ft_strlen.s src/ft_strcpy.s src/ft_strcmp.s src/ft_write.s src/ft_read.s src/ft_strdup.s
SRCS_BONUS = src/bonus/ft_atoi_base.s src/bonus/ft_list_push_front.s src/bonus/ft_list_size.s src/bonus/ft_list_sort.s src/bonus/ft_list_remove_if.s
OBJS = $(SRCS:.s=.o)
OBJS_BONUS = $(SRCS_BONUS:.s=.o)
INCLUDES = -Iinc

all: $(NAME)

bonus: $(NAME) $(OBJS_BONUS)
	@if [ ! -f $(NAME) ] || [ src/bonus/ft_atoi_base.o -nt $(NAME) ] || [ src/bonus/ft_list_push_front.o -nt $(NAME) ] || [ src/bonus/ft_list_size.o -nt $(NAME) ] || [ src/bonus/ft_list_sort.o -nt $(NAME) ] || [ src/bonus/ft_list_remove_if.o -nt $(NAME) ]; then \
		ar rcs $(NAME) $(OBJS_BONUS); \
	else \
		echo "$(NAME) is up to date"; \
	fi

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

src/bonus/%.o: src/bonus/%.s
	$(NASM) $(NASMFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) test_program test_program_bonus write_test.txt

re: fclean all

# ==================== TEST PROGRAMS ====================
test_program: main.c $(NAME)
	@if [ ! -f test_program ] || [ main.c -nt test_program ] || [ $(NAME) -nt test_program ]; then \
		$(CC) $(CFLAGS) $< -L. -lasm $(INCLUDES) -o $@; \
	else \
		echo "test_program is up to date"; \
	fi

test_program_bonus: main_bonus.c $(NAME) $(OBJS_BONUS)
	@if [ ! -f test_program_bonus ] || [ main_bonus.c -nt test_program_bonus ] || [ $(NAME) -nt test_program_bonus ]; then \
		ar rcs $(NAME) $(OBJS_BONUS); \
		$(CC) $(CFLAGS) $< -L. -lasm $(INCLUDES) -o $@; \
	else \
		echo "test_program_bonus is up to date"; \
	fi

.PHONY: all bonus clean fclean re test_program test_program_bonus