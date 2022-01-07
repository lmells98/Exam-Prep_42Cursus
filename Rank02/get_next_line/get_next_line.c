#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int		i;
	int		byte;
	char	tmp;
	char	*line;
	char	buffer[100000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	line = NULL;
	byte = read(fd, &tmp, 1);
	while (byte > 0)
	{
		buffer[i++] = tmp;
		if (tmp == '\n')
			break ;
		byte = read(fd, &tmp, 1);
	}
	buffer[i] = 0;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line || (byte <= 0 && i == 0))
		return (NULL);
	i = 0;
	while (buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
