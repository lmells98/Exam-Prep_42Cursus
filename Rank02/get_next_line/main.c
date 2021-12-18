#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd);

int	main(void)
{
	int	fd;
	int	i;

	fd = open("./test.txt", O_RDONLY);
	if (fd > 0)
	{
		i = 0;
		while (i < 4)
		{
			printf("%d : %s", i + 1, get_next_line(fd));
			i++;
		}
	}
	close(fd);
	return (0);
}
