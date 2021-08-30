#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
** Includes
*/
# include <unistd.h>
# include <stdlib.h>

/*
** Prototypes
*/
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif