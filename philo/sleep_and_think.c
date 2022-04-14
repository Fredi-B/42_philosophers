/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_and_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:11:49 by fbechtol          #+#    #+#             */
/*   Updated: 2022/04/14 11:54:35 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	sync_philosophers(t_data *philosopher);

/* calls ft_sleep only if philosopher won't die during sleep */
void	sleep_and_think(t_data *philosopher)
{
	long long	current_time;

	protected_print(philosopher, "is sleeping\n", SLEEP);
	current_time = get_time();
	ft_sleep(philosopher, current_time, philosopher->time_to_sleep);
	protected_print(philosopher, "is thinking\n", THINK);
	sync_philosophers(philosopher);
}

void	ft_sleep(t_data *philosopher, long long current_time, long long chill)
{
	long long	start_time;
	int			someone_died;

	someone_died = FALSE;
	start_time = current_time;
	while (current_time < start_time + chill)
	{
		pthread_mutex_lock(philosopher->enough_mutex);
		if (*philosopher->died == TRUE)
			someone_died = TRUE;
		pthread_mutex_unlock(philosopher->enough_mutex);
		if (someone_died == TRUE)
			break ;
		if (philosopher->total_number_of_p > 50)
			usleep(philosopher->total_number_of_p);
		else
			usleep(50);
		current_time = get_time();
	}
}

static void	sync_philosophers(t_data *philosopher)
{
	if (philosopher->total_number_of_p > 170)
		usleep(820);
	else if (philosopher->total_number_of_p > 30)
		usleep(200);
	else
		usleep(200);
}
