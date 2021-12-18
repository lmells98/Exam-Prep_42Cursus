#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd);

int	main(void)
{
	int	fd;
	char	*i;

	fd = open("./test.txt", O_RDONLY);
	if (fd > 0)
	{
		int	j;
		j = 1;
		i = get_next_line(fd);
		while (i)
		{
			printf("%d : %s", j, i);
			j++;
			i = get_next_line(fd);
		}
	}
	close(fd);
	return (0);
}
