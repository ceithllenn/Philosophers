/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:58:45 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/31 11:18:50 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_threads(t_data *data)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitoring, data) != 0)
		return (ft_putstr("Thread creation error\n", 2));
	i = 0;
	while (i < data->philos[0]->nb_philos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL, &philo_routine,
				data->philos[i]) != 0)
			return (ft_putstr("Thread creation error\n", 2));
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		return (ft_putstr("Thread join error\n", 2));
	while (i < data->philos[0]->nb_philos)
	{
		if (pthread_join(data->philos[i]->thread, NULL) != 0)
			return (ft_putstr("Thread join error\n", 2));
		i++;
	}
}

t_philo	*get_philo(t_data *data, t_philo *philo, char **argv)
{
	philo->nb_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->start = get_current_time();
	philo->last_meal = get_current_time();
	if (argv[5])
		philo->meals_to_eat = ft_atoi(argv[5]);
	else
		philo->meals_to_eat = -1;
	philo->dead = &data->dead_flag;
	philo->meals_eaten = 0;
	philo->write_lock = &data->write_lock;
	philo->dead_lock = &data->dead_lock;
	philo->meal_lock = &data->meal_lock;
	return (philo);
}

t_philo	*get_forks(t_philo *philo, pthread_mutex_t *forks)
{
	philo->l_fork = &forks[philo->id - 1];
	if (philo->id == 1)
		philo->r_fork = &forks[philo->nb_philos - 1];
	else
		philo->r_fork = &forks[philo->id - 2];
	return (philo);
}

t_philo	**init_philos(t_data *data, char **argv)
{
	t_philo			**philos;
	int				i;

	philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philos)
		return (NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!data->forks)
		return (free(philos), NULL);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&data->forks[i], NULL);
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (free_philo(philos), NULL);
		philos[i]->id = i + 1;
		philos[i] = get_philo(data, philos[i], argv);
		if (!philos[i])
			return (NULL);
		philos[i] = get_forks(philos[i], data->forks);
		i++;
	}
	data->philos = philos;
	return (philos);
}

void	init(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return ;
	data->dead_flag = 0;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	data->philos = init_philos(data, argv);
	if (!data->philos)
		return (free(data));
	init_threads(data);
	ft_exit(data);
}
