#include "philosophers_bonus.h"

static int	one_philosopher(t_data *data);
static void	eat_sleep_repeat(t_data *data);

void	routine(t_data *data)
{
	sem_wait(data->wait_for_children);
	sem_post(data->wait_for_children);
	data->start_time = ft_get_time();
	data->time_last_eaten = data->start_time;
	if (one_philosopher(data) == TRUE)
		exit(0);
	if (data->philosopher % 2 && data->total_number_of_p != 1)
		usleep(data->time_to_eat * 100);
	eat_sleep_repeat(data);
}

static void	eat_sleep_repeat(t_data *data)
{
	while (1)
	{
		eat(data);
	}
static int	one_philosopher(t_data *data)
{
	long long	current_time;

	if (data->total_number_of_p == 1)
	{
		sem_wait(data->cutlery_sem);
		current_time = protected_print(data, "has taken a fork\n");
		ft_sleep(current_time, data->time_to_die);
		protected_print(data, "died\n");
		return (TRUE);
	}
	return (FALSE);
}