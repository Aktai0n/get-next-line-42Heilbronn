#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd[2];
	int		i;
	char	*reading;

	i = 0;
	fd[0] = open("test_dracula.txt", O_RDONLY);
	fd[1] = open("test_short.txt", O_RDONLY);
	reading = get_next_line(0);
	printf("%s", reading);
	reading = get_next_line(fd[0]);
	
	while (i < 6)
	{
		printf("line %d=%s", i, reading);
		reading = get_next_line(fd[0]);
		i++;
	}
	
	while (reading)
	{
		printf("%s", reading);
		reading = get_next_line(fd[1]);
	}
	
	reading = get_next_line(fd[0]);
	while (reading)
	{
		printf("line %d=%s", i, reading);
		reading = get_next_line(fd[0]);
		i++;
	}
	
	free(reading);
	close(fd[1]);
	close(fd[0]);
	return (0);
}
