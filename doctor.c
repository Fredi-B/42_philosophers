#include "philosophers.h"

static void	doctor_sleeps(t_data *philosopher);

void	*doctor(void *arg)
{
	t_data		**philosophers;
	long long	current_time;
	long long	time_passed;
	int			i;

	philosophers = (t_data **)arg;
	doctor_sleeps(philosophers[0]);
	i = 0;
	while (1)
	{
		current_time = get_time();
		time_passed = (current_time - *philosophers[i]->time_last_eaten);
		if (time_passed >= philosophers[i]->time_to_die)
		{
			protected_print(philosophers[i], "died\n", DIED);
			*philosophers[i]->died = TRUE;
			printf("time passed %lli\n", time_passed);
			printf("%i time last eaten %lli\n", philosophers[i]->philosopher, *philosophers[i]->time_last_eaten - *philosophers[0]->start_time);
			break ;
		}
		i++;
		if (*philosophers[0]->enough_meals == philosophers[0]->number_of_meals)
			break;
		if (i == philosophers[0]->total_number_of_p)
			i = 0;
	}
	return (OK);
}

static void	doctor_sleeps(t_data *philosopher)
{
	if (philosopher->total_number_of_p > 30)
		usleep(philosopher->time_to_die * 500);
	else
		usleep(philosopher->time_to_die * 500);
}
