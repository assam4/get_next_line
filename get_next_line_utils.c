#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		++count;
	return (count);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (!n)
		return (src_len);
	i = 0;
	while (i < n - 1 && src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (src_len);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	s_len;
	char	letter;

	letter = (char)c;
	s_len = ft_strlen(s) + 1;
	while (s_len--)
	{
		if (*s == letter)
			return ((char *)s);
		++s;
	}
	return (NULL);
}

void	*ft_memset(void *ptr, int simb, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (n--)
		*p++ = (unsigned char)simb;
	return (ptr);
}

void	*ft_calloc(size_t num, size_t size)
{
	size_t	total;
	void	*ptr;

	total = num * size;
	if (num && total / num != size)
		return (NULL);
	ptr = malloc(total);
	if (ptr)
		return (ft_memset(ptr, num, size));
	return (NULL);
}
