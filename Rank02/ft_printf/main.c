#include <stdio.h>
#include <limits.h>

int	ft_printf(const char *format, ...);

int	main(void)
{
	int	bytes, my_bytes = 0;

	bytes = printf("Hello %s\n", "Toto");
	printf("bytes = %i\n", bytes);
	my_bytes = ft_printf("Hello %s\n", "Toto");
	printf("bytes = %i\n", my_bytes);
	printf("- - - - - - - - - - - - - - - - - - - -\n");

	bytes = 0; 
	my_bytes = 0;
	bytes = printf("Magic %s is %d\n", "number", -42);
	printf("bytes = %i\n", bytes);
	my_bytes = ft_printf("Magic %s is %d\n", "number", -42);
	printf("bytes = %i\n", my_bytes);
	printf("- - - - - - - - - - - - - - - - - - - -\n");

	bytes = 0; 
	my_bytes = 0;
	bytes = printf("Hexadecimal %%d is %% %x\n", INT_MAX);
	printf("bytes = %i\n", bytes);
	my_bytes = ft_printf("Hexadecimal %%d is %% %x\n",  INT_MAX);
	printf("bytes = %i\n", my_bytes);
	printf("- - - - - - - - - - - - - - - - - - - -\n");
}
