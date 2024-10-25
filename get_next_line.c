#include "get_next_line.h"

static int	small_aloc(int fd, char **mini_buf)
{
	int	count;

	if (!*mini_buf)
		*mini_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*mini_buf)
		return (-1);
	count = read(fd, *mini_buf, BUFFER_SIZE);
	if (count <= 0)
	{
		free(*mini_buf);
		*mini_buf = NULL;
	}
	else
		(*mini_buf)[count] = '\0';
	return (count);
}

static int	push_to_buf(int fd, char **buffer)
{
	char		*temp;
	int			count;
	static char	*mini_buf = NULL;

	count = small_aloc(fd, &mini_buf);
	if (count <= 0)
		return (count);
	if (!*buffer)
	{
		*buffer = mini_buf;
		mini_buf = NULL;
	}
	else
	{
		temp = *buffer;
		*buffer = ft_strjoin(temp, mini_buf);
		free(temp);
	}
	return (count);
}

static char	*compress_buffer(char **buffer, char *endline)
{
	size_t	line_len;
	char	*newline;
	char	*temp;

	line_len = endline - *buffer + 1;
	newline = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!newline)
		return (NULL);
	ft_strlcpy(newline, *buffer, line_len + 1);
	temp = ft_strdup(endline + 1);
	if (!temp)
	{
		free(newline);
		return (NULL);
	}
	free(*buffer);
	*buffer = temp;
	return (newline);
}

static char	*cut_buf(char **buffer, int read_count)
{
	char	*endline;
	char	*last_line;

	endline = ft_strrchr(*buffer, '\n');
	if (!endline)
	{
		if (!read_count)
		{
			last_line = ft_strdup(*buffer);
			free(*buffer);
			*buffer = NULL;
			return (last_line);
		}
		return (NULL);
	}
	return (compress_buffer(buffer, endline));
}

char	*get_next_line(int fd)
{
	static char	*render_buffer = NULL;
	int			read_count;
	char		*out_buf;

	if (fd < 0)
		return (NULL);
	while (1)
	{
		read_count = push_to_buf(fd, &render_buffer);
		if (read_count < 0)
			break ;
		if (!read_count && !render_buffer)
			break ;
		out_buf = cut_buf(&render_buffer, read_count);
		if (out_buf)
			return (out_buf);
	}
	if (render_buffer)
		free(render_buffer);
	render_buffer = NULL;
	return (NULL);
}
