#include "get_next_line.h"

static void	buffer_resize(char **buffer, size_t *size)
{
	char	*temp;

	if (!*buffer)
	{
		*buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!*buffer)
			return ;
		*size = BUFFER_SIZE + 1;
	}
	else
	{
		temp = *buffer;
		*buffer = (char *)ft_calloc(*size * 2, sizeof(char));
		if (!*buffer)
			*size = 0;
		else
		{
			ft_strlcpy(*buffer, temp, *size);
			*size = *size * 2;
		}
		free(temp);
	}
}

static int	buffer_push(int fd, char **buffer, size_t *size, size_t *index)
{
	int	read_bit;

	while (!ft_strchr(*buffer, NEWLINE))
	{
		if (!(*size) || (*size - 1) < (*index + BUFFER_SIZE))
			buffer_resize(buffer, size);
		if (!*buffer)
			return (-99);
		read_bit = read(fd, *buffer + *index, BUFFER_SIZE);
		if (read_bit <= 0)
			break ;
		*index += read_bit;
	}
	return (read_bit);
}

size_t	outline_len(char **endline, char **buffer)
{
	if (!endline)
		return (ft_strlen(*buffer));
	else
		return (*endline - *buffer + 1);
}

static char	*buffer_pop(char **buffer, size_t *index, size_t *size)
{
	char	*outline;
	char	*endline;
	size_t	out_len;

	if (!*buffer || !**buffer)
		return (NULL);
	endline = ft_strchr(*buffer, NEWLINE);
	out_len = outline_len(&endline, buffer);
	outline = (char *)ft_calloc(out_len + 1, sizeof(char));
	if (outline)
	{
		ft_strlcpy(outline, *buffer, out_len + 1);
		*index -= out_len;
		if (out_len != ft_strlen(*buffer))
			ft_strlcpy(*buffer, endline + 1, *size);
		else
			ft_memset(*buffer, 0, *size);
	}
	return (outline);
}

char	*get_next_line(int fd)
{
	static char		*fd_buffer = NULL;
	static size_t	bf_index = 0;
	static size_t	bf_size = 0;
	char			*out_line;
	int				rd_bit;

	if (fd < 0)
		return (NULL);
	rd_bit = buffer_push(fd, &fd_buffer, &bf_size, &bf_index);
	if (rd_bit < 0)
	{
		if (fd_buffer)
			free(fd_buffer);
		bf_index = 0;
		bf_size = 0;
		return (NULL);
	}
	out_line = buffer_pop(&fd_buffer, &bf_index, &bf_size);
	if (!out_line)
	{
		free(fd_buffer);
		fd_buffer = NULL;
	}
	return (out_line);
}
