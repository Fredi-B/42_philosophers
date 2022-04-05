#include "philosophers.h"

static void	take_forks(t_data *philosopher);
static void	put_forks(t_data *philosopher);

void	eat(t_data *philosopher)
{
	long long	current_time;

	philosopher->times_eaten++;
	take_forks(philosopher);
	protected_print(philosopher, "is eating\n\n", EAT);
	current_time = *philosopher->time_last_eaten;
	ft_sleep(philosopher, current_time, philosopher->time_to_eat);
	put_forks(philosopher);
}

static void	take_forks(t_data *philosopher)
{
	if (philosopher->philosopher % 2)
	{
		pthread_mutex_lock(philosopher->left_fork);
		// to do: change to "has taken a fork"
		protected_print(philosopher, "has taken left fork\n", L_FORK);
		pthread_mutex_lock(philosopher->right_fork);
		protected_print(philosopher, "has taken right fork\n", R_FORK);
	}
	else
	{
		pthread_mutex_lock(philosopher->right_fork);
		protected_print(philosopher, "has taken right fork\n", R_FORK);
		pthread_mutex_lock(philosopher->left_fork);
		protected_print(philosopher, "has taken left fork\n", L_FORK);
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
