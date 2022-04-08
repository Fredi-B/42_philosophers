#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		current_time;

	gettimeofday(&tv, NULL);
	current_time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (current_time);
}
