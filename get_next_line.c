/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 15:31:59 by skienzle          #+#    #+#             */
/*   Updated: 2021/08/30 12:51:47 by skienzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

static size_t	ft_search_nl(char *rest)
{
	int		i;

	i = 0;
	while (rest[i])
	{
		if (rest[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

static int	ft_no_newline(char *rest)
{
	int	i;

	if (rest == NULL)
		return (1);
	i = 0;
	while (rest[i])
	{
		if (rest[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

static char	*ft_append_buffer(char *rest, char *buffer)
{
	char	*temp;

	if (rest)
	{
		temp = ft_strdup(rest);
		free(rest);
		rest = ft_strjoin(temp, buffer);
		free(temp);
		return (rest);
	}
	return (ft_strdup(buffer));
}

static char	*ft_read_file(int fd, char *rest)
{
	char	*buffer;
	ssize_t	num_bytes;

	buffer = (char *)malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while (ft_no_newline(rest))
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes == 0 || num_bytes == -1)
			break ;
		buffer[num_bytes] = '\0';
		rest = ft_append_buffer(rest, buffer);
	}
	free(buffer);
	if (num_bytes == -1)
		return (NULL);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*output;
	char		*temp;
	size_t		nl;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	rest = ft_read_file(fd, rest);
	if (rest == NULL)
		return (NULL);
	nl = ft_search_nl(rest);
	output = ft_substr(rest, 0, nl + 1);
	if (ft_strlen(output) == 0)
	{
		free(output);
		free(rest);
		return (NULL);
	}
	temp = ft_substr(rest, nl + 1, ft_strlen(rest) - nl);
	free(rest);
	rest = ft_strdup(temp);
	free(temp);
	return (output);
}
