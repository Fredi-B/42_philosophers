#include "philosophers.h"

static int	doctor_sleeps(t_data *philosopher);
static void	philosopher_died(t_data **philosophers, \
								long long current_time, int i);

void	*doctor(void *arg)
{
	t_data		**philosophers;
	long long	current_time;
	long long	time_passed;
	int			i;
	int			flag;

	philosophers = (t_data **)arg;
	i = doctor_sleeps(philosophers[0]);
	flag = FALSE;
	while (1)
	{
		current_time = get_time();
		pthread_mutex_lock(philosophers[i]->eaten_mutex);
		time_passed = (current_time - *philosophers[i]->time_last_eaten);
		pthread_mutex_unlock(philosophers[i]->eaten_mutex);
		if (time_passed >= philosophers[i]->time_to_die)
		{
			philosopher_died(philosophers, current_time, i);
			break ;
		}
		i++;
		pthread_mutex_lock(philosophers[0]->enough_mutex);
		if (*philosophers[0]->enough_meals == \
				philosophers[0]->total_number_of_p)
				flag = TRUE;
		pthread_mutex_unlock(philosophers[0]->enough_mutex);
		if (flag == TRUE)
			break ;
		if (i == philosophers[0]->total_number_of_p)
			i = 0;
	}
	return (OK);
}

static int	doctor_sleeps(t_data *philosopher)
{
	if (philosopher->total_number_of_p > 30)
		usleep(philosopher->time_to_die * 500);
	else
		usleep(philosopher->time_to_die * 500);
	return (0);
}

static void	philosopher_died(t_data **philosophers, \
								long long current_time, int i)
{
	pthread_mutex_lock(philosophers[0]->enough_mutex);
	*philosophers[0]->died = TRUE;
	pthread_mutex_unlock(philosophers[0]->enough_mutex);
	usleep(50);
	pthread_mutex_lock(philosophers[0]->start_mutex);
	printf("%lli %i died\n", (current_time - \
		*philosophers[i]->start_time), philosophers[0]->philosopher);
	pthread_mutex_unlock(philosophers[0]->start_mutex);
}
