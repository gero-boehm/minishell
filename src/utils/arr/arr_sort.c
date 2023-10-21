#include "array.h"
#include "memory.h"

static int	arr_element_clone(t_array *arr, unsigned long index, void **clone)
{
	void	*element;

	element = arr_get(arr, index);
	if (mem_alloc(arr->bytes, clone))
		return (1);
	mem_ncpy(*clone, element, arr->bytes);
	return (0);
}

static void	arr_elements_shift(t_array *arr, unsigned long index, size_t len)
{
	void	*src;
	void	*dst;

	src = arr_get(arr, index);
	dst = arr_get(arr, index + 1);
	mem_nmov(dst, src, len * arr->bytes);
}

int	arr_sort(t_array *arr, int (fn)(void *, void *))
{
	unsigned long	i;
	unsigned long	j;
	void			*element2;
	void			*tmp;

	i = 0;
	while (++i < arr_size(arr))
	{
		j = i;
		element2 = arr_get(arr, i);
		if (arr_element_clone(arr, i, &tmp))
			return (1);
		while (j)
		{
			if (fn(arr_get(arr, j - 1), element2) > 0)
				break ;
			j--;
		}
		if (j == i)
			continue ;
		arr_elements_shift(arr, j, i - j);
		arr_set(arr, j, tmp);
		mem_free(tmp);
	}
	return (0);
}
