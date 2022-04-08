#include "philosophers.h"

static int	doctor_sleeps(t_data *philosopher);

void	*doctor(void *arg)
{
	t_data		**philosophers;
	long long	current_time;
	long long	time_passed;
	int			i;

	philosophers = (t_data **)arg;
	i = doctor_sleeps(philosophers[0]);
	while (1)
	{
		current_time = get_time();
		time_passed = (current_time - *philosophers[i]->time_last_eaten);
		if (time_passed >= philosophers[i]->time_to_die)
		{
			protected_print(philosophers[i], "died\n", DIED);
			*philosophers[i]->died = TRUE;
			break ;
		}
		i++;
		if (*philosophers[0]->enough_meals == \
				philosophers[0]->total_number_of_p)
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
