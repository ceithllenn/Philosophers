/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:21:05 by elvallet          #+#    #+#             */
/*   Updated: 2024/07/29 09:32:46 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i]->thread, NULL);
		pthread_mutex_destroy(&(data->philos[i]->right_fork.mutex));
		free(data->philos[i]);
		i++;
	}
	free(data->philos);
	pthread_join(data->monitoring, NULL);
	free(data);
}
