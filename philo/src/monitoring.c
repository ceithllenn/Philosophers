/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:45:54 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/02 11:39:13 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitoring(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (!data->dead_flag)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			if (!is_alive(data->philos[i]))
				return (NULL);
			i++;
		}
		if (!data->dead_flag && data->meals_to_eat)
		{
			if (is_finished(data))
				return (NULL);
		}
		if (!data->dead_flag)
			whos_eating(data);
	}
	return (NULL);
}

int	is_finished(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->nb_philos)
	{
		if (data->philos[i]->finished)
			return (1);
		i++;
	}
	return (0);
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
		if (!data->philos[i]->eating_rd
			&& !data->philos[i]->finished && !data->dead_flag)
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
