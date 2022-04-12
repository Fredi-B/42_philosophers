/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:10:56 by fbechtol          #+#    #+#             */
/*   Updated: 2022/04/11 16:10:57 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_data *philosopher);
static void	put_forks(t_data *philosopher);

void	eat(t_data *philosopher)
{
	long long	current_time;

	philosopher->times_eaten++;
	take_forks(philosopher);
	protected_print(philosopher, "is eating\n", EAT);
	pthread_mutex_lock(philosopher->eaten_mutex);
	current_time = *philosopher->time_last_eaten;
	pthread_mutex_unlock(philosopher->eaten_mutex);
	ft_sleep(philosopher, current_time, philosopher->time_to_eat);
	put_forks(philosopher);
}

static void	take_forks(t_data *philosopher)
{
	if (philosopher->philosopher % 2)
	{
		pthread_mutex_lock(philosopher->left_fork);
		protected_print(philosopher, "has taken a fork\n", FORK);
		pthread_mutex_lock(philosopher->right_fork);
		protected_print(philosopher, "has taken a fork\n", FORK);
	}
	else
	{
		pthread_mutex_lock(philosopher->right_fork);
		protected_print(philosopher, "has taken a fork\n", FORK);
		pthread_mutex_lock(philosopher->left_fork);
		protected_print(philosopher, "has taken a fork\n", FORK);
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
