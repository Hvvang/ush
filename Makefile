NAME = ush

INCD = inc
SRCD = src
OBJD = obj
LIBD = libmx

INC = inc

LIB = libmx/libmx.a
INPUT = $(SRCD)/input/input.a
PARSER = $(SRCD)/parser/parser.a
BUILTINS = $(SRCD)/builtins/builtins.a
HISTORY = $(SRCD)/history/history.a
EXEC = $(SRCD)/exec/exec.a
SHELL_PREF = $(SRCD)/shell/shell.a

MODULES = $(INPUT) $(EXEC) $(SHELL_PREF) $(HISTORY) $(PARSER) $(BUILTINS) $(LIB)
INCLUDE = \
	-I $(INC) \
	-I $(EXEC) \
	-I $(HISTORY) \
	-I $(INPUT) \
	-I $(PARSER) \
	-I $(BUILTINS) \


SRCS = $(wildcard $(SRCD)/*.c)
OBJS = $(addprefix $(OBJD)/, $(SRCS:src/%.c=%.o))

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: $(NAME)

install: all clean

modules:
	@make -sC $(LIBD)
	@make -sC src/history
	@make -sC src/input
	@make -sC src/parser
	@make -sC src/exec
	@make -sC src/shell
	@make -sC src/builtins

$(NAME): modules $(OBJS)
	@clang $(CFLAGS) $(OBJS) $(MODULES) -o $@
	@printf "\e[32;1mProject $@ created\e[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INC)
	@clang $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@printf "\e[32mcompiled: \e[0m[$(<:$(SRCD)/%.c=%.c)]\n"

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

uninstall: clean
	@make -sC $(LIBD) $@
	@make -sC src/builtins $@
	@make -sC src/exec $@
	@make -sC src/history $@
	@make -sC src/input $@
	@make -sC src/parser $@
	@make -sC src/shell $@
	@rm -rf $(NAME)
	@printf "\e[34;1mProject $(NAME) deleted \e[0m\n"

clean:
	@rm -rf $(OBJD)
	@make -sC $(LIBD) $@
	@make -sC src/builtins $@
	@make -sC src/exec $@
	@make -sC src/history $@
	@make -sC src/input $@
	@make -sC src/parser $@
	@make -sC src/shell $@
	@printf "\e[34;1mdeleted object files in $(NAME)\e[0m\n"

reinstall: uninstall install
