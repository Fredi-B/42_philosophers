#include "philosophers.h"

static int	one_philosopher(t_data *philosopher);
static void	wait_for_all_philosophers(t_data *philosopher);

void	*routine(void *arg)
{
	t_data	*philosopher;
	int		ate_enough;
	int		someone_died;

	philosopher = (t_data *)arg;
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
	ate_enough = FALSE;
	someone_died = FALSE;
	while (ate_enough == FALSE && someone_died == FALSE)
	{
		eat(philosopher);
		sleep_and_think(philosopher);
		pthread_mutex_lock(philosopher->enough_mutex);
		if (*philosopher->enough_meals >= philosopher->total_number_of_p)
			ate_enough = TRUE;
		if (*philosopher->died == TRUE)
			someone_died = TRUE;
		pthread_mutex_unlock(philosopher->enough_mutex);
	}
	return (0);
}

static void	wait_for_all_philosophers(t_data *philosopher)
{
	int	flag;

	flag = FALSE;
	pthread_mutex_lock(philosopher->print_mutex);
	*philosopher->cnt_number_of_p = *philosopher->cnt_number_of_p + 1;
	pthread_mutex_unlock(philosopher->print_mutex);
	while (1)
	{
		pthread_mutex_lock(philosopher->print_mutex);
		if (*philosopher->cnt_number_of_p >= philosopher->total_number_of_p)
			flag = TRUE;
		pthread_mutex_unlock(philosopher->print_mutex);
		if (flag == TRUE)
			break ;
	}
	if (philosopher->philosopher == 1)
		*philosopher->start_time = get_time();
	else if (philosopher->total_number_of_p < 8)
		usleep(philosopher->total_number_of_p * 30);
	else if (philosopher->total_number_of_p < 30)
		usleep(philosopher->total_number_of_p * 15);
	else if (philosopher->total_number_of_p < 170)
		usleep(philosopher->total_number_of_p * 3);
	else
		usleep(philosopher->total_number_of_p);
	pthread_mutex_lock(philosopher->eaten_mutex);
	pthread_mutex_lock(philosopher->start_mutex);
	*philosopher->time_last_eaten = *philosopher->start_time;
	pthread_mutex_unlock(philosopher->eaten_mutex);
	pthread_mutex_unlock(philosopher->start_mutex);
	if (philosopher->philosopher % 2 && philosopher->total_number_of_p != 1)
		usleep(philosopher->time_to_eat * 100);
}

void	protected_print(t_data *philosopher, char *action, int state)
{
	long long	current_time;
	long long	runtime;

	pthread_mutex_lock(philosopher->print_mutex);
	current_time = get_time();
	runtime = current_time - *philosopher->start_time;
	pthread_mutex_lock(philosopher->enough_mutex);
	if (*philosopher->enough_meals < philosopher->total_number_of_p \
			&& *philosopher->died == FALSE)
		printf("%lli %i %s", runtime, philosopher->philosopher, action);
	pthread_mutex_unlock(philosopher->enough_mutex);
	pthread_mutex_unlock(philosopher->print_mutex);
	if (state == EAT)
	{
		if (philosopher->times_eaten == philosopher->number_of_meals)
		{
			pthread_mutex_lock(philosopher->enough_mutex);
			(*philosopher->enough_meals)++;
			pthread_mutex_unlock(philosopher->enough_mutex);
		}
		pthread_mutex_lock(philosopher->eaten_mutex);
		*philosopher->time_last_eaten = current_time;
		pthread_mutex_unlock(philosopher->eaten_mutex);
	}
}

static int	one_philosopher(t_data *philosopher)
{
	if (philosopher->total_number_of_p == 1)
	{
		pthread_mutex_lock(philosopher->left_fork);
		protected_print(philosopher, "has taken a fork\n", FORK);
		while (*philosopher->died != TRUE)
			usleep(20);
		return (TRUE);
	}
	return (FALSE);
}
