#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(&data, argc, argv) == ERROR)
		exit(1);
	if (init_mutexes(&data) == ERROR)
		err_exit(&data, 2, "Error in init_mutexes\n", 22);
	if (init_pointer(&data) == ERROR)
		err_exit(&data, 3, "Error in init_pointer\n", 22);
	if (init_threads(&data) == ERROR)
		err_exit(&data, 3, "Error in init_threads\n", 22);
	free_data(&data);
	// system("leaks philosopher");
	return (0);
}
