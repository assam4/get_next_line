#include "get_next_line.h"

static void	resize_capacity(char **buffer, size_t *capacity)
{
	char	*temp_ptr;

	if (!*buffer)
	{
		*buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (*buffer)
			*capacity = BUFFER_SIZE + 1;
	}
	else
	{
		temp_ptr = *buffer;
		*buffer = (char *)ft_calloc(*capacity * 2 - 1, sizeof(char));
		if (!*buffer)
			*capacity = 0;
		else
		{
			ft_strlcpy(*buffer, temp_ptr, *capacity);
			*capacity = *capacity * 2 - 1;
		}
		free(temp_ptr);
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
	}
	return (read_bit);
}

static size_t	length(char **endline, char **buffer)
{
	if (!endline)
		return (ft_strlen(*buffer));
	else
		return (*endline - *buffer + 1);
}

static char	*pop(char **buffer, size_t *capacity, size_t *readed)
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
			ft_strlcpy(*buffer, endline + 1, *capacity);
		else
			ft_memset(*buffer, 0, *capacity);
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
	if (read_bit < 0)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		readed_count = 0;
		capacity = 0;
		return (NULL);
	}
	outline = pop(&buffer, &capacity, &readed_count);
	if (!outline)
	{
		free(buffer);
		buffer = NULL;
	}
	return (outline);
}
