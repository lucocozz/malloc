# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/30 15:23:20 by lucocozz          #+#    #+#              #
#    Updated: 2022/12/03 19:33:06 by lucocozz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRCS =	malloc.c				\
		free.c					\
		realloc.c				\
		show_alloc_mem.c		\
		show_alloc_mem_ex.c		\
		show_alloc_mem_freed.c	\
		show_page_num.c			\
		libft.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPENDENCIES = $(OBJS:%.o=%.d)

SRCS_DIR = sources
OBJS_DIR = .objs
INCLUDES_DIR = includes $(LIBS:%=lib%/includes) $(LIBS:%=lib%)

LIBS =

MAKE = make
CC = clang
RM = rm -f
MKDIR = mkdir -p
DEBUG = off

CFLAGS = -MMD -Wall -Wextra -Werror -std=gnu99
CXXFLAGS = $(INCLUDES_DIR:%=-I %)
ifeq ($(DEBUG), on)
	CXXFLAGS += -g3
endif
LDFLAGS = $(LIBS:%=-L lib%) $(LIBS:%=-l%)

vpath %.c	$(addprefix $(SRCS_DIR), /.)

all:
	$(foreach LIB, ${LIBS}, ${MAKE} -C lib${LIB} ;)
	$(MAKE) $(NAME)
	$(CC) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) -lpthread -o tests main.c libft_malloc.so
	mv tests.d .objs/

scan:
	scan-build-12 $(MAKE)

$(NAME): $(OBJS) | $(LIBS:%=lib%.a)
	ar -rcs $(NAME) $(OBJS)
	$(RM) libft_malloc.so
	ln -s $(NAME) libft_malloc.so

-include $(DEPENDENCIES)
$(OBJS_DIR)/%.o: %.c $(OBJS_DIR)/debug$(DEBUG) | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@ 

$(OBJS_DIR):
	$(MKDIR) $(OBJS_DIR)

lib%.a:
	$(MAKE) -C $(@:%.a=%)

$(OBJS_DIR)/debug$(DEBUG): | $(OBJS_DIR)
	$(RM) $(OBJS_DIR)/debug*
	touch $@

clean:
	$(foreach LIB, $(LIBS), $(MAKE) $@ -C lib$(LIB);)
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME) $(foreach LIB, $(LIBS), lib$(LIB)/lib$(LIB).a) libft_malloc.so
	$(RM) tests tests.d

re: fclean all

test:
	clang mains/test$(main).c -o test$(main)
	clang mains/test$(main).c -D LIBFT libft_malloc.so -o test$(main)_libft
	/usr/bin/time -v ./test$(main)
	/usr/bin/time -v ./test$(main)_libft
	rm test$(main)
	rm test$(main)_libft

.PHONY: all clean fclean re scan test
