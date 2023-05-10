NAME = minishell

SRC = minishell.c \
		utils.c \
		utils_2.c \
		utils_3.c \
		utils_4.c \
		utils_5.c \
		utils_6.c \
		lexer/lexer_lists.c \
		lexer/lexer_main.c \
		ft_split.c \
		ft_free.c \
		handler.c \

OBJ = $(SRC:.c=.o)

RM = rm -rf

CC = cc

FLAGS = -Wall -Werror -Wextra

all : $(NAME)

%.o : %.c minishell.h
	@$(CC) $(FLAGS) $< -c -o $@ -g

$(NAME) : $(OBJ) minishell.h
	@$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME) -g
	@echo █▀▄▀█ ░▀░ █▀▀▄ ░▀░ █▀▀ █░░█ █▀▀ █░░ █░░
	@echo █░▀░█ ▀█▀ █░░█ ▀█▀ ▀▀█ █▀▀█ █▀▀ █░░ █░░
	@echo ▀░░░▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀▀▀ ▀▀▀

clean : $(OBJ) $(OBJ_B)
	@$(RM) $(OBJ) $(OBJ_B)

fclean :
	@$(RM) $(NAME) $(OBJ_B) $(OBJ)

re : fclean all

.PHONY : re clean fclean all