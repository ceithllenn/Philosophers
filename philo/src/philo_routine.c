/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:43:40 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/31 11:20:26 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_delay(philo);
	while (1)
	{
		if (dead_loop(philo))
			break ;
		if (!ft_eat(philo))
			break ;
		ft_sleep(philo);
		if (dead_loop(philo))
			break ;
		philo_message(philo, THINKING_MSG);
		ft_usleep(1);
	}
	return (arg);
}

void	ft_delay(t_philo *philo)
{
	if (philo->nb_philos % 2)
	{
		if (philo->id % 2 && philo->id != 1)
			ft_usleep(philo->time_to_eat / 2);
		if (!(philo->id % 2))
			ft_usleep(philo->time_to_eat / 2 + 1);
	}
	else if (!(philo->id % 2))
		ft_usleep(1);
}

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	philo_message(philo, SLEEPING_MSG);
	ft_usleep(philo->time_to_sleep);
}

int	ft_eat(t_philo *philo)
{
	if (!(philo->id % 2) && philo->time_to_die <= philo->time_to_eat)
		return (ft_usleep(philo->time_to_die), 0);
	pthread_mutex_lock(philo->r_fork);
	if (dead_loop(philo))
		return (pthread_mutex_unlock(philo->r_fork), 0);
	philo_message(philo, FORK_MSG);
	if (philo->nb_philos == 1)
		return (solo_philo(philo));
	pthread_mutex_lock(philo->l_fork);
	if (dead_loop(philo))
		return (pthread_mutex_unlock(philo->r_fork),
			pthread_mutex_unlock(philo->l_fork), 0);
	philo_message(philo, FORK_MSG);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	philo_message(philo, EATING_MSG);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	return (1);
}
