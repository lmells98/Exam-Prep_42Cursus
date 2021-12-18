#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

static void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static void	*ft_calloc(size_t membs, size_t size)
{
	char	*output;
	size_t	i;
	size_t	bytes;

	if (!(membs || size))
		return (NULL);
	bytes = membs * size;
	output = malloc(bytes);
	if (!output)
		return (NULL);
	i = 0;
	while (i < bytes)
	{
		output[i] = '0';
		i++;
	}
	output[bytes] = '\0';
	return (output);
}

static int	print_string(char *str)
{
	int	bytes;

	if (!str)
		return (0);
	bytes = 0;
	while (str[bytes] != '\0')
	{
		write(1, &str[bytes], 1);
		bytes++;
	}
	return (bytes);
}

static size_t	get_nb_len_base(unsigned int nb, unsigned int sign, int base)
{
	unsigned int	len;

	len = 0;
	if (sign)
		len += 1;
	while (nb != 0)
	{
		len += 1;
		nb /= base;
	}
	return (len);
}

static char	*u_itoa(unsigned int nb, unsigned int sign)
{
	unsigned int	nb_len;
	unsigned int	i;
	char	*array;

	nb_len = get_nb_len_base(nb, sign, 10);
	array = (char *)ft_calloc(nb_len + 1, sizeof(char));
	if (!array)
		return (NULL);
	i = 0;
	while (i < nb_len)
	{
		array[i] = '0';
		i++;
	}
	if (sign)
		array[0] = '-';
	i -= 1;
	while (nb != 0)
	{
		array[i] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
	array[nb_len] = '\0';
	return (array);
}

static int	print_decimal(int nb)
{
	int	sign;
	int	bytes;
	char	*output;

	output = NULL;
	bytes = 0;
	sign = 0;
	if (nb < 0)
	{
		sign = 1;
		nb *= -1;
	}
	output = u_itoa(nb, sign);
	bytes += print_string(output);
	ft_free(&output);
	return (bytes);
}

static int	print_hex(unsigned int nb)
{
	unsigned int	bytes;
	char	*hex_l;
	char	*array;
	size_t	nb_len;

	bytes = 0;
	nb_len = get_nb_len_base(nb, 0, 16);
	array = (char *)ft_calloc(nb_len + 1, sizeof(char));
	if (!array)
		return (0);
	while (bytes < nb_len)
	{
		array[bytes] = '0';
		bytes++;
	}
	bytes -= 1;
	hex_l = "0123456789abcdef";
	while (nb != 0)
	{
		array[bytes] = hex_l[nb % 16];
		nb /= 16;
		bytes--;
	}
	array[nb_len] = '\0';
	bytes = print_string(array);
	ft_free(&array);
	return (bytes);
}

static int	do_conversion(const char *format, va_list argp)
{
	int	bytes;

	bytes = 0;
	format++;
	if (*format)
	{
		if (*format == 's')
			bytes += print_string(va_arg(argp, char *));
		else if (*format == 'd')
			bytes += print_decimal(va_arg(argp, int));
		else if (*format == 'x')
			bytes += print_hex(va_arg(argp, unsigned int));
		else if (*format == '%')
		{
			write(1, "%", 1);
			bytes += 1;
		}
		return (bytes);
	}
	return (bytes);
}

int	ft_printf(const char *format, ...)
{
	int		bytes;
	va_list	argp;

	bytes = 0;
	va_start(argp, format);
	{
		while (*format != '\0')
		{
			if (*format == '%')
			{
				bytes += do_conversion(format, argp);
				format++;
			}
			else
			{
				write(1, format, 1);
				bytes += 1;
			}
			format++;
		}
	}
	va_end(argp);
	return (bytes);
}
