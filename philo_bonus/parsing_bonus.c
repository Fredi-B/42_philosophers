#include "philosophers_bonus.h"

static void	get_data(t_data *data, int argc, char **argv);
static int	check_input(int argc, char **argv);

int	parsing(t_data *data, int argc, char **argv)
{
	if (check_input(argc, argv) == ERROR)
		return (ERROR);
	get_data(data, argc, argv);
	if (data->total_number_of_p == 0 || data->number_of_meals == 0)
	{
		write(2, "Error: wrong argument\n", 22);
		return (ERROR);
	}
	return (OK);
}

static int	check_input(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		return (ERROR);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_is_pos_int(argv[i]) == FALSE)
		{
			write(2, "Error: wrong argument\n", 22);
			return (ERROR);
		}
		i++;
	}
	return (OK);
}

static void	get_data(t_data *data, int argc, char **argv)
{
	data->total_number_of_p = ft_atoi(argv[1]);
	data->time_to_die = (long long)ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	else
		data->number_of_meals = -1;
	data->start_time = 0;
	data->philosopher = 0;
	data->time_last_eaten = 0;
	data->times_eaten = 0;
}
