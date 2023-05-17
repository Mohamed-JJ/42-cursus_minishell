NAME = minishell

SRC = minishell.c \
		utils/utils.c \
		utils/utils_2.c \
		utils/utils_3.c \
		utils/utils_4.c \
		utils/utils_5.c \
		utils/utils_6.c \
		lexer_cmd/lexer_lists.c \
		lexer_cmd/lexer_main.c \
		lexer_cmd/cmd_generator.c \
		utils/inserting_spaces.c \
		utils/ft_split.c \
		utils/ft_free.c \
		utils/handler.c \

OBJ = $(SRC:.c=.o)

INC = includes/minishell.h \
		includes/structs.h \
		includes/lexer.h \
		includes/utils.h \

RM = rm -rf

CC = cc

FLAGS = -Wall -Werror -Wextra

all : $(NAME)

%.o : %.c $(INC)
	@$(CC) $(FLAGS) $<  -c -o $@ -g

$(NAME) : $(OBJ) $(INC)
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