#include "philosophers.h"

static void	copy_data(t_data *data, t_data *philosopher, int i);

int	init_threads(t_data *data)
{
	t_data		**philosopher;
	pthread_t	**thread;
	int			i;

	philosopher = malloc(sizeof(t_data *) * data->total_number_of_p);
	thread = malloc(sizeof(pthread_t *) * data->total_number_of_p + 1);
	if (!philosopher || !thread)
		err_exit(data, 4, "Error: malloc philosopher || thread\n", 36);
	i = 0;
	while (i < data->total_number_of_p)
	{
		philosopher[i] = malloc(sizeof(t_data));
		thread[i] = malloc(sizeof(pthread_t));
		if (!philosopher || !thread)
			err_exit(data, 5, "Error: malloc philosopher[i] || thread[i]\n", 42);
		copy_data(data, philosopher[i], i);
		if (pthread_create(thread[i], NULL, &routine, philosopher[i]) != 0)
			err_exit(data, 6, "Error: create threads\n", 22);
		i++;
	}
	// doctor thread to check if everyone is still alive
	thread[i] = malloc(sizeof(pthread_t));
	if (!philosopher || !thread)
		err_exit(data, 6, "Error: malloc thread[i]\n", 24);
	i = 0;
	while (i < data->total_number_of_p)
	{
		if (pthread_join(*thread[i], NULL) != 0)
			err_exit(data, 7, "Error: join threads\n", 20);
		i++;
	}
	return (OK);
}

static void	copy_data(t_data *data, t_data *philosopher, int i)
{
	philosopher->total_number_of_p = data->total_number_of_p;
	philosopher->cnt_number_of_p = 0;
	philosopher->time_to_die = data->time_to_die;
	philosopher->time_to_eat = data->time_to_eat;
	philosopher->time_to_sleep = data->time_to_sleep;
	philosopher->number_of_meals = data->number_of_meals;
	philosopher->total_time = 0;
	philosopher->cutlery = data->cutlery;
	philosopher->philosopher = i + 1;
	philosopher->left_fork = data->cutlery[i];
	if (i != data->total_number_of_p)
		philosopher->right_fork = data->cutlery[i + 1];
	else
		philosopher->right_fork = data->cutlery[0];
	philosopher->time_last_eaten = 0;
}
