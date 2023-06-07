NAME		= 	minishell
CFLAGS		= 	-Wall -Werror -Wextra
CC			= 	cc
RM			=	rm -rf
INCLUDE 	= 	-I include

MAN_FILES	=	src_man/minishell.c 
BONUS_FILES	=	src_bonus/bonus.c		

MAN_OBJ		=	$(MAN_FILES:.c=.o)
BONUS_OBJ	=	$(BONUS_FILES:.c=.o)

LIBS		=	libs/libs.a

GREEN		= 	\033[0;32m
BLUE		=	\033[0;94m
WHITE		=	\033[0m


ifdef DEBUG
	CFLAGS += -g
endif

# RULES

all: $(NAME) 

$(NAME): $(LIBS) $(MAN_OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(MAN_OBJ) $(LIBS) $(INCLUDE)
	@echo "$(GREEN)*** Minishell compiled!***$(WHITE)"
	

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBS):
	@if [ ! -d "./libs" ]; then git clone https://github.com/gero-boehm/libft.git; fi
	@make --silent DEBUG=$(DEBUG) -C libs

clean:
	$(RM) $(MAN_OBJ)
#	$(RM) $(BONUS_OBJ)
	make clean --silent -C libs
	@echo "$(BLUE)*** Object files cleaned! ***$(WHITE)"

fclean: clean
	$(RM) $(NAME)
	make fclean --silent -C libs
	@echo "$(BLUE)*** Executable cleaned! ***$(WHITE)"

re: fclean all
	@echo "$(GREEN)*** Cleaned and rebuilt minishell! ***$(WHITE)"

.PHONY:  bonus fclean re all