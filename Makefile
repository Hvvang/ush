NAME = ush

INCD = inc
SRCD = src
OBJD = obj

INC = $(wildcard $(INCD)/*.h)


LIB = libmx/libmx.a
INPUT = $(SRCD)/input/input.a
PARSER = $(SRCD)/parser/parser.a
BUILTINS = $(SRCD)/builtins/builtins.a

INPUT_INC = $(SRCD)/input/$(INCD)/mx_input.h
PARSER_INC = $(SRCD)/parser/$(INCD)/mx_parser.h
BUILTINS_INC = $(SRCD)/builtins/$(INCD)/mx_builtins.h

MODULES = $(LIB) $(INPUT) $(PARSER) $(BUILTINS)
INCLUDE = \
	-I $(INCD) \
	-I $(LIB) \
	-I $(INPUT) \
	-I $(PARSER) \
	-I $(BUILTINS) \


SRCS = $(wildcard $(SRCD)/*.c)
OBJS = $(SRCS:src/%.c=%.o)

CFLAGS = -std=c11
# -Wall -Wextra -Werror -Wpedantic

all: $(NAME)

$(NAME): $(OBJS)
	@clang $(CFLAGS) $(MODULES) $(OBJS) -o $@
	@printf "\e[32;1m$@ created\e[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INC)
	@clang $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@printf "\e[32mcompiled: \e[0m[$(<:$(SRCD)/%.c=%.c)]\n"

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

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
	@cp $(INPUTS) .
	@cp $(INCI) .
	@clang $(CFLAGS) -c $(SRC) $(PARSER) $(INPUT) $(BUILTIN) -I $(INC)
	@clang $(CFLAGS) -g $(OBJSRC) $(OBJPARSER) $(OBJINPUT) $(OBJBUILTIN) $(INCLIB) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJSRC) $(OBJPARSER) $(OBJINPUT) $(OBJBUILTIN) ./obj
	@make clean

clean:
	@make clean -C $(LIBMXF)
	@rm -rf $(SRC) $(PARSER) $(BUILTIN) $(OBJSRC) $(OBJPARSER) $(OBJBUILTIN) $(INC)
	@rm -rf ./obj

reinstall: uninstall install
