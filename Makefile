NAME = ush

INC = ush.h

INCI = inc/ush.h

INCLIB = libmx/libmx.a

LIBMXF = libmx

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
mx_parser.c \
\
mx_isWord.c \
mx_isPipe.c \
mx_isNewLine.c \
mx_isGreat.c \
mx_isLess.c \
mx_isGreatGreat.c \
mx_isGreatAmpersand.c \
mx_isAmpersand.c \


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

clean:
	@make clean -C $(LIBMXF)
	@rm -rf $(SRC) $(OBJ) $(INC)
	@rm -rf ./obj

reinstall: uninstall install
