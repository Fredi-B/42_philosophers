#include "philosophers.h"

void	*doctor(void *arg)
{
	t_data			**philosophers;
	unsigned long	current_time;
	long			time_passed;
	int				i;

	philosophers = (t_data **)arg;
	current_
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
