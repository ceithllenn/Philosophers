/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:21:05 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/20 07:05:31 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_exit(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->philos[0]->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		free(data->philos[i]);
		i++;
	}
	pthread_mutex_destroy(&data->forks[0]);
	free(data->philos[0]);
	free(data->philos);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	free(data->forks);
	free(data);
}
