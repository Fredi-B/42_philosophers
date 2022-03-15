#include "philosophers.h"

int time(void)
{
	struct timeval tv_start;
	struct timeval tv_run;
	long int i;

	i = 0;
	gettimeofday(&tv_start, NULL);
	printf("sec: %li\n", tv_start.tv_sec);
	printf("usec: %li\n", tv_start.tv_usec);
	printf("sec * 1000: %li\n", tv_start.tv_sec * 1000);
	printf("usec / 1000: %li\n", tv_start.tv_usec / 1000);
	while (i < 5200)
	{
		gettimeofday(&tv_run, NULL);
		i = ((tv_run.tv_sec * 1000) + (tv_run.tv_usec / 1000)) \
				- ((tv_start.tv_sec * 1000) + (tv_start.tv_usec / 1000));
	}
	printf("%li\n", i);


	return (0);
}