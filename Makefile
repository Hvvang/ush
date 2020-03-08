NAME = ush

INC = ush.h

INCI = inc/ush.h

INCLIB = libmx/libmx.a

LIBMXF = libmx

SRC = \
main.c \
mx_ush_loop.c \
mx_ush_read_line.c \
mx_launch_process.c \
mx_print_pwd.c \
mx_change_dir.c \
mx_get_array_size.c \
mx_builtin_func.c \
mx_chage_dir_and_pwd.c \
mx_chage_link_dir_pwd.c \
<<<<<<< HEAD
mx_env.c \
mx_export.c \
mx_unset.c \
=======
>>>>>>> fc9844dab0ba4ff53020527d03755d6729e482e5
\
mx_str_arr_size.c \
mx_get_commands.c \
mx_check_input.c \
mx_set_literal.c \
mx_get_literal.c \
mx_skip_literal.c \
mx_split_to_struct.c \
mx_list_to_arr.c \
mx_split_commands.c \

SRCS = $(addprefix src/, $(SRC))

OBJ = $(SRC:%.c=%.o)

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install

install:
	@make -C libmx
	@cp $(SRCS) .
	@cp $(INCI) .
	@clang $(CFLAGS) -c $(SRC) -I $(INC)
	@clang $(CFLAGS) $(INCLIB) $(OBJ) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJ) ./obj

uninstall: clean
	@make uninstall -C $(LIBMXF)
	@rm -rf $(NAME)

app:
	@cp $(SRCS) .
	@cp $(INCI) .
	@clang $(CFLAGS) -c $(SRC) -I $(INC)
	@clang $(CFLAGS) $(INCLIB) $(OBJ) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJ) ./obj
	@make clean

clean:
	@make clean -C $(LIBMXF)
	@rm -rf $(SRC) $(OBJ) $(INC)
	@rm -rf ./obj

reinstall: uninstall install
