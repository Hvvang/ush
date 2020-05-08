NAME = libmx.a

INCD = inc
SRCD = src
OBJD = obj

INC = libmx.h

INCS = inc/libmx.h
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=obj/%.o)

CFLAGS = -std=gnu99 -Wall -Wextra -Werror -Wpedantic

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@printf "\e[32;1m$@ created\e[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@clang $(CFLAGS) -c $< -o $@ -I $(INCD)
	@printf "\e[32mcompiled[libmx]: \e[0m[$(<:$(SRCD)/%.c=%.c)]\n"

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

install: all clean

uninstall: clean
	@rm -rf $(NAME)
	@printf "\e[34;1mUninstall $(NAME)\e[0m\n"

clean:
	@rm -rf $(OBJD)
	@printf "\e[34;1mdeleted object files in libmx\e[0m\n"

reinstall: uninstall install
