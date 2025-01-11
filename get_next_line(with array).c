#include "get_next_line.h"

static void	resize_capacity(char **buffer, size_t *capacity)
{
	char	*temp_ptr;

	temp_ptr = NULL;
	if (BUFFER_SIZE + 1 > SIZE_MAX || (*capacity && SIZE_MAX / *capacity < 2))
	{
		if (*buffer)
			free(*buffer);
		*buffer = NULL;
	}
	else
	{
		if (!*capacity)
			*capacity = BUFFER_SIZE + 1;
		else
		{
			temp_ptr = *buffer;
			*capacity = *capacity * 2 - 1;
		}
		*buffer = (char *)ft_calloc(*capacity, sizeof(char));
		if (*buffer && temp_ptr)
		{
			ft_strlcpy(*buffer, temp_ptr, *capacity);
			free(temp_ptr);
		}
	}
}

static int	push(int fd, char **buffer, size_t *capacity, size_t *readed)
{
	int	read_bit;

	while (1)
	{
		if (*capacity <= *readed + BUFFER_SIZE)
			resize_capacity(buffer, capacity);
		if (!*buffer)
			return (-42);
		read_bit = read(fd, *buffer + *readed, BUFFER_SIZE);
		if (read_bit <= 0)
			break ;
		*readed += read_bit;
		if (ft_strchr(*buffer, NEWLINE))
			break ;
	}
	return (read_bit);
}
/*
static size_t	length(char **endline, char **buffer, size_t readed)
{
	size_t	len;

	if (!*endline)
		len = ft_strlen(*buffer);
	else
	{
		len = *endline - *buffer + 1;
		if (len > readed)
			len = readed;
	}
	return (len);
}

static char	*pop(char **buffer, size_t *readed)
{
	char	*outline;
	char	*endline;
	size_t	linelen;

	if (!*buffer || !**buffer)
		return (NULL);
	endline = ft_strchr(*buffer, NEWLINE);
	linelen = length(&endline, buffer, *readed);
	outline = (char *)ft_calloc(linelen + 1, sizeof(char));
	if (outline)
	{
		ft_strlcpy(outline, *buffer, linelen + 1);
		*readed -= linelen;
		if (endline)
			ft_strlcpy(*buffer, endline + 1, *readed + 1);
		else
			ft_memset(*buffer, 0, linelen);
	}
	return (outline);
}
*/

static char	*pop(char **buffer, size_t *readed)
{
	char	*outline;
	char	*endline;
	size_t	linelen;

	if (!*buffer || !**buffer)
		return (NULL);
	endline = ft_strchr(*buffer, NEWLINE);
	if (!endline)
		linelen = ft_strlen(*buffer);
	else if ((size_t)(endline - *buffer + 1) > *readed)
		linelen = *readed;
	else
		linelen = endline - *buffer + 1;
	outline = (char *)ft_calloc(linelen + 1, sizeof(char));
	if (outline)
	{
		ft_strlcpy(outline, *buffer, linelen + 1);
		*readed -= linelen;
		if (endline)
			ft_strlcpy(*buffer, endline + 1, *readed + 1);
		else
			ft_memset(*buffer, 0, linelen);
	}
	return (outline);
}

void	arg_free(void **buffer, void **capacity, void **readed_count)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (*capacity)
	{
		free(*capacity);
		*capacity = NULL;
	}
	if (*readed_count)
	{
		free(*readed_count);
		*readed_count = NULL;
	}
}

char	*get_next_line(int fd)
{
	static void		*data[3] = {NULL};
	char			*outline;
	int				read_bit;

	if (fd != 0 && fd < 2)
		return (NULL);
	if (!data[1])
		data[1] = ft_calloc(1, sizeof(size_t));
	if (!data[2])
		data[2] = ft_calloc(1, sizeof(size_t));
	read_bit = push(fd, (char **)&data[0],
			(size_t *)data[1], (size_t *)data[2]);
	if (read_bit >= 0)
		outline = pop((char **)&data[0], (size_t *)data[2]);
	if (read_bit < 0 || !*((size_t *)data[2]))
	{
		arg_free(&data[0], &data[1], &data[2]);
		if (read_bit < 0)
			return (NULL);
	}
	return (outline);
}
