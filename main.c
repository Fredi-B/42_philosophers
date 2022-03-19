#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parsing(&data, argc, argv) == ERROR)
		return (1);
	if (init_mutexes(&data) == ERROR)
		return (2);
	return (0);
}
