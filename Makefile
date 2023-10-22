NAME			= 	minishell
CC				= 	cc
CFLAGS			=
READLINE_FLAGS	=	-L lib/readline_out/lib -l readline -l history

SRC_DIR			=	src
OBJ_DIR			=	obj
INCLUDE 		= 	-I include -I include/defs
READLINE_INCLUDE=	-I ./lib/readline_out/include/

SRCS			=	src/converter/converter_expand.c \
					src/converter/converter_builtin_exit.c \
					src/converter/converter_external.c \
					src/converter/converter_builtin_export.c \
					src/converter/converter_convert.c \
					src/converter/converter_redir.c \
					src/converter/converter_builtin_echo.c \
					src/converter/converter_builtin_unset.c \
					src/converter/converter_builtin_cd.c \
					src/input/prompt.c \
					src/input/parse_input.c \
					src/input/read_input.c \
					src/lexer/lexer_fragments.c \
					src/lexer/lexer_quotes.c \
					src/lexer/lexer_vars.c \
					src/lexer/lexer_boundaries.c \
					src/lexer/lexer_boundaries2.c \
					src/lexer/lexer_token_ranges.c \
					src/lexer/lexer_token_validate.c \
					src/lexer/lexer_token_classify.c \
					src/lexer/lexer_token_mask.c \
					src/lexer/lexer_fragments_to_tokens.c \
					src/signals/signals.c \
					src/utils/token/token_classify_redirection.c \
					src/utils/token/token_classify_operator.c \
					src/utils/token/token_classify.c \
					src/utils/token/token_classify_parenthesis.c \
					src/utils/token/token_is.c \
					src/utils/deserializer/deserializer_chain.c \
					src/utils/deserializer/deserializer_utils.c \
					src/utils/deserializer/deserializer_command.c \
					src/utils/deserializer/deserializer_deserialize.c \
					src/utils/deserializer/deserializer_var.c \
					src/utils/deserializer/deserializer_arg.c \
					src/utils/deserializer/deserializer_sequence.c \
					src/utils/deserializer/deserializer_file.c \
					src/utils/serializer/serializer_sequence.c \
					src/utils/serializer/serializer_var.c \
					src/utils/serializer/serializer_arg.c \
					src/utils/serializer/serializer_file.c \
					src/utils/serializer/serializer_utils.c \
					src/utils/serializer/serializer_serialize.c \
					src/utils/serializer/serializer_command.c \
					src/utils/serializer/serializer_chain.c \
					src/utils/memory/mem_free.c \
					src/utils/memory/mem_alloc.c \
					src/utils/memory/mem_move.c \
					src/utils/memory/mem_copy.c \
					src/utils/memory/mem_compare.c \
					src/utils/memory/mem_alloc_str.c \
					src/utils/fd/fd_dup.c \
					src/utils/fd/fd_open.c \
					src/utils/fd/fd_pipe.c \
					src/utils/fd/fd_close.c \
					src/utils/path/path_get_home.c \
					src/utils/path/path_boundaries.c \
					src/utils/path/path_segments.c \
					src/utils/path/path_expand.c \
					src/utils/path/path_normalize.c \
					src/utils/path/path_utils.c \
					src/utils/arr/arr_index.c \
					src/utils/arr/arr_sub.c \
					src/utils/arr/arr_sort.c \
					src/utils/arr/arr_clone.c \
					src/utils/arr/arr_add_insert.c \
					src/utils/arr/arr_create.c \
					src/utils/arr/arr_size.c \
					src/utils/arr/arr_free.c \
					src/utils/arr/arr_get_set.c \
					src/utils/arr/arr_print.c \
					src/utils/arr/arr_remove.c \
					src/utils/base64/base64_decode.c \
					src/utils/base64/base64_encode.c \
					src/utils/var/var_expand.c \
					src/utils/var/var_extract.c \
					src/utils/env.c \
					src/utils/assoc/assoc_print.c \
					src/utils/assoc/assoc_get.c \
					src/utils/assoc/assoc_set.c \
					src/utils/assoc/assoc_remove.c \
					src/utils/assoc/assoc_index.c \
					src/utils/assoc/assoc_size.c \
					src/utils/assoc/assoc_create.c \
					src/utils/tmp.c \
					src/utils/range/range_get.c \
					src/utils/range/range_contains.c \
					src/utils/global.c \
					src/utils/error/error_invalid_identifier.c \
					src/utils/error/error_syntax.c \
					src/utils/error/error_no_file_or_dir.c \
					src/utils/error/error.c \
					src/utils/error/error_numeric_arg_required.c \
					src/utils/error/error_command_not_found.c \
					src/utils/error/error_env_not_set.c \
					src/utils/error/error_too_many_args.c \
					src/utils/error/error_not_dir.c \
					src/utils/error/error_permission_denied.c \
					src/utils/error/error_ambiguous_redir.c \
					src/utils/number_convert.c \
					src/utils/str/str_char_is_whitespace.c \
					src/utils/str/str_to_long_unsafe.c \
					src/utils/str/str_range.c \
					src/utils/str/str_trim.c \
					src/utils/str/str_char_replace.c \
					src/utils/str/str_arr_from_assoc.c \
					src/utils/str/str_compare.c \
					src/utils/str/str_range2.c \
					src/utils/str/str_print_error.c \
					src/utils/str/str_range_action.c \
					src/utils/str/str_key_value.c \
					src/utils/str/str_substring.c \
					src/utils/str/str_from_array.c \
					src/utils/str/str_arr_from_array.c \
					src/utils/str/str_copy.c \
					src/utils/str/str_duplicate.c \
					src/utils/str/str_range_set.c \
					src/utils/str/str_starts_with.c \
					src/utils/str/str_length.c \
					src/utils/str/str_char_in_set.c \
					src/utils/str/str_char_is_quote.c \
					src/utils/str/str_random.c \
					src/utils/str/str_cut.c \
					src/utils/str/str_join.c \
					src/utils/str/str_split.c \
					src/utils/str/str_char_repeat.c \
					src/utils/str/str_contains.c \
					src/parser/parser_sequence.c \
					src/parser/parser_redir.c \
					src/parser/parser_vars.c \
					src/parser/parser_command.c \
					src/parser/parser_chain.c \
					src/parser/parser_subsequence.c \
					src/parser/parser_parse.c \
					src/builtins/builtin_echo.c \
					src/builtins/builtin_export.c \
					src/builtins/builtin_unset.c \
					src/builtins/builtin_pwd.c \
					src/builtins/builtin_env.c \
					src/builtins/builtin_exit.c \
					src/builtins/builtin_cd.c \
					src/main.c \
					src/exec/exec_run.c \
					src/exec/exec_sequence.c \
					src/exec/exec_utils.c \
					src/exec/exec_builtin.c \
					src/exec/exec_redirect.c \
					src/exec/exec_external.c \
					src/exec/exec_chain.c

