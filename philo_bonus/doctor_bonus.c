#include "philosophers_bonus.h"

static void	*doctor(void *arg);

void	create_doctor(t_data *data)
{
	pthread_t dr;

	if (pthread_create(&dr, NULL, &doctor, (void *) data) != 0)
	{
		write(2, "Error: creating doctor thread\n", 30);
		exit(1);
	}
	pthread_detach(dr);
}

static void	*doctor(void * arg)
{
	t_data		*data;
	long long	current_time;

	data = (t_data *)arg;
	while(1)
	{
		usleep(50);
		current_time = ft_get_time();
		// printf("\n%i %lld\n", data->philosopher, current_time - data->time_last_eaten);
		if (data->time_to_die < current_time - data->time_last_eaten)
			protected_print(data, "died\n");
	}
	return (NULL);
}