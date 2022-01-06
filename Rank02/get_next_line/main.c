#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int	fd;
	char	*i;

	fd = open("./test.txt", O_RDONLY);
	if (fd > 0)
	{
		i = get_next_line(fd);
		while (i)
		{
			printf("> %s", i);
			i = get_next_line(fd);
		}
	}
	close(fd);
	return (0);
}
