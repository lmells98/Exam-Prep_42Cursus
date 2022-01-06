#include "get_next_line.h"

static int	ft_strlen(const char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

static char	*ft_strdup(char *str)
{
	int		i;
	char	*duplicate;

	duplicate = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		duplicate[i] = str[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*get_next_line(int fd)
{
	int		i;
	int		byte;
	char	buff;
	char	saved[100000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	byte = read(fd, &buff, 1);
	while (byte > 0)
	{
		saved[i++] = buff;
		if (buff == '\n')
			break ;
		byte = read(fd, &buff, 1);
	}
	saved[i] = 0;
	if (byte <= 0 && i == 0)
		return (NULL);
	return (ft_strdup(saved));
}
