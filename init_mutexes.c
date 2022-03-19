#include "philosophers.h"

int	init_mutexes(t_data *data)
{
	int	i;

	data->cutlery = malloc(sizeof(pthread_mutex_t) * data->total_number_of_p);
	if (!data->cutlery)
	{
		write(2, "Error: malloc cutlery\n", 22);
		return (ERROR);
	}
	i = 0;
	//while (i < data->total_number_of_p)
	//{
		//malloc mutexes[i]
		//init_mutex()
	//}
	return (OK);
}