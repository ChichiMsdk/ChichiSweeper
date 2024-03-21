#include "demineur.h"

#define MAX_SIZE_BUFFER_ITOA 20

static int	digit_counter(int n)
{
	int	i;

	i = 1;
	while (n >= 10 || n <= -10)
	{
			n /= 10;
			i++;
	}
	if (n < 0)
			i++;
	return (i);
}

char    *ft_itoa10(int n) // static size of 20 !
{
	static char	ptr[MAX_SIZE_BUFFER_ITOA];
	long		nbr;
	int			i;

	nbr = n;
	i = digit_counter(n);
	ptr[i] = '\0';
	if (!n)
			ptr[0] = '0';
	if (nbr < 0)
	{
			nbr = -nbr;
			ptr[0] = '-';
	}
	while (nbr)
	{
			ptr[--i] = nbr % 10 + '0';
			nbr /= 10;
	}
	return (ptr);
}

char    *ft_itoa(int n)
{
	char	*ptr;
	long	nbr;
	int		i;

	nbr = n;
	i = digit_counter(n);
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
			return (0);
	ptr[i] = '\0';
	if (!n)
			ptr[0] = '0';
	if (nbr < 0)
	{
			nbr = -nbr;
			ptr[0] = '-';
	}
	while (nbr)
	{
			ptr[--i] = nbr % 10 + '0';
			nbr /= 10;
	}
	return (ptr);
}

void	debug(c_square ptr[NUMBER_Y][NUMBER_X])
{
	int x = 0; int y = 0;

	while (y < NUMBER_Y)
	{
		x = 0;
		while (x < NUMBER_X)
		{
 			printf("x=%f y=%f, type= %d, clicked= %d\n",
					ptr[x][y].dimensions.x, ptr[x][y].dimensions.y,
					ptr[x][y].type, ptr[x][y].clicked);
			x++;
		}
		y++; 
	}
}
