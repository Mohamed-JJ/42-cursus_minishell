# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 22:38:08 by imaaitat          #+#    #+#              #
#    Updated: 2023/05/17 19:25:27 by mjarboua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS= -Wall -Werror -Wextra -I libft.h
AR=ar cr
RM=rm -rf
OBJ= ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_strlen.o \
	   ft_toupper.o ft_tolower.o ft_strchr.o ft_strrchr.o ft_strcmp.o \
	   ft_strnstr.o ft_strlcpy.o ft_strlcat.o ft_atoi.o ft_strdup.o \
	   ft_substr.o ft_strjoin.o ft_split.o ft_itoa.o ft_strmapi.o \
	   ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_isprint.o \
	   ft_putnbr_fd.o ft_strtrim.o ft_memcpy.o ft_memmove.o ft_memset.o \
	   ft_memcmp.o ft_memchr.o ft_bzero.o ft_calloc.o ft_striteri.o \
	   get_next_line.o  get_next_line_utils.o

NAME=libft.a

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m


all: $(NAME)
	@echo "$(RED)------#done#------$(RESET)"

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

%.o: %.c libft.h
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaned$(RESET)"
	@$(RM) $(OBJ) $(BOBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all