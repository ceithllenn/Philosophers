/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:59:29 by elvallet          #+#    #+#             */
/*   Updated: 2024/09/04 09:01:15 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (is_dead(philo, philo->time_to_die) || is_over(philo))
			break ;
		ft_usleep(1);
	}
	return (arg);
}

void	philo_message(t_philo *philo, t_msg msg)
{
	size_t	curr;

	curr = get_current_time() - philo->start;
	sem_wait(philo->write);
	if (msg == DEAD_MSG)
		printf("%ld %d died\n", curr, philo->id);
	else
	{
		sem_wait(philo->dead);
		if (philo->dead_flag)
			return ((void)sem_post(philo->dead), (void)sem_post(philo->write));
		sem_post(philo->dead);
	}
	if (msg == FORK_MSG)
		printf("%ld %d has taken a fork\n", curr, philo->id);
	else if (msg == EATING_MSG)
		printf("%ld %d is eating\n", curr, philo->id);
	else if (msg == SLEEPING_MSG)
		printf("%ld %d is sleeping\n", curr, philo->id);
	else if (msg == THINKING_MSG)
		printf("%ld %d is thinking\n", curr, philo->id);
	sem_post(philo->write);
}

int	is_dead(t_philo *philo, size_t time_to_die)
{
	sem_wait(philo->meal);
	if (get_current_time() - philo->last_meal >= time_to_die)
	{
		philo_message(philo, DEAD_MSG);
		sem_wait(philo->dead);
		philo->dead_flag = 1;
		sem_post(philo->dead);
		sem_post(philo->meal);
		return (1);
	}
	sem_post(philo->meal);
	return (0);
}

int	is_over(t_philo *philo)
{
	sem_wait(philo->meal);
	if (philo->meals_eaten == philo->meals_to_eat)
	{
		philo->done = 1;
		sem_wait(philo->dead);
		philo->dead_flag = 1;
		sem_post(philo->dead);
		sem_post(philo->meal);
		return (1);
	}
	sem_post(philo->meal);
	return (0);
}
