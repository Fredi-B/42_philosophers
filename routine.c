#include "philosophers.h"

static void	wait_for_all_philosophers(t_data *philosopher);

void	*routine(void *arg)
{
	t_data	*philosopher;

	philosopher = (t_data *)arg;
	// to do: free philosopher[i]->time_last_eaten
	philosopher->time_last_eaten = malloc(sizeof(unsigned long));
	if (!philosopher->time_last_eaten)
	{
		write(2, "Errorphilosopher->time_last_eaten\n", 34);
		return (0);
	}
	*philosopher->time_last_eaten = 0;
	wait_for_all_philosophers(philosopher);
	while (*philosopher->enough_meals != philosopher->total_number_of_p \
			&& *philosopher->died == FALSE)
	{
		eat(philosopher);
		sleep_and_think(philosopher);
	}
	return (0);
}

static void	wait_for_all_philosophers(t_data *philosopher)
{
	struct timeval	start_time;

	pthread_mutex_lock(philosopher->print_mutex);
	*philosopher->cnt_number_of_p = *philosopher->cnt_number_of_p + 1;
	pthread_mutex_unlock(philosopher->print_mutex);
	while (*philosopher->cnt_number_of_p != philosopher->total_number_of_p)
		usleep(50);
	if (philosopher->philosopher == philosopher->total_number_of_p)
	{
		gettimeofday(&start_time, NULL);
		*philosopher->start_time = (start_time.tv_sec * 1000) \
									+ (start_time.tv_usec / 1000);
	}
	else
		usleep(500);
	*philosopher->time_last_eaten = *philosopher->start_time;
	if (philosopher->philosopher % 2)
		usleep(200);
}

void	protected_print(t_data *philosopher, int state)
{
	struct timeval	tv;
	unsigned long	runtime;

	pthread_mutex_lock(philosopher->print_mutex);
	gettimeofday(&tv, NULL);
	runtime = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) \
				- *philosopher->start_time;
	if (*philosopher->enough_meals == philosopher->total_number_of_p \
		|| *philosopher->died == TRUE)
		exit(0);
	// to do: change to "has taken a fork"
	if (state == L_FORK)
		printf("%li %i has taken left fork\n", runtime, philosopher->philosopher);
	if (state == R_FORK)
		printf("%li %i has taken right fork\n", runtime, philosopher->philosopher);
	else if (state == EAT)
	{
		philosopher->times_eaten++;
		if (philosopher->times_eaten == philosopher->number_of_meals)
			(*philosopher->enough_meals)++;
		printf("%li %i is eating\n\n", runtime, philosopher->philosopher);
	}
	else if (state == SLEEP)
		printf("%li %i is sleeping\n", runtime, philosopher->philosopher);
	else if (state == THINK)
		printf("%li %i is thinking\n", runtime, philosopher->philosopher);
	else if (state == DIED)
		printf("%li %i died\n", runtime, philosopher->philosopher);
	pthread_mutex_unlock(philosopher->print_mutex);
}