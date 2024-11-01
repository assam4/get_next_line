#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// buffer size default value define
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// first action scenario for wrong input
/*
# if BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
*/

// second action scenario for wrong input
# if BUFFER_SIZE < 1
#  error "BUFFER_SIZE must be greater than 0"
# endif

/*
// define allocation size need to comment for norminette :(
# if BUFFER_SIZE < 42
#  define ALLOC_SIZE (BUFFER_SIZE * 2)
# else
#  define ALLOC_SIZE BUFFER_SIZE
# endif
*/

// define character thats split string
# ifndef NEWLINE
#  define NEWLINE '\n'
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
void	*ft_memset(void *ptr, int simb, size_t n);
void	*ft_calloc(size_t num, size_t size);

#endif
