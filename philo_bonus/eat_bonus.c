#include "philosophers_bonus.h"

static void	take_forks(t_data *data);
static void	put_forks(t_data *data);

void	eat(t_data *data)
{
	take_forks(data);
	data->time_last_eaten = protected_print(data, "is eating\n");
	create_doctor(data);
	ft_sleep(data->time_last_eaten, data->time_to_eat);
	data->times_eaten++;
	put_forks(data);
	if (data->times_eaten == data->number_of_meals)
		exit(0);
}

static void	take_forks(t_data *data)
{
	sem_wait(data->cutlery_sem);
	protected_print(data, "has taken a fork\n");
	sem_wait(data->cutlery_sem);
	protected_print(data, "has taken a fork\n");
}

static void	put_forks(t_data *data)
{
	sem_post(data->cutlery_sem);
	sem_post(data->cutlery_sem);
}
