#include "philosophers.h"

void	sleep_and_think(t_data *philosopher)
{
	protected_print(philosopher, SLEEP);
	ft_sleep(philosopher->time_to_sleep);
	protected_print(philosopher, THINK);
	if (philosopher->total_number_of_p > 30)
		usleep(550);
	usleep(200);
}


void ft_sleep(unsigned long chill) 
{
	unsigned long start_time; 
	unsigned long current_time; 

	start_time = get_time();
	current_time = start_time;
	while (current_time <= start_time + chill)
	{ 
		current_time = get_time();
		usleep(20);
	}
}
