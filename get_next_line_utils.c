/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:49:46 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/30 23:18:13 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (s && *s)
	{
		if (*s == c)
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
	if (!total)
		return (NULL);
	if (num && total / num != size)
		return (NULL);
	ptr = malloc(total);
	if (ptr)
		return (ft_memset(ptr, 0, total));
	return (NULL);
}
