/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:45:54 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/31 10:49:29 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		ft_usleep(1);
		if (is_over(data->philos) || ft_dead_flag(data->philos))
			break ;
	}
	return (arg);
}

void	philo_message(t_philo *philo, t_msg msg)
{
	size_t	curr;

	pthread_mutex_lock(philo->write_lock);
	curr = get_current_time() - philo->start;
	if (msg == DEAD_MSG)
		printf("%ld %d died\n", curr, philo->id);
	else if (dead_loop(philo))
		return ;
	else if (msg == FORK_MSG)
		printf("%ld %d has taken a fork\n", curr, philo->id);
	else if (msg == EATING_MSG)
		printf("%ld %d is eating\n", curr, philo->id);
	else if (msg == SLEEPING_MSG)
		printf("%ld %d is sleeping\n", curr, philo->id);
	else if (msg == THINKING_MSG)
		printf("%ld %d is thinking\n", curr, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

int	is_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	ft_dead_flag(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < philos[0]->nb_philos)
	{
		if (is_dead(philos[i], philos[i]->time_to_die))
		{
			philo_message(philos[i], DEAD_MSG);
			pthread_mutex_lock(philos[i]->dead_lock);
			*philos[i]->dead = 1;
			pthread_mutex_unlock(philos[i]->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_over(t_philo **philos)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	if (philos[i]->meals_to_eat == -1)
		return (0);
	while (i < philos[0]->nb_philos)
	{
		pthread_mutex_lock(philos[i]->meal_lock);
		if (philos[i]->meals_eaten >= philos[i]->meals_to_eat)
			done++;
		pthread_mutex_unlock(philos[i]->meal_lock);
		i++;
	}
	if (done == philos[0]->nb_philos)
	{
		pthread_mutex_lock(philos[0]->dead_lock);
		*philos[0]->dead = 1;
		pthread_mutex_unlock(philos[0]->dead_lock);
		return (1);
	}
	return (0);
}
