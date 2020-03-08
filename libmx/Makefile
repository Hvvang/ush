NAME = libmx.a

INC = libmx.h

INCI = inc/libmx.h

SRC = \
mx_binary_search.c \
mx_memmove.c \
mx_sqrt.c \
mx_bubble_sort.c \
mx_memrchr.c \
mx_str_reverse.c \
mx_count_substr.c \
mx_memset.c \
mx_strcat.c \
mx_count_words.c \
mx_nbr_to_hex.c \
mx_create_node.c \
mx_pop_back.c \
mx_strcmp.c \
mx_del_extra_spaces.c \
mx_pop_front.c \
mx_strcpy.c \
mx_del_strarr.c \
mx_pow.c \
mx_strdel.c \
mx_file_to_str.c \
mx_print_strarr.c \
mx_strdup.c \
mx_foreach.c \
mx_print_unicode.c \
mx_strjoin.c \
mx_get_char_index.c \
mx_printchar.c \
mx_strlen.c \
mx_get_substr_index.c \
mx_strncmp.c \
mx_hex_to_nbr.c \
mx_printint.c \
mx_strncpy.c \
mx_printstr.c \
mx_strndup.c \
mx_itoa.c \
mx_push_back.c \
mx_strnew.c \
mx_list_size.c \
mx_push_front.c \
mx_strsplit.c \
mx_memccpy.c \
mx_quicksort.c \
mx_strstr.c \
mx_memchr.c \
mx_read_line.c \
mx_strtrim.c \
mx_memcmp.c \
mx_realloc.c \
mx_swap_char.c \
mx_memcpy.c \
mx_replace_substr.c \
mx_memmem.c \
mx_sort_list.c \
mx_calc_num.c \
mx_isspace.c \
mx_strchr.c \
mx_strjoin_no_leaks.c \
mx_strchr_index.c \
mx_add_buff_to_static.c \
mx_atoi.c \
mx_del_list.c \

SRCS = $(addprefix src/, $(SRC))
OBJ = $(SRC:%.c=%.o)

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@cp $(SRCS) .
	@cp $(INCI) .
	@clang $(CFLAGS) -c $(SRC) -I $(INC)
	@ar crs $(NAME) $(OBJ)
	@mkdir -p obj
	@mv $(OBJ) ./obj
uninstall: clean
	@rm -rf $(NAME)
clean:
	@rm -rf $(SRC) $(INC)
	@rm -rf ./obj
reinstall: uninstall install
