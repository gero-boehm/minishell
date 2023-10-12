int	str_char_replace(char *str, char find, char replace)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == find)
		{
			*str = replace;
			count++;
		}
		str++;
	}
	return (count);
}
