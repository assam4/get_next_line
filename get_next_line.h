/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:49:55 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/30 18:41:52 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE < 1
#  error "BUFFER_SIZE must be greater than 0"
# endif

# ifndef NEWLINE
#  define NEWLINE '\n'
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
void	*ft_memset(void *ptr, int simb, size_t n);
void	*ft_calloc(size_t num, size_t size);

#endif
