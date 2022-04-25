/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:10:47 by fbechtol          #+#    #+#             */
/*   Updated: 2022/04/25 12:46:34 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int			doctor_sleeps(t_data *philosopher);
static long long	get_time_passed(t_data *philosopher, \
										long long current_time);
static int			sb_died(t_data **philosophers, \
				long long current_time, long long time_passed, int i);
static int			check_meals(t_data *philosopher);

void	*doctor(void *arg)
{
	t_data		**philosophers;
	long long	current_time;
	long long	time_passed;
	int			i;

	philosophers = (t_data **)arg;
	i = doctor_sleeps(philosophers[0]);
	while (1)
	{
		current_time = get_time();
		time_passed = get_time_passed(philosophers[i], current_time);
		if (sb_died(philosophers, current_time, time_passed, i) == TRUE)
			break ;
		i++;
		if (check_meals(philosophers[0]) == TRUE)
			break ;
		if (i == philosophers[0]->total_number_of_p)
			i = 0;
	}
	return (OK);
}

static int	doctor_sleeps(t_data *philosopher)
{
	if (philosopher->total_number_of_p > 30)
		usleep(philosopher->time_to_die * 500);
	else
		usleep(philosopher->time_to_die * 500);
	return (0);
}

static long long	get_time_passed(t_data *philosopher, long long current_time)
{
	long long	time_passed;

	pthread_mutex_lock(philosopher->eaten_mutex);
	time_passed = (current_time - *philosopher->time_last_eaten);
	pthread_mutex_unlock(philosopher->eaten_mutex);
	return (time_passed);
}

static int	sb_died(t_data **philosophers, long long current_time, \
								long long time_passed, int i)
{
	if (time_passed < philosophers[i]->time_to_die)
		return (FALSE);
	pthread_mutex_lock(philosophers[0]->enough_mutex);
	*philosophers[0]->died = TRUE;
	pthread_mutex_unlock(philosophers[0]->enough_mutex);
	usleep(50);
	pthread_mutex_lock(philosophers[0]->start_mutex);
	printf("%lli %i died\n", (current_time - \
		*philosophers[i]->start_time), philosophers[i]->philosopher);
	pthread_mutex_unlock(philosophers[0]->start_mutex);
	return (TRUE);
}

static int	check_meals(t_data *philosopher)
{
	int	flag;

	flag = FALSE;
	pthread_mutex_lock(philosopher->enough_mutex);
	if (*philosopher->enough_meals == \
			philosopher->total_number_of_p)
			flag = TRUE;
	pthread_mutex_unlock(philosopher->enough_mutex);
	return (flag);
}
