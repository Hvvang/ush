NAME = ush

INCD = inc
SRCD = src
OBJD = obj
LIBD = libmx

INC = inc/ush.h

LIB = libmx/libmx.a
INPUT = $(SRCD)/input/input.a
PARSER = $(SRCD)/parser/parser.a
BUILTINS = $(SRCD)/builtins/builtins.a

INPUT_INC = $(SRCD)/input/$(INCD)/mx_input.h
PARSER_INC = $(SRCD)/parser/$(INCD)/mx_parser.h
BUILTINS_INC = $(SRCD)/builtins/$(INCD)/mx_builtins.h

MODULES = $(INPUT) $(PARSER) $(BUILTINS) $(LIB)
INCLUDE = \
	-I $(INC) \
	-I $(INPUT) \
	-I $(PARSER) \
	-I $(BUILTINS) \


SRCS = $(wildcard $(SRCD)/*.c)
OBJS = $(addprefix $(OBJD)/, $(SRCS:src/%.c=%.o))

CFLAGS = -std=c11
# -Wall -Wextra -Werror -Wpedantic

all: $(NAME)

install: all clean

$(LIB):
	@make -sC $(LIBD)

modules:
	@make -sC $(LIBD)
	@make -sC src/input
	@make -sC src/parser
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
	@make -sC src/input $@
	@make -sC src/parser $@
	@make -sC src/builtins $@
	@rm -rf $(NAME)
	@printf "\e[34;1mProject $(NAME) deleted \e[0m\n"

clean:
	@rm -rf $(OBJD)
	@make -sC $(LIBD) $@
	@make -sC src/input $@
	@make -sC src/parser $@
	@make -sC src/builtins $@
	@printf "\e[34;1mdeleted object files in $(NAME)\e[0m\n"

reinstall: uninstall install
