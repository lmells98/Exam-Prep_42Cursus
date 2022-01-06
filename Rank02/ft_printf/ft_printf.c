#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

static void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static int	print_string(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

static unsigned int	get_u_len_base(unsigned int nb, int base)
{
	unsigned int	len;

	len = 0;
	while (nb != 0)
	{
		len += 1;
		nb /= base;
	}
	if (nb == 0 && len == 0)
		len += 1;
	return (len);
}

static char	*u_itoa(unsigned int nb, int nb_len, int sign)
{
	int		i;
	char	*array;

	array = (char *)malloc((nb_len + 1) * sizeof(char));
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
		i--;
		nb /= 10;
	}
	array[nb_len] = '\0';
	return (array);
}

static int	print_decimal(int nb)
{
	int				bytes;
	int				sign;
	char			*decimal;
	unsigned int	nb_len;
	
	bytes = 0;
	sign = 0;
	nb_len = get_u_len_base(nb, 10);
	if (nb < 0)
	{
		sign = 1;
		nb_len += 1;
	}
	decimal = u_itoa(nb, nb_len, sign);
	bytes += print_string(decimal);
	ft_free(&decimal);
	return (bytes);
}

static int	print_hex(unsigned int nb)
{
	int				bytes;
	char			*output;
	unsigned int	hex_len;

	bytes = 0;
	hex_len = get_u_len_base(nb, 16);
	output = (char *)malloc((hex_len + 1) * sizeof(char));
	if (!output)
		return (0);
	while ((unsigned)bytes < hex_len)
	{
		output[bytes] = '0';
		bytes++;
	}
	bytes -= 1;
	while (nb != 0)
	{
		output[bytes] = "0123456789abcdef"[nb % 16];
		bytes--;
		nb /= 16;
	}
	output[hex_len] = '\0';
	bytes = print_string(output);
	ft_free(&output);
	return (bytes);
}

static int	do_conversion(const char *format, va_list argp)
{
	int	bytes;

	format++;
	bytes = 0;
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
