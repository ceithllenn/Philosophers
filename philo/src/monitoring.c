/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:45:54 by elvallet          #+#    #+#             */
/*   Updated: 2024/07/29 09:52:37 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitoring(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	data->flag = 1;
	while (!data->dead_flag)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			if (!is_alive(data->philos[i]))
			{
				data->dead_flag = 1;
				break ;
			}
			i++;
		}
		if (!data->dead_flag && data->meals_to_eat)
		{
			i = 0;
			while (i < data->nb_philos)
			{
				if (data->philos[i]->finished)
					break ;
				i++;
			}
			return (NULL);
		}
		if (!data->dead_flag)
			whos_eating(data);
	}
	return (NULL);
}

void	whos_eating(t_data *data)
{
	int		i;
	size_t	time_tmp;
	int		id_tmp;

	i = 0;
	time_tmp = INT_MAX;
	id_tmp = 0;
	while (i < data->nb_philos)
	{
		if (!data->philos[i]->eating_rd && !data->philos[i]->finished && !data->dead_flag)
		{
			if ((get_current_time() - data->philos[i]->last_meal) < time_tmp)
			{
				time_tmp = get_current_time() - data->philos[i]->last_meal;
				id_tmp = i;
			}
		}
		i++;
	}
	data->philos[id_tmp]->eating_rd = 1;
}
