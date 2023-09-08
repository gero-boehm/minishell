#include "array.h"
#include "str.h"

static int lexer_spaces_augment_start(t_array *spaces)
{
	unsigned long	index;

	index = *(unsigned long *) arr_get(spaces, 0);
	if (index == 0)
		return (0);
	index = 0;
	return (arr_insert_at(spaces, 0, &index));
}

static int lexer_spaces_augment_end(t_array *spaces, size_t count)
{
	unsigned long	index;

	index = *(unsigned long *) arr_get(spaces, arr_size(spaces) - 1);
	if (index == count - 1)
		return (0);
	return (arr_add(spaces, &count));
}

static int lexer_spaces_augment(t_array *spaces, size_t count)
{
	if (lexer_spaces_augment_start(spaces))
		return (1);
	if (lexer_spaces_augment_end(spaces, count))
		return (2);
	return (0);
}

int	lexer_spaces_get(t_array *fragments, t_array *spaces)
{
	unsigned long	i;
	char			*fragment;

	if (arr_create(spaces, sizeof(unsigned long)))
		return (1);
	i = 0;
	while (i < arr_size(fragments))
	{
		fragment = *(char **) arr_get(fragments, i);
		if (!str_char_is_whitespace(*fragment))
		{
			i++;
			continue ;
		}
		if (arr_add(spaces, &i))
			return (2);
		i++;
	}
	if (lexer_spaces_augment(spaces, arr_size(fragments)))
		return (3);
	return (0);
}