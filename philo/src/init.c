/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:58:45 by elvallet          #+#    #+#             */
/*   Updated: 2024/07/26 18:35:21 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*get_philo(t_data *data, t_philo *philo)
{
	if (pthread_create(&(philo->thread), NULL, philo_routine(philo), philo))
		return (NULL);
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->nb_philos = data->nb_philos;
	if (data->meals_to_eat)
		philo->meals_to_eat = data->meals_to_eat;
	philo->dead = &(data->dead_flag);
	if (pthread_mutex_init(&(philo->right_fork), NULL))
		return (NULL);
	if (philo->id == 0)
		philo->left_fork = &(data->philo[data->nb_philos]->right_fork);
	else
		philo->left_fork = &(data->philo[philo->id - 1]->right_fork);
	if (pthread_mutex_init(&(philo->meal_lock), NULL))
		return (NULL);
	return (philo);
}

t_philo	**init_philos(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo*) * data->nb_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			while (--i)
				free(philos[i]);
			free(philos);
			return (NULL);
		}
		philos[i]->id = i + 1;
		philos[i] = get_philo(data, philos[i]);
		i++;
	}
	return (philos);
}

void	init(char **argv)
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	if (!data)
		return ;
	data->start = get_current_time();
	if (pthread_create(&(data->monitoring), NULL, monitoring(), data))
		return (free(data));
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_to_eat = ft_atoi(argv[5]);
	data->philo = init_philos(data);
	if (!data->philo)
		return (free(data));
}