OBJS			=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

READLINE		=	lib/readline_out/lib/libreadline.a

HEADERS			=	include/error.h \
					include/fd.h \
					include/env.h \
					include/range.h \
					include/base64.h \
					include/path.h \
					include/parser.h \
					include/global.h \
					include/deserializer.h \
					include/tmp.h \
					include/minishell.h \
					include/converter.h \
					include/assoc.h \
					include/builtins.h \
					include/serializer.h \
					include/array.h \
					include/memory.h \
					include/lexer.h \
					include/str.h \
					include/token.h \
					include/number.h \
					include/vars.h \
					include/defs/tokendef.h \
					include/defs/cmddef.h \
					include/defs/rangedef.h \
					include/defs/arraydef.h \
					include/defs/exchain.h \
					include/defs/lexerdef.h \
					include/defs/globaldef.h \
					include/defs/assocdef.h

RM				=	rm -rf
GREEN			= 	\033[0;32m
BLUE			=	\033[0;94m
RESET			=	\033[0m

ifndef LENIENT
	CFLAGS += -Wall -Werror -Wextra
endif

ifdef DEBUG
	CFLAGS += -g
#	CFLAGS += -fsanitize=address
endif

CFLAGS += $(INCLUDE) $(READLINE_INCLUDE)

# RULES

all: $(NAME)

$(NAME): $(READLINE) $(OBJS)
	$(CC) $(CFLAGS) $(READLINE_FLAGS) -o $@ $^
	@echo "$(GREEN)*** Minishell compiled!***$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

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
	@echo "$(GREEN)*** Readline compiled!***$(RESET)"

#####################################################################################

clean:
	$(RM) -rf $(OBJ_DIR)
	@echo "$(BLUE)*** Object files cleaned! ***$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(BLUE)*** Executable cleaned! ***$(RESET)"

re: fclean all
	@echo "$(GREEN)*** Cleaned and rebuilt minishell! ***$(RESET)"

delete:
	$(RM) lib/
	@echo "$(BLUE)*** Lib deleted! ***$(RESET)"

test: all
	./$(NAME)

.PHONY: all bonus fclean re delete test