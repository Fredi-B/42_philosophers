#include "philosophers.h"

void	sleep_and_think(t_data *philosopher)
{
	unsigned long	current_time;
	long			time_passed;

	protected_print(philosopher, SLEEP);
	current_time = get_time();
	*philosopher->runtime = current_time - *philosopher->start_time;
	time_passed = (current_time - *philosopher->time_last_eaten);
	if (time_passed + philosopher->time_to_sleep >= philosopher->time_to_die)
	{
		while (*philosopher->died != TRUE)
			usleep(20);
	}
	else
		ft_sleep(philosopher->time_to_sleep);
	protected_print(philosopher, THINK);
	if (philosopher->total_number_of_p > 30)
		usleep(550);
	usleep(200);
}

void	ft_sleep(unsigned long chill)
{
	unsigned long	start_time;
	unsigned long	current_time;

	start_time = get_time();
	current_time = start_time;
	while (current_time <= start_time + chill)
	{
		current_time = get_time();
		usleep(20);
	}
}
