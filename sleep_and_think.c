#include "philosophers.h"

void	sleep_and_think(t_data *philosopher)
{
	protected_print(philosopher, SLEEP);
	usleep(philosopher->time_to_sleep);
	protected_print(philosopher, THINK);
}

