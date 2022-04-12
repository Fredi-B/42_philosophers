/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:11:27 by fbechtol          #+#    #+#             */
/*   Updated: 2022/04/11 16:57:59 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long long	get_runtime(t_data *philosopher, long long current_time);

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
		err_exit(&data, 4, "Error in init_threads\n", 22);
	free_data(&data);
	return (0);
}

void	protected_print(t_data *philosopher, char *action, int state)
{
	long long	current_time;
	long long	runtime;

	current_time = get_time();
	runtime = get_runtime(philosopher, current_time);
	if (state == EAT)
	{
		pthread_mutex_lock(philosopher->eaten_mutex);
		*philosopher->time_last_eaten = current_time;
		pthread_mutex_unlock(philosopher->eaten_mutex);
	}
	pthread_mutex_lock(philosopher->print_mutex);
	pthread_mutex_lock(philosopher->enough_mutex);
	if (*philosopher->enough_meals < philosopher->total_number_of_p \
			&& *philosopher->died == FALSE)
		printf("%lli %i %s", runtime, philosopher->philosopher, action);
	pthread_mutex_unlock(philosopher->enough_mutex);
	pthread_mutex_unlock(philosopher->print_mutex);
	if (state == EAT && philosopher->times_eaten == \
										philosopher->number_of_meals)
	{
		pthread_mutex_lock(philosopher->enough_mutex);
		(*philosopher->enough_meals)++;
		pthread_mutex_unlock(philosopher->enough_mutex);
	}
}

static long long	get_runtime(t_data *philosopher, long long current_time)
{
	long long	runtime;

	pthread_mutex_lock(philosopher->start_mutex);
	runtime = current_time - *philosopher->start_time;
	pthread_mutex_unlock(philosopher->start_mutex);
	return (runtime);
}
