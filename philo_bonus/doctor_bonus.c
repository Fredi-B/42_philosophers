#include "philosophers_bonus.h"

static void	*doctor(void *arg);

void	create_doctor(t_data *data)
{
	pthread_t *dr;

	data->time_last_eaten = malloc(sizeof(long long*));
	dr = malloc(sizeof(pthread_t));
	if (!data->time_last_eaten || !dr)
		kill(0, SIGINT);
	*data->time_last_eaten = data->start_time;
	pthread_create(dr, 0, doctor, data->time_last_eaten);
}

static void	*doctor(void * arg)
{
	long long	*time_last_eaten;

	time_last_eaten = (long long *)arg;
	
	return (NULL);
}