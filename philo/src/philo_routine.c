/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:43:40 by elvallet          #+#    #+#             */
/*   Updated: 2024/07/27 11:27:57 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_routine(t_philo *philo)
{
	while (!philo->dead)
	{
		if (philo->eating_rd == 1)
		{
			eat(philo);
			philo_sleep(philo);
			if (!philo->eating_rd)
				philo_message(philo, THINKING_MSG);
		}
		if (!philo->eating_rd)
			usleep(1);
	}
}

void	eat(t_philo *philo)
{
	philo->eating_rd = 2;
	philo->last_meal = get_current_time() - philo->start;
	pthread_mutex_lock(&(philo->right_fork));
	philo_message(philo, FORK_MSG);
	pthread_mutex_lock(philo->left_fork);
	philo_message(philo, FORK_MSG);
	philo_message(philo, EATING_MSG);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&(philo->right_fork));
	pthread_mutex_unlock(philo->left_fork);
	philo->meals_eaten++;
	if (philo->meals_to_eat)
	{
		if (philo->meals_eaten == philo->meals_to_eat)
			philo->finished = 1;
	}
}

void	philo_sleep(t_philo *philo)
{
	philo_message(philo, SLEEPING_MSG);
	usleep(philo->time_to_sleep);
	philo->eating_rd = 0;
}

int		is_alive(t_philo *philo)
{
	size_t	curr;

	curr = get_current_time() - philo->last_meal;
	if (curr >= philo->time_to_die)
	{
		philo_message(philo, DEAD_MSG);
		return (0);
	}
	else
		return (1);
}

void	philo_message(t_philo *philo, t_msg msg)
{
	size_t	curr;

	curr = get_current_time() - philo->start;
	if (msg == DEAD_MSG)
		printf("%ld : %d has died\n", curr, philo->id);
	else if (msg == FORK_MSG)
		printf("%ld : %d has taken a fork\n", curr, philo->id);
	else if (msg == EATING_MSG)
		printf("%ld : %d is eating\n", curr, philo->id);
	else if (msg == SLEEPING_MSG)
		printf("%ld : %d is sleeping\n", curr, philo->id);
	else if (msg == THINKING_MSG)
		printf("%ld : %d is thinking\n", curr, philo->id);
}
