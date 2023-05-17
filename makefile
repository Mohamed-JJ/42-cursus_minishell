NAME = minishell

OBJ = minishell.o \
		utils/utils.o \
		utils/utils_2.o \
		utils/utils_3.o \
		utils/utils_4.o \
		utils/utils_5.o \
		utils/utils_6.o \
		lexer_cmd/lexer_lists.o \
		lexer_cmd/lexer_main.o \
		lexer_cmd/cmd_generator.o \
		utils/inserting_spaces.o \
		utils/ft_split.o \
		utils/ft_free.o \
		utils/handler.o ./execution/execution_utils.o  ./execution/execution_utils_1.o\


INC = includes/minishell.h \
		includes/structs.h \
		includes/lexer.h \
		includes/utils.h \

RM = rm -f

CC = cc

FLAGS = -Wall -Werror -Wextra

all : $(NAME)


$(NAME) : $(OBJ) $(INC)
	@cd libft && make 
	@$(CC) $(FLAGS) $(OBJ) ./libft/libft.a -lreadline -o $(NAME) -g
	@echo █▀▄▀█ ░▀░ █▀▀▄ ░▀░ █▀▀ █░░█ █▀▀ █░░ █░░
	@echo █░▀░█ ▀█▀ █░░█ ▀█▀ ▀▀█ █▀▀█ █▀▀ █░░ █░░
	@echo ▀░░░▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀▀▀ ▀░░▀ ▀▀▀ ▀▀▀ ▀▀▀

$(OBJ) : $(INC)

clean : $(OBJ)
	@cd libft && make clean
	@$(RM) $(OBJ) 

fclean :
	@cd libft && make fclean
	@$(RM) $(NAME) $(OBJ)

re : fclean all

.PHONY : re clean fclean all