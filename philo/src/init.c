/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:58:45 by elvallet          #+#    #+#             */
/*   Updated: 2024/07/23 09:23:15 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_fork	**init_forks(t_data *data)
{
	t_fork	**forks;
	int		i;
	
	forks = malloc(sizeof(t_fork*) * data->nb_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		forks[i] = malloc(sizeof(t_fork));
		if (!forks[i])
		{
			while (--i)
				free(forks[i]);
			free(forks);
			return (NULL);
		}
		forks[i]->id = i + 1;
		i++;
	}
	return (forks);
}

t_philo	**init_philos(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo*) * data->nb_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
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
		philos[i]->right = &data->forks[i];
		philos[i]->left = &data->forks[i + 1];
		philos[i]->meals_eaten = 0;
		philos[i]->dead = 0;
		i++;
	}
	return (philos);
}

int	init(int argc, char **argv)
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_to_eat = ft_atoi(argv[5]);
	data->forks = init_forks(data);
	data->philos = init_philos(data);
	if (!data->forks || !data->philos)
		return (free(data), 0);
}
