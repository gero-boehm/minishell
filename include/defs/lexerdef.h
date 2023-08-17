#ifndef LEXERDEF_H
# define LEXERDEF_H

typedef enum e_token_type {
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_OPERAND,
	TOKEN_REDIRECTION,
	TOKEN_HEREDOC
}	t_token_type;

typedef enum e_string_type {
	STRING_NONE,
	STRING_SINGLE,
	STRING_DOUBLE,
}	t_string_type;

typedef enum e_lexer_mode {
	MODE_COMMAND,
	MODE_ARG,
	MODE_OPERAND,
	MODE_REDIRECTION,
	MODE_HEREDOC
}	t_lexer_mode;

typedef struct s_token {
	char			*str;
	t_token_type	type;
}	t_token;

typedef struct s_lexer_state
{
	t_lexer_mode	mode;
	t_string_type	string_type;
	int				is_escaped;
}	t_lexer_state;


#endif