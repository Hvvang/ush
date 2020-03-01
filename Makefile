NAME = ush

INC = ush.h

INCI = inc/ush.h

INCLIB = libmx/libmx.a

SRC = \
main.c \
mx_ush_loop.c \
mx_ush_read_line.c \
mx_split_argv.c \
mx_launch_process.c \
mx_check_flag.c \
mx_print_pwd.c \
mx_change_dir.c \
mx_get_array_size.c \
mx_builtin_func.c \

SRCS = $(addprefix src/, $(SRC))

OBJ = $(SRC:%.c=%.o)

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@make -C libmx
	@cp $(SRCS) .
	@cp $(INCI) .
	@clang $(CFLAGS) -c $(SRC) -I $(INC)
	@clang $(CFLAGS) $(INCLIB) $(OBJ) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJ) ./obj

uninstall: clean
	@rm -rf $(NAME) $(INCLIB)

clean:
	@rm -rf $(SRC) $(OBJ) $(INC)
	@rm -rf ./obj

reinstall: uninstall install
