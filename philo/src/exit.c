/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:21:05 by elvallet          #+#    #+#             */
/*   Updated: 2024/07/27 10:29:34 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_exit(t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->nb_philos)
	{
		pthread_join(data->philo[i]->thread, NULL);
		pthread_mutex_destroy(&(data->philo[i]->right_fork));
		free(data->philo[i]);
		i++;
	}
	free(data->philo);
	pthread_join(data->monitoring, NULL);
	free(data);
}
