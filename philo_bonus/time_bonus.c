#include "philosophers_bonus.h"

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(long long current_time, long long chill)
{
	long long	start_time;

	start_time = current_time;
	while (current_time < start_time + chill)
	{
		usleep(50);
		current_time = ft_get_time();
	}
}
