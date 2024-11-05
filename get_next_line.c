#include "get_next_line.h"
#include <stdio.h>

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

	while (!ft_strchr(*buffer, NEWLINE))
	{
		if (*capacity <= *readed + BUFFER_SIZE)
			resize_capacity(buffer, capacity);
		if (!*buffer)
			return (-42);
		read_bit = read(fd, *buffer + *readed, BUFFER_SIZE);
		if (read_bit <= 0)
			break ;
		*readed += read_bit;
		printf("Buffer readed count: %zu , Buffer view : %s\n",ft_strlen(*buffer), *buffer);
	}
	return (read_bit);
}

static size_t	length(char **endline, char **buffer)
{
	if (!*endline)
		return (ft_strlen(*buffer));
	else
		return (*endline - *buffer + 1);
}

static char	*pop(char **buffer, size_t *readed)
{
	char	*outline;
	char	*endline;
	size_t	linelen;

	if (!*buffer || !**buffer)
		return (NULL);
	endline = ft_strchr(*buffer, NEWLINE);
	linelen = length(&endline, buffer);
	outline = (char *)ft_calloc(linelen + 1, sizeof(char));
	if (outline)
	{
		ft_strlcpy(outline, *buffer, linelen + 1);
		*readed -= linelen;
		if (endline)
			ft_strlcpy(*buffer, endline + 1, *readed);
		else
			ft_memset(*buffer, 0, linelen);
	}
	return (outline);
}

char	*get_next_line(int fd)
{
	static char		*buffer = NULL;
	static size_t	capacity = 0;
	static size_t	readed_count = 0;
	char			*outline;
	int				read_bit;

	if (fd != 0 && fd < 2)
		return (NULL);
	read_bit = push(fd, &buffer, &capacity, &readed_count);
	if (read_bit >= 0)
		outline = pop(&buffer, &readed_count);
	if (read_bit < 0 || !readed_count)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		readed_count = 0;
		capacity = 0;
		if (read_bit < 0)
			return (NULL);
	}
	return (outline);
}
