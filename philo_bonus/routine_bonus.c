#include "philosophers_bonus.h"

void	routine(t_data *data)
{
	sem_wait(data->wait_for_children);
	sem_post(data->wait_for_children);
}