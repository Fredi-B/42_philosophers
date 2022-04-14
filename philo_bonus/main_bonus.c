#include "philosophers_bonus.h"

static void	create_semaphores(t_data *data);
static void	create_philosophers(t_data *data);

int	main(int argc, char **argv)
{
	t_data			data;

	if (parsing(&data, argc, argv) == ERROR)
		exit(1);
	create_semaphores(&data);
	create_philosophers(&data);
	waitpid(-1, 0, 0);
	// kill(0, SIGINT);
	// system("leaks philo_bonus");
	sleep(1);
	return (0);
}
static void	create_semaphores(t_data *data)
{
	data->cutlery_sem = sem_open("cutlery",O_CREAT, 0644, data->total_number_of_p);
	sem_unlink("cutlery");
	data->print_sem = sem_open("print",O_CREAT, 0644, 1);
	sem_unlink("print");
	data->wait_for_children = sem_open("wait_for_children", O_CREAT, 0644, 0);
	sem_unlink("wait_for_children");
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
}