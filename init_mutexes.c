#include "philosophers.h"

static int	init_print_mutex(t_data *data);

int	init_mutexes(t_data *data)
{
	int	i;

	data->cutlery = malloc(sizeof(pthread_mutex_t *) * data->total_number_of_p);
	if (!data->cutlery)
	{
		write(2, "Error: malloc cutlery\n", 22);
		return (ERROR);
	}
	i = 0;
	while (i < data->total_number_of_p)
	{
		data->cutlery[i] = malloc(sizeof(pthread_mutex_t));
		if (!data->cutlery[i])
		{
			write(2, "Error: malloc cutlery\n", 22);
			return (ERROR);
		}
		pthread_mutex_init(data->cutlery[i], NULL);
		i++;
	}
	if (init_print_mutex(data) == ERROR)
		return (ERROR);
	return (OK);
}

static int	init_print_mutex(t_data *data)
{
	data->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!data->print_mutex)
	{
		write(2, "Error: malloc print_mutex\n", 26);
		return (ERROR);
	}
	pthread_mutex_init(data->print_mutex, NULL);
	return (OK);
}
