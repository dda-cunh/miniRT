#include "cvector.h"

void	*_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_bytes;
	unsigned char	*desints;

	i = -1;
	src_bytes = (unsigned char *)src;
	desints = (unsigned char *)dest;
	if (desints >= src_bytes && desints <= src_bytes + n)
	{
		if (dest)
			while (n--)
				desints[n] = src_bytes[n];
	}
	else
		while (++i < n)
			desints[i] = src_bytes[i];
	return (dest);
}

void	*_realloc(void *ptr, size_t prev_size, size_t new_size)
{
	unsigned char	*bytes;

	if (new_size <= prev_size)
		return (ptr);
	bytes = malloc(new_size);
	if (!ptr)
		return (bytes);
	if (!bytes)
	{
		free(ptr);
		return (NULL);
	}
	_memmove(bytes, ptr, prev_size);
	free(ptr);
	return (bytes);
}
