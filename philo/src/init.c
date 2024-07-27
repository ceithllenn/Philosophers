/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:58:45 by elvallet          #+#    #+#             */
/*   Updated: 2024/07/27 11:30:13 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*get_philo(t_data *data, t_philo *philo)
{
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	if (data->meals_to_eat)
		philo->meals_to_eat = data->meals_to_eat;
	philo->dead = &(data->dead_flag);
	if (pthread_mutex_init(&(philo->right_fork), NULL))
		return (NULL);
	philo->meals_eaten = 0;
	philo->finished = 0;
	philo->eating_rd = 0;
	philo->last_meal = philo->start;
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
	left_fork(data);
	return (philos);
}

void	left_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->nb_philos)
	{
		if (i == 0)
			data->philo[i]->left_fork = &(data->philo[data->nb_philos]->right_fork);
		else if (data->nb_philos != 1)
			data->philo[i]->left_fork = &(data->philo[i - 1]->right_fork);
	if (pthread_create(&(data->philo[i]->thread), NULL, philo_routine, data->philo[i]))
		return ;
	i++;
	}
}

void	init(char **argv)
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	if (!data)
		return ;
	data->start = get_current_time();
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_to_eat = ft_atoi(argv[5]);
	else
		data->meals_to_eat = 0;
	data->dead_flag = 0;
	data->philo = init_philos(data);
	if (!data->philo)
		return (free(data));
	if (pthread_create(&(data->monitoring), NULL, monitoring, data))
		return (free(data));
	start_simu(data);
}
