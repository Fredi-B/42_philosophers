/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pointer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:11:14 by fbechtol          #+#    #+#             */
/*   Updated: 2022/04/11 16:11:15 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_pointer(t_data *data)
{
	data->cnt_number_of_p = malloc(sizeof(int));
	*data->cnt_number_of_p = 0;
	data->start_time = malloc(sizeof(long long));
	*data->start_time = 0;
	data->enough_meals = malloc(sizeof(int));
	*data->enough_meals = 0;
	data->died = malloc(sizeof(int));
	if (!data->died || !data->enough_meals || !data->start_time \
			|| !data->cnt_number_of_p)
	{
		write(2, "Error: malloc pointer\n", 22);
		return (ERROR);
	}
	*data->died = FALSE;
	return (OK);
}
