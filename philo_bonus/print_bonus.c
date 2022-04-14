#include "philosophers_bonus.h"

long long	protected_print(t_data *data, char *action)
{
	long long	current_time;
	long long	runtime;

	current_time = ft_get_time();
	runtime = current_time - data->start_time;
	printf("%lli %i %s", runtime, data->philosopher, action);
	return (current_time);
}