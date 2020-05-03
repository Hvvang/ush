NAME = parser
MODULE = $(NAME).a

SRCD = src
OBJD = obj
INCD = inc

INC_POSIX = ../../inc/mx_posix.h
INC_PATH = inc/mx_parser.h

LIB_PATH = ../../libmx/libmx.a

INCLUDE = \
	-I $(LIB_PATH) \
	-I $(INCD) \
	-I ../../libmx/inc \

SRCS = $(wildcard $(SRCD)/*.c)
OBJS = $(addprefix $(OBJD)/, $(SRCS:src/%.c=%.o))

CFLAGS = -std=c11
# -Wall -Wextra -Werror -Wpedantic

all: $(NAME)

$(NAME): $(OBJS)
	@ar crs $(MODULE) $(OBJS)

$(OBJD)/%.o: $(SRCD)/%.c $(INC_PATH) $(INC_POSIX)
	@clang $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@printf "\e[32mcompiled: \e[0m[$(<:$(SRCD)/%.c=%.c)]\n"

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

install: $(NAME) clean

clean:
	@rm -rf $(OBJD)
	@printf "\e[35;1mdeleted $(OBJD)\e[0m\n"

uninstall:
	@make clean
	@rm -rf $(MODULE)
	@rm -rf $(NAME)
	@printf "\e[35;1mUninstall $(MODULE)\e[0m\n"

test1:
	@make all
	@clang $(CFLAGS) -c test.c -o test.o -I $(INC_PATH)
	@clang $(CFLAGS) -g test.o $(MODULE) $(LIB_PATH) -o $(NAME)
	@rm -rf test.o
