NAME			= 	minishell
CC				= 	cc
CFLAGS			=
READLINE_FLAGS	=	-L lib/readline_out/lib -l readline -l history

INCLUDE 		= 	-I include -I include/defs -I lib/libft
READLINE_INCLUDE=	-I ./lib/readline_out/include/

# MAN_FILES		=	src/main.c src/minishell.c src/prompt.c src/signals.c src/exec.c \
					\
				 	src/builtins/builtin_cd.c src/builtins/builtin_echo.c src/builtins/builtin_env.c src/builtins/builtin_exit.c \
					src/builtins/builtin_export.c src/builtins/builtin_pwd.c src/builtins/builtin_unset.c \
					\
					src/utils/env.c src/utils/global.c src/utils/wildcard.c \
					\
					src/utils/memory/mem_alloc.c src/utils/memory/mem_alloc_str.c src/utils/memory/mem_free_str_arr.c src/utils/memory/mem_copy.c src/utils/memory/mem_compare.c \
					\
					src/utils/arr/arr_index.c src/utils/arr/arr_add.c src/utils/arr/arr_create.c src/utils/arr/arr_size.c \
					src/utils/arr/arr_free.c src/utils/arr/arr_get_set.c src/utils/arr/arr_remove.c src/utils/arr/arr_print_str.c \
					\
					src/utils/assoc/assoc_print.c src/utils/assoc/assoc_get.c src/utils/assoc/assoc_set.c \
					src/utils/assoc/assoc_remove.c src/utils/assoc/assoc_size.c src/utils/assoc/assoc_create.c \
					\
					src/utils/sequence/sequence_factory.c src/utils/sequence/sequence_print.c \
					\
					src/utils/str/str_range.c src/utils/str/str_trim.c src/utils/str/str_malloc.c src/utils/str/str_arr_from_assoc.c \
					src/utils/str/str_compare.c src/utils/str/str_range2.c src/utils/str/str_range_action.c src/utils/str/str_substring.c \
					src/utils/str/str_from_array.c src/utils/str/str_arr_from_array.c src/utils/str/str_copy.c src/utils/str/str_duplicate.c \
					src/utils/str/str_length.c src/utils/str/str_cut.c src/utils/str/str_join.c src/utils/str/str_split.c
MAN_FILES		=	$(shell find src -type f -name '*.c')
BONUS_FILES		=	src_bonus/bonus.c

MAN_OBJ			=	$(MAN_FILES:.c=.o)
BONUS_OBJ		=	$(BONUS_FILES:.c=.o)

LIBFT			=	lib/libft/libft.a
READLINE		=	lib/readline_out/lib/libreadline.a

HEADERS			=	$(wildcard include/*.h) $(wildcard include/def/*.h) lib/libft/libft.h

RM				=	rm -rf
GREEN			= 	\033[0;32m
BLUE			=	\033[0;94m
WHITE			=	\033[0m

ifndef LENIENT
	CFLAGS += -Wall -Werror -Wextra
endif

ifdef DEBUG
	CFLAGS += -g
endif

CFLAGS += $(INCLUDE) $(READLINE_INCLUDE)

# RULES

all: $(NAME)

$(NAME): $(READLINE) $(LIBFT) $(MAN_OBJ)
	$(CC) $(CFLAGS) $(READLINE_FLAGS) -o $@ $^
	@echo "$(GREEN)*** Minishell compiled!***$(WHITE)"


%.o: %.c $(HEADERS) Makefile
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

test: all
	./$(NAME)

.PHONY: all bonus fclean re delete test