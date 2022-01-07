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
	int	bytes;

	bytes = 0;
	while (str[bytes] != '\0')
		write(1, &str[bytes++], 1);
	return (bytes);
}

static int	get_digits_base(unsigned int nb, int neg, int base)
{
	int	digits;

	digits = 0;
	if (nb == 0)
		digits++;
	while (nb != 0)
	{
		digits++;
		nb /= base;
	}
	return (neg + digits);
}

static char	*u_itoa(unsigned int nb, int neg, int size)
{
	int		i;
	char	*arr;

	arr = (char *)malloc((size + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	i = 0;
	if (neg)
	{
		arr[i] = '-';
		i++;
	}
	while (i < size)
		arr[i++] = '0';
	arr[i] = '\0';
	i -= 1;
	while (nb != 0)
	{
		arr[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (arr);
}

static int	print_decimal(int nb)
{
	int		neg;
	int		size;
	int		bytes;
	char	*decimal;

	decimal = NULL;
	neg = 0;
	bytes = 0;
	if (nb < 0)
	{
		nb *= -1;
		neg = 1;
	}
	size = get_digits_base(nb, neg, 10);
	decimal = u_itoa(nb, neg, size);
	bytes += print_string(decimal);
	ft_free(&decimal);
	return (bytes);
}

static int	print_hex(unsigned int nb)
{
	int		size;
	int		bytes;
	char	*hex_str;

	hex_str = NULL;
	size = get_digits_base(nb, 0, 16);
	hex_str = (char *)malloc((size + 1) * sizeof(char));
	if (!hex_str)
		hex_str = NULL;
	bytes = 0;
	while (bytes < size)
		hex_str[bytes++] = '0';
	hex_str[bytes] = '\0';
	bytes -= 1;
	while (nb != 0)
	{
		hex_str[bytes--] = "0123456789abcdef"[nb % 16];
		nb /= 16;
	}
	bytes = print_string(hex_str);
	ft_free(&hex_str);
	return (bytes);
}

static int	do_conversion(va_list argp, const char *format)
{
	int	bytes;

	bytes = 0;
	format++;
	if (*format == 's')
		bytes += print_string(va_arg(argp, char *));
	else if (*format == 'd')
		bytes += print_decimal(va_arg(argp, int));
	else if (*format == 'x')
		bytes += print_hex(va_arg(argp, unsigned int));
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
				bytes += do_conversion(argp, format);
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
