#include "philosophers_bonus.h"

long long	protected_print(t_data *data, char *action)
{
	long long	current_time;
	long long	runtime;
	int			someone_died;

	someone_died = FALSE;
	if (ft_strncmp(action, "died\n", 5) == 0)
		someone_died = TRUE;
	current_time = ft_get_time();
	runtime = current_time - data->start_time;
	sem_wait(data->print_sem);
	printf("%lli %i %s", runtime, data->philosopher, action);
	if (someone_died == TRUE)
		kill(0, SIGINT);
	else
		sem_post(data->print_sem);
	return (current_time);
}
