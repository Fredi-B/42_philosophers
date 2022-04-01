#include "philosophers.h"

static void	update_runtime(t_data *philosopher);

void	*doctor(void *arg)
{
	t_data			**philosophers;
	unsigned long	current_time;
	long			time_passed;
	int				i;

	philosophers = (t_data **)arg;
	update_runtime(philosophers[1]);
	usleep(philosophers[1]->time_to_die * 900);
	i = 0;
	while (1)
	{
		*philosophers[1]->runtime = get_time() - *philosophers[1]->start_time;
		current_time = get_time();
		time_passed = (current_time - *philosophers[i]->time_last_eaten);
		if (time_passed > philosophers[i]->time_to_die)
		{
			protected_print(philosophers[i], DIED);
			*philosophers[i]->died = TRUE;
			printf("time passed %li\n", time_passed);
			printf("%i time last eaten %li\n", philosophers[i]->philosopher, *philosophers[i]->time_last_eaten - *philosophers[1]->start_time);
			break ;
		}
		i++;
		if (i == philosophers[1]->total_number_of_p)
			i = 0;
	}
	return (OK);
}

static void	update_runtime(t_data *philosopher)
{
	unsigned long	start_time;

	usleep(philosopher->total_number_of_p * 100);
	*philosopher->runtime = get_time() - *philosopher->start_time;
	start_time = *philosopher->runtime;
	while (*philosopher->runtime < start_time + (philosopher->time_to_die / 2))
	{
		*philosopher->runtime = get_time() - *philosopher->start_time;
		usleep(10);
	}
}
