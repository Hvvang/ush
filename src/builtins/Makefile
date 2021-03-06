NAME = builtins
MODULE = $(NAME).a

SRCD = src
OBJD = obj
INCD = inc

INC_PATH = inc/mx_builtins.h

LIB_PATH = ../../libmx/libmx.a
EXEC_PATH = ../exec/exec.a
PARSER_PATH = ../parser/parser.a
SHELL_PATH = ../shell/shell.a

INCLUDE = \
	-I $(LIB_PATH) \
	-I $(SHELL_PATH) \
	-I $(PARSER_PATH) \
	-I $(EXEC_PATH) \
	-I $(INCD) \

SRCS = $(wildcard $(SRCD)/*.c)
OBJS = $(addprefix $(OBJD)/, $(SRCS:src/%.c=%.o))

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: $(NAME)

$(NAME): $(OBJS)
	@ar crs $(MODULE) $(OBJS)
	@printf "\e[32;1m$@ module created\e[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INC_PATH) ../exec/inc/mx_exec.h
	@clang $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@printf "\e[32mcompiled: \e[0m[$(<:$(SRCD)/%.c=%.c)]\n"

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

install: all clean

uninstall: clean
	@rm -rf $(MODULE)
	@printf "\e[34;1mdeleted $(NAME) module\e[0m\n"

clean:
	@rm -rf $(OBJD)
	@printf "\e[34;1mdeleted object files in $(NAME)\e[0m\n"

reinstall: uninstall install
