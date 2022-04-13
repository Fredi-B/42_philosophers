#include "philosophers_bonus.h"

static void	take_forks(t_data *data);

void	eat(t_data *data)
{
	take_forks(data);
	protected_print(data, "is eating\n");

}

static void	take_forks(t_data *data)
{
	sem_wait(data->cutlery_sem);
	protected_print(data, "has taken a fork\n");
	sem_wait(data->cutlery_sem);
	protected_print(data, "has taken a fork\n");
}
