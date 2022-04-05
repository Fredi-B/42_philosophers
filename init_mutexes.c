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
	// to do: free data->cnt_number_of_p
	data->cnt_number_of_p = malloc(sizeof(int));
	if (!data->cnt_number_of_p)
	{
		write(2, "Error: malloc cnt_number_of_p\n", 30);
		return (ERROR);
	}
	*data->cnt_number_of_p = 0;
	// to do: free data->start_time
	data->start_time = malloc(sizeof(long long));
	if (!data->start_time)
	{
		write(2, "Error: malloc start_time\n", 25);
		return (ERROR);
	}
	*data->start_time = 0;
	// to do: free data->enough_meals
	data->enough_meals = malloc(sizeof(int));
	if (!data->enough_meals)
	{
		write(2, "Error: malloc enough_meals\n", 27);
		return (ERROR);
	}
	*data->enough_meals = 0;
	// to do: free data->died
	data->died = malloc(sizeof(int));
	if (!data->died)
	{
		write(2, "Error: malloc died\n", 19);
		return (ERROR);
	}
	*data->died = FALSE;
	return (OK);
}
