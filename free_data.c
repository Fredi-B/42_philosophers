#include "philosophers.h"

static void	free_mutexes(t_data *data);

void	free_data(t_data *data)
{
	free_mutexes(data);
	free(data->cnt_number_of_p);
	free(data->start_time);
	free(data->enough_meals);
	free(data->died);
}

static void	free_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_number_of_p)
	{
		pthread_mutex_destroy(data->cutlery[i]);
		free(data->cutlery[i]);
		data->cutlery[i] = NULL;
		i++;
	}
	free(data->cutlery);
	data->cutlery = NULL;
	pthread_mutex_destroy(data->print_mutex);
	free(data->print_mutex);
	data->print_mutex = NULL;
}

/* frees everything needed. prints out error message */
void	err_exit(t_data *data, int exit_status, char *msg, int len)
{
	write(STDERR_FILENO, msg, len);
	free_data(data);
	exit(exit_status);
}
