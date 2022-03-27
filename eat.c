#include "philosophers.h"

static void	take_forks(t_data *philosopher);
static void	put_forks(t_data *philosopher);

void	eat(t_data *philosopher)
{
	struct timeval	just_eaten;

	take_forks(philosopher);
	protected_print(philosopher, EAT);
	gettimeofday(&just_eaten, NULL);
	*philosopher->time_last_eaten = ((just_eaten.tv_sec * 1000) \
									+ (just_eaten.tv_usec / 1000));
	usleep(philosopher->time_to_eat * 1000);
	put_forks(philosopher);
}

static void	take_forks(t_data *philosopher)
{
	if (philosopher->philosopher % 2)
	{
		pthread_mutex_lock(philosopher->left_fork);
		protected_print(philosopher, L_FORK);
		pthread_mutex_lock(philosopher->right_fork);
		protected_print(philosopher, R_FORK);
	}
	else
	{
		pthread_mutex_lock(philosopher->right_fork);
		protected_print(philosopher, R_FORK);
		pthread_mutex_lock(philosopher->left_fork);
		protected_print(philosopher, L_FORK);
	}
}

static	void	put_forks(t_data *philosopher)
{
	if (philosopher->philosopher % 2)
	{
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
	}
}
