NAME = ush

INC = ush.h

INCI = inc/ush.h

INCLIB = libmx/libmx.a

LIBMXF = libmx

PARSER = \
mx_get_commands.c \
mx_check_input.c \
mx_set_literal.c \
mx_get_literal.c \
mx_skip_literal.c \
mx_split_to_struct.c \
mx_list_to_arr.c \
mx_split_commands.c \
mx_check_subs_lvls.c \

BUILTIN = \
mx_error_handle.c \
mx_builtin_usage.c \
mx_valid_cd.c \
mx_valid_pwd.c \
mx_check_flags.c \
mx_pwd.c \
mx_cd.c \
mx_builtin_func.c \
\

SRC = \
main.c \
mx_ush_loop.c \
mx_ush_read_line.c \
mx_str_arr_size.c \
mx_launch_process.c \
mx_get_array_size.c \
mx_env.c \
mx_export.c \
mx_unset.c \
mx_env_create.c \
mx_check_flag.c \
mx_exp_change_dublicate.c \
mx_exp_add_argv.c \
\
mx_get_type.c \
\


SRCS = $(addprefix src/, $(SRC))
PARSERS = $(addprefix src/parser/, $(PARSER))
BUILTINS = $(addprefix src/builtins/, $(BUILTIN))

OBJSRC = $(SRC:%.c=%.o)
OBJPARSER = $(PARSER:%.c=%.o)
OBJBUILTIN = $(BUILTIN:%.c=%.o)

CFLAGS = -std=c11
# -Wall -Wextra -Werror -Wpedantic

all: install

install:
	@make -C libmx
	@cp $(SRCS) .
	@cp $(PARSERS) .
	@cp $(BUILTINS) .
	@cp $(INCI) .
	@clang $(CFLAGS) -c $(SRC) $(PARSER) $(BUILTIN) -I $(INC)
	@clang $(CFLAGS) -g $(OBJSRC) $(OBJPARSER) $(OBJBUILTIN) $(INCLIB) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJSRC) $(OBJPARSER) $(OBJBUILTIN) ./obj

uninstall: clean
	@make uninstall -C $(LIBMXF)
	@rm -rf $(NAME)

app:
	@cp $(SRCS) .
	@cp $(PARSERS) .
	@cp $(BUILTINS) .
	@cp $(INCI) .
	@clang $(CFLAGS) -c $(SRC) $(PARSER) $(BUILTIN) -I $(INC)
	@clang $(CFLAGS) -g $(OBJSRC) $(OBJPARSER) $(OBJBUILTIN) $(INCLIB) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJSRC) $(OBJPARSER) $(OBJBUILTIN) ./obj
	@make clean

clean:
	@make clean -C $(LIBMXF)
	@rm -rf $(SRC) $(PARSER) $(BUILTIN) $(OBJSRC) $(OBJPARSER) $(OBJBUILTIN) $(INC)
	@rm -rf ./obj

reinstall: uninstall install
