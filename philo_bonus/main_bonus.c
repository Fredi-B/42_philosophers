#include "philosophers_bonus.h"

static void	create_philosophers(t_data *data);

int	main(int argc, char **argv)
{
	t_data			data;
	struct timeval	tv;


	if (parsing(&data, argc, argv) == ERROR)
		exit(1);
	data.cutlery_sem = sem_open("cutlery",O_CREAT, 0644, data.total_number_of_p);
	data.print_sem = sem_open("print",O_CREAT, 0644, 1);
	gettimeofday(&tv, NULL);
	data.start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	create_philosophers(&data);
	return (0);
}

static void	create_philosophers(t_data *data)
{
	int		i;
	pid_t	id;

	i = 1;
	while (i <= data->total_number_of_p)
	{
		data->philosopher = i;
		id = fork();
		if (id < 0)
			kill(0, SIGINT);
		if (id == 0)
		{
			routine(data);
			exit(1);
		}
		i++;
	}
	sem_post(data->wait_for_children);
	waitpid(-1, 0, 0);
}