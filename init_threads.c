#include "philosophers.h"

static void	copy_data(t_data *data, t_data *philosopher, int i);

int	init_threads(t_data *data)
{
	t_data		**philosopher;
	pthread_t	**thread;
	int			i;

	philosopher = malloc(sizeof(t_data *) * data->total_number_of_p);
	thread = malloc(sizeof(pthread_t *) * (data->total_number_of_p + 1));
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
	create_doctor_thread(data, philosopher, thread, i);
	join_threads(data, thread);
	free_philosopher_and_threads(data, philosopher, thread);
	return (OK);
}

static void	copy_data(t_data *data, t_data *philosopher, int i)
{
	philosopher->total_number_of_p = data->total_number_of_p;
	philosopher->cnt_number_of_p = data->cnt_number_of_p;
	philosopher->time_to_die = data->time_to_die;
	philosopher->time_to_eat = data->time_to_eat;
	philosopher->time_to_sleep = data->time_to_sleep;
	philosopher->number_of_meals = data->number_of_meals;
	philosopher->enough_meals = data->enough_meals;
	philosopher->start_time = data->start_time;
	philosopher->print_mutex = data->print_mutex;
	philosopher->cutlery = data->cutlery;
	philosopher->philosopher = i + 1;
	philosopher->left_fork = data->cutlery[i];
	if (philosopher->total_number_of_p == 1)
		philosopher->right_fork = NULL;
	else
	{
		if (i == data->total_number_of_p - 1)
			philosopher->right_fork = data->cutlery[0];
		else
			philosopher->right_fork = data->cutlery[i + 1];
	}
	philosopher->time_last_eaten = NULL;
	philosopher->times_eaten = data->times_eaten;
	philosopher->died = data->died;
}

static void	create_doctor_thread(t_data *data, \
				t_data **philosopher, pthread_t **thread, int i)
{
	thread[i] = malloc(sizeof(pthread_t));
	if (!thread[i])
		err_exit(data, 6, "Error: malloc thread[i]\n", 24);
	if (pthread_create(thread[i], NULL, &doctor, philosopher) != 0)
		err_exit(data, 6, "Error: create doctor thread\n", 28);
}

static void	join_threads(t_data *data, pthread_t **thread)
{
	int	i;

	i = 0;
	while (i < data->total_number_of_p + 1)
	{
		if (pthread_join(*thread[i], NULL) != 0)
			err_exit(data, 7, "Error: join threads\n", 20);
		i++;
	}
}
