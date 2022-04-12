#include "philosophers_bonus.h"

static const char	*isspacechar(const char *str);
static const char	*issign(const char *str, int *sign);
static int			ft_isdigit(int c);

int	ft_atoi(const char *str)
{
	size_t	i;
	long	nbr;
	int		sign;

	str = isspacechar(str);
	str = issign(str, &sign);
	nbr = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nbr <= 2147483648)
			nbr = nbr * 10 + str[i] - '0';
		else
			break ;
		i++;
	}
	if (nbr * sign > 2147483647)
		return (-1);
	if (nbr * sign < -2147483648)
		return (0);
	return (sign * nbr);
}

static const char	*isspacechar(const char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	return ((str));
}

static const char	*issign(const char *str, int *sign)
{
	int	i;

	*sign = 1;
	i = 0;
	if (*str == '-' || *str == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

int	ft_is_pos_int(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '+' && str[1])
		{
			i++;
			continue ;
		}
		if (ft_isdigit(str[i]) == FALSE || \
			(i == 9 && str[i] > '7') || i > 9)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	ft_isdigit(int c)
{
	if ((c < '0') || (c > '9'))
		return (FALSE);
	return (TRUE);
}
