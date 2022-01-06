#include <unistd.h>

int	main(int ac, char **av)
{
	int	i;
	int	j;
	int	used[255];

	if (ac == 3)
	{
		i = 0;
		while (i < 255)
		{
			used[i] = 0;
			i++;
		}
		i = 1;
		while (i < 3)
		{
			j = 0;
			while (av[i][j] != '\0')
			{
				if (!used[(unsigned char)av[i][j]])
				{
					used[(unsigned char)av[i][j]] = 1;
					write(1, &av[i][j], 1);
				}
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
