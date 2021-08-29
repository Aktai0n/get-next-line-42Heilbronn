/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 15:31:59 by skienzle          #+#    #+#             */
/*   Updated: 2021/08/29 22:46:00 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

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

static char	*ft_append_buffer(char **rest, char *buffer)
{
	char	*temp;

	if (*rest)
	{
		temp = ft_strdup(*rest);
		free(*rest);
		*rest = ft_strjoin(temp, buffer);
		free(temp);
		return (*rest);
	}
	else
	{
		return (ft_strdup(buffer));
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*rest;
	char		*output;
	ssize_t		bytes_read;
	size_t		nl;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = (char *)malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	while (!ft_strchr_index(rest, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		rest = ft_append_buffer(&rest, buffer);
	}
	free(buffer);
	nl = ft_search_nl(rest);
	output = ft_substr(rest, 0, nl + 1);
	buffer = ft_substr(rest, ft_strlen(output), ft_strlen(rest) - nl);
	free(rest);
	rest = ft_strdup(buffer);
	free(buffer);
	if (ft_strlen(output) == 0)
	{
		free(output);
		free(rest);
		return (NULL);
	}
	return(output);
}
/*
#include <fcntl.h>

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
