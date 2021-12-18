#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static int	ft_strchr(char *str, int c, int flag)
{
	int	i;

	if (flag == 1 && !str)
		return (-5);
	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s && s[i])
		i++;
	return (i);
}

static char	*ft_strnjoin(char *s1, char *s2, int bytes)
{
	int		i;
	int		j;
	char	*output;

	if (s2 == NULL)
		return (NULL);
	output = (char *)malloc((ft_strlen(s1) + bytes + 1) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	if (!s1)
	{
		while (s2[i] != '\0')
		{
			output[i] = s2[i];
			i++;
		}
		output[i] = '\0';
		return (output);
	}
	while (s1[i] != '\0')
	{
		output[i] = s1[i];
		i++;
	}
	j = 0;
	while ((s2[j] != '\0') && j < bytes)
	{
		output[i] = s2[j];
		i++;
		j++;
	}
	output[i] = '\0';
	return (output);
}

static char	*update_line(char **buff, int pos)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*buff) - pos;
	tmp = ft_strnjoin(*buff + pos, "", len);
	ft_free(buff);
	*buff = tmp;
	return (*buff);
}

static char	*check_output(char **buff, int pos, int bytes)
{
	char	*output;

	if ((bytes <= 0 && !*buff) || pos == -5)
	{
		if (*buff)
			return (*buff);
		return (NULL);
	}
	output = NULL;
	if (pos == -1)
		pos = ft_strlen(*buff);
	else
		pos++;
	output = ft_strnjoin("", *buff, pos);
	if (pos == ft_strlen(*buff))
		ft_free(buff);
	else
		*buff = update_line(buff, pos);
	return (output);
}

char	*get_next_line(int fd)
{
	int			i;
	int			bytes;
	int			pos;
	char		*line;
	static char	*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	pos = ft_strchr(buff, '\n', 0);
	while (pos == -1 && pos != -5)
	{
		line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!line)
			return (NULL);
		i = 0;
		while (i <= BUFFER_SIZE)
		{
			line[i] = '0';
			i++;
		}
		bytes = read(fd, line, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buff = ft_strnjoin(buff, line, bytes);
		pos = ft_strchr(buff, '\n', 1);
		ft_free(&line);
	}
	ft_free(&line);
	return (check_output(&buff, pos, bytes));
}
