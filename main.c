#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd;
	char *line;
	int lines_read;

	lines_read = 0;
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open file.\n");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		lines_read++;
		printf("Line %d: %s", lines_read, line);
		free(line);
	}
	printf("\n--- EOF reached or error ---\n");
	close(fd);
	return (0);
}