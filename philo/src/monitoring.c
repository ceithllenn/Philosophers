/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:45:54 by elvallet          #+#    #+#             */
/*   Updated: 2024/07/27 11:27:48 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	start_simu(t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->nb_philos)
	{
		philo_routine(data->philo[i]);
		i++;
	}
	monitoring(data);
}

void	monitoring(t_data *data)
{
	int	i;

	while (!data->dead_flag)
	{
		i = 1;
		while (i <= data->nb_philos)
		{
			if (!is_alive(data->philo[i]))
			{
				data->dead_flag = 1;
				break ;
			}
			i++;
		}
		if (!data->dead_flag && data->meals_to_eat)
		{
			i = 1;
			while (i <= data->nb_philos)
			{
				if (!data->philo[i]->finished)
					break ;
				i++;
			}
			return (ft_exit(data));
		}
		whos_eating(data);
	}
	return (ft_exit(data));
}

void	whos_eating(t_data *data)
{
	int		i;
	size_t	time_tmp;
	int		id_tmp;

	i = 1;
	time_tmp = INT_MAX;
	id_tmp = 0;
	while (i <= data->nb_philos)
	{
		if (!data->philo[i]->eating_rd && !data->philo[i]->finished)
		{
			if ((get_current_time() - data->philo[i]->last_meal) < time_tmp)
			{
				time_tmp = get_current_time() - data->philo[i]->last_meal;
				id_tmp = data->philo[i]->id;
			}
			i++;
		}
	}
	data->philo[id_tmp]->eating_rd = 1;
}
