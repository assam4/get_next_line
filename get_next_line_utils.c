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
	i = 0;
	if (n)
	{
		while (i < n - 1 && *src)
			dest[i++] = *src++;
	}
	while (i < n)
		dest[i++] = '\0';
	return (src_len);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*iter;
	size_t	s_len;
	char	letter;

	s_len = ft_strlen(s) + 1;
	iter = NULL;
	letter = (char)c;
	while (s_len--)
	{
		if (*s == letter)
			iter = (char *)s;
		++s;
	}
	return (iter);
}

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*ptr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s) + 1;
	ptr = (char *)malloc((s_len) * sizeof(char));
	if (ptr)
		ft_strlcpy(ptr, s, s_len);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (ptr)
	{
		ft_strlcpy(ptr, s1, s1_len + 1);
		ft_strlcpy(ptr + s1_len, s2, s2_len + 1);
	}
	return (ptr);
}
