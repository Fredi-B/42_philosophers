
#include "philosophers.h"

static int	one_philosopher(t_data *philosopher);
static void	wait_for_all_philosophers(t_data *philosopher);

void	*routine(void *arg)
{
	t_data	*philosopher;

	philosopher = (t_data *)arg;
	// to do: free philosopher[i]->time_last_eaten --> check
	philosopher->time_last_eaten = malloc(sizeof(long long));
	if (!philosopher->time_last_eaten)
	{
		write(2, "Error: philosopher->time_last_eaten\n", 36);
		return (0);
	}
	*philosopher->time_last_eaten = 0;
	wait_for_all_philosophers(philosopher);
	if (one_philosopher(philosopher) == TRUE)
		return (0);
	while (*philosopher->enough_meals != philosopher->total_number_of_p \
			&& *philosopher->died == FALSE)
	{
		eat(philosopher);
		sleep_and_think(philosopher);
	}
	free(philosopher->time_last_eaten);
	return (0);
}

static void	wait_for_all_philosophers(t_data *philosopher)
{
	pthread_mutex_lock(philosopher->print_mutex);
	*philosopher->cnt_number_of_p = *philosopher->cnt_number_of_p + 1;
	pthread_mutex_unlock(philosopher->print_mutex);
	while (*philosopher->cnt_number_of_p != philosopher->total_number_of_p)
		usleep(50);
	if (philosopher->philosopher == philosopher->total_number_of_p)
		*philosopher->start_time = get_time();
	else
		usleep(philosopher->total_number_of_p * 2);
	*philosopher->time_last_eaten = *philosopher->start_time;
	if (philosopher->philosopher % 2)
		usleep(philosopher->time_to_eat * 300);
}

void	protected_print(t_data *philosopher, char *action, int state)
{
	long long	current_time;
	long long	runtime;

	pthread_mutex_lock(philosopher->print_mutex);
	current_time = get_time();
	runtime = current_time - *philosopher->start_time;
	if (*philosopher->enough_meals == philosopher->total_number_of_p \
		|| *philosopher->died == TRUE)
		exit(0);
	if (state == EAT)
	{
		if (philosopher->times_eaten == philosopher->number_of_meals)
			(*philosopher->enough_meals)++;
		*philosopher->time_last_eaten = current_time;
	}
	printf("%lli %i %s", runtime, philosopher->philosopher, action);
	pthread_mutex_unlock(philosopher->print_mutex);
}

static int	one_philosopher(t_data *philosopher)
{
	if (philosopher->total_number_of_p == 1)
	{
		pthread_mutex_lock(philosopher->left_fork);
		protected_print(philosopher, "has taken left fork\n", L_FORK);
		while (*philosopher->died != TRUE)
			usleep(20);
		return (TRUE);
	}
	return (FALSE);
}
