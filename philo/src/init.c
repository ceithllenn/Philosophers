/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:58:45 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/02 11:37:55 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_fork(t_philo *philo)
{
	t_fork	fork;

	fork.flag = 0;
	if (pthread_mutex_init(&fork.mutex, NULL) != 0)
		return (0);
	philo->right_fork = fork;
	return (1);
}

t_philo	*get_philo(t_data *data, t_philo *philo)
{
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->start = data->start;
	if (data->meals_to_eat)
		philo->meals_to_eat = data->meals_to_eat;
	philo->dead = &(data->dead_flag);
	philo->meals_eaten = 0;
	philo->finished = 0;
	philo->eating_rd = 0;
	philo->last_meal = philo->start;
	if (!init_fork(philo))
		return (NULL);
	return (philo);
}

t_philo	**init_philos(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			free_philo(data->philos);
			return (NULL);
		}
		philos[i]->id = i + 1;
		philos[i] = get_philo(data, philos[i]);
		i++;
	}
	data->philos = philos;
	left_fork(data);
	return (philos);
}

void	left_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (i == 0)
			data->philos[i]->left_fork
				= &(data->philos[data->nb_philos - 1]->right_fork);
		else if (data->nb_philos != 1)
			data->philos[i]->left_fork = &(data->philos[i - 1]->right_fork);
		if (pthread_create(&(data->philos[i]->thread),
				NULL, philo_routine, data->philos[i]))
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
	data->philos = init_philos(data);
	if (!data->philos)
		return (free(data));
	if (pthread_create(&(data->monitoring), NULL, monitoring, data))
		return (free(data));
	ft_exit(data);
}
