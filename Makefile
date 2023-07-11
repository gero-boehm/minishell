NAME			= 	minishell
CC				= 	cc
CFLAGS			= 	-Wall -Werror -Wextra
READLINE_FLAGS	=	-Llib/readline_out/lib -lreadline -lhistory

INCLUDE 		= 	-I include -I lib/libft
READLINE_INCLUDE=	-I ./lib/readline_out/include/

MAN_FILES		=	src/minishell.c src/prompt.c src/signals.c src/exec.c
BONUS_FILES		=	src_bonus/bonus.c

MAN_OBJ			=	$(MAN_FILES:.c=.o)
BONUS_OBJ		=	$(BONUS_FILES:.c=.o)

LIBFT			=	lib/libft/libft.a
READLINE		=	lib/readline_out/lib/libreadline.a

RM				=	rm -rf
GREEN			= 	\033[0;32m
BLUE			=	\033[0;94m
WHITE			=	\033[0m


ifdef DEBUG
	CFLAGS += -g
endif

# RULES

all: $(NAME)

$(NAME): $(READLINE) $(LIBFT)  $(MAN_OBJ)
	$(CC) $(MAN_OBJ) -o $(NAME) $(LIBFT) $(READLINE_FLAGS) $(CFLAGS)
	@echo "$(GREEN)*** Minishell compiled!***$(WHITE)"


%.o: %.c $(INCLUDE) $(READLINE_INCLUDE) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@if [ ! -d "./lib/libft" ]; then git clone https://github.com/gero-boehm/libft.git ./lib/libft; fi
	@make  --silent DEBUG=$(DEBUG) -C lib/libft

#####################################################################################
READLINE_VERSION=	readline-8.1.2

$(READLINE):
	@mkdir -p lib
	@curl -s https://ftp.gnu.org/gnu/readline/$(READLINE_VERSION).tar.gz --output lib/$(READLINE_VERSION).tar.gz
	@tar xfz lib/$(READLINE_VERSION).tar.gz -C lib
	@cd lib/$(READLINE_VERSION); ./configure --prefix=$(PWD)/lib/readline_out
	@make -C lib/$(READLINE_VERSION)
	@make install -C lib/$(READLINE_VERSION)
	@rm -rf lib/$(READLINE_VERSION)
	@rm -f lib/$(READLINE_VERSION).tar.gz
	@echo "$(GREEN)*** Readline compiled!***$(WHITE)"

#####################################################################################

clean:
	$(RM) $(MAN_OBJ)
#	$(RM) $(BONUS_OBJ)
	make clean --silent -C lib/libft
	@echo "$(BLUE)*** Object files cleaned! ***$(WHITE)"

fclean: clean
	$(RM) $(NAME)
	make fclean --silent -C lib/libft
	@echo "$(BLUE)*** Executable cleaned! ***$(WHITE)"

re: fclean all
	@echo "$(GREEN)*** Cleaned and rebuilt minishell! ***$(WHITE)"

delete:
	$(RM) lib/
	@echo "$(BLUE)*** Lib deleted! ***$(WHITE)"

.PHONY:  bonus fclean re all delete