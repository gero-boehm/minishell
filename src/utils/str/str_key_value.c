#include "str.h"
#include "range.h"

int	str_key_value(char *str, char **key, char **value)
{
	t_range range;

	*key = NULL;
	*value = NULL;
	if (str_range_to_exclusive(str, "=", 0, &range))
		return (str_dup(str, key));
	if (str_extract_range(str, &range, key))
		return (2);
	range.start = range_end(&range) + 1;
	range.length = str_len(str) - range.start;
	if (str_extract_range(str, &range, value))
		return (3);
	return (0);
}
