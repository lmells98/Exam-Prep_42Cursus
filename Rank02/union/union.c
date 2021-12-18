#include <unistd.h>

int	main(int ac, char **av)
{
	//Declare 2 index trackers and a fixed array with size of unsigned char.
	int	i;
	int	j;
	int	used[255];
	//This array will be our checking mechanism.
	//Unsigned char has range of 0-255.
	if (ac == 3)
	{
		//Initialise array and fill with 0's.
		i = 0;
		while (i < 255)
		{
			used[i] = 0;
			i++;
		}
		//Assign first index value of 1. This is to index the arguments.
		i = 1;
		while (i < 3)
		{
			j = 0;
			//Loop through argument characters 1 by 1.
			while (av[i][j] != '\0')
			{
				//If We havent stored a value in the array at the index position given by the value of the unsigned char from the argument.
				if (!used[(unsigned char)av[i][j]])
				{
					//We assign the array position a value of 1 and output the current character.
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
