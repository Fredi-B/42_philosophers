#include "philosophers.h"

void	sleep_and_think(t_data *philosopher)
{
	protected_print(philosopher, SLEEP);
	usleep(philosopher->time_to_sleep * 1000);
	protected_print(philosopher, THINK);
	if (philosopher->total_number_of_p > 30)
		usleep(650);
	usleep(200);
}
