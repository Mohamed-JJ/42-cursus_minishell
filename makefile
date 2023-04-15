NAME = minishell

SRC = minishell.c \
		utils.c \
		lexer/lexer_lists.c \
		lexer/lexer_main.c \
		export_env.c \

OBJ = $(SRC:.c=.o)

RM = rm -rf

CC = cc

FLAGS = -Wall -Werror -Wextra

all : $(NAME)

%.o : %.c minishell.h
	@$(CC) $(FLAGS) $< -c -o $@ -g

$(NAME) : $(OBJ) minishell.h
	@$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME) -g

clean : $(OBJ) $(OBJ_B)
	@$(RM) $(OBJ) $(OBJ_B)

fclean :
	@$(RM) $(NAME) $(OBJ_B) $(OBJ)

re : fclean all

.PHONY : re clean fclean all