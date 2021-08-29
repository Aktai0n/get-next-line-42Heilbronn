/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 15:31:59 by skienzle          #+#    #+#             */
/*   Updated: 2021/08/29 20:17:29 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//#include <stdio.h>

static int	ft_search_nl(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

static char	*ft_append_buffer(char *rest, char *buffer)
{
	char	*temp;
	if (!*buffer)
		return (rest);
	if (!*rest)
		return (ft_strdup(buffer));
	else
	{
		temp = ft_strdup(rest);
		free(rest);
		rest = ft_strjoin(temp, buffer);
		free(temp);
		return (rest);
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*rest = "\0";
	char		*output;
	ssize_t		bytes_read;
	int			nl;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = (char *)malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	while (ft_strchr(rest, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		rest = ft_append_buffer(rest, buffer);
	}
	free(buffer);
	nl = ft_search_nl(rest);
	output = ft_substr(rest, 0, (size_t)nl + 1);
	buffer = ft_substr(rest, ft_strlen(output), ft_strlen(rest));
	free(rest);
	rest = ft_strdup(buffer);
	free(buffer);
	if (ft_strlen(output) == 0)
		return (NULL);
	return(output);
}

//#include <fcntl.h>
/*
int main(void)
{
	int		fd;
	char	*reading;

	fd = open("test_dracula.txt", 100);
	reading = get_next_line(fd);
	printf("%s", reading);
	
	while (reading)
	{
		reading = get_next_line(fd);
		printf("%s", reading);
	}
	
	close(fd);
	return (0);
}
*/
