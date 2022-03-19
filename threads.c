#include "philosophers.h"

void	*test(void *ptr)
{
	t_data *data;

	data = (t_data *) ptr;
	pthread_mutex_lock(data->mutex1);
	data->cnt_p++;
	printf("cnt %i\n", data->cnt_p);
	pthread_mutex_unlock(data->mutex1);
	return (0);
}

int	threads(void)
{
	pthread_t	p[10];
	int	*i;
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	data->mutex1 = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->mutex1, NULL);
	i = malloc(sizeof(int));
	*i = 0;
	data->cnt_p = 0;
	while (*i < 10)
	{
		pthread_create(p + *i, NULL, test, data);
		(*i)++;
	}
	*i = 0;
	while (*i < 10)
	{
		if (pthread_join(p[*i], NULL) != 0)
			dwrite (aaaaahhhh);
		(*i)++;
	}
	return (0);
}
