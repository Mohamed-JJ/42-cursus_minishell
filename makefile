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
        utils/handler.c ./execution/execution_utils.c  ./execution/execution_utils_1.c ./execution/execution_utils_2.c \
        ./execution/execution_utils_3.c ./execution/execution_utils_4.c ./execution/execution_utils_5.c \
        ./execution/execution_utils_6.c  ./execution/execution_utils_7.c 

OBJ = $(SRC:.c=.o)

INC = includes/minishell.h \
        includes/structs.h \
        includes/lexer.h \
        includes/utils.h \

RM = rm -f

CC = cc

FLAGS = -Wall -Werror -Wextra  

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@

$(NAME) : $(OBJ) $(INC)
	@cd libft && make 
	@$(CC) -L $(shell brew --prefix readline)/lib -lreadline $(FLAGS) $(OBJ) ./libft/libft.a -o $(NAME) -g
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