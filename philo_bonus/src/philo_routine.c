/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:16:39 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/31 11:20:34 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	philo_loop(t_philo *philo)
{
	while (1)
	{
		if (!ft_eat(philo))
			return ;
		ft_usleep(1);
		sem_wait(philo->end);
		if (*philo->stop)
		{
			sem_post(philo->end);
			return ;
		}
		sem_post(philo->end);
		ft_sleep(philo);
		sem_wait(philo->end);
		if (*philo->stop)
		{
			sem_post(philo->end);
			return ;
		}
		sem_post(philo->end);
		ft_think(philo);
	}
}

void	philo_routine(t_prog *prog, t_philo *philo)
{
	if (pthread_create(&philo->observer, NULL, &monitoring, philo) != 0)
		return (ft_putstr("pthread_create error\n", 2), end_child(prog, 0));
	if (pthread_create(&philo->death_monitor, NULL, &death_monitor, philo) != 0)
		return (ft_putstr("pthread_create error\n", 2), end_child(prog, 0));
	ft_delay(philo);
	philo_loop(philo);
	ft_usleep(1);
	if (philo->dead_flag)
	{
		if (pthread_join(philo->death_monitor, NULL) != 0)
			return (ft_putstr("pthread join error\n", 2), end_child(prog, 0));
	}
	else
	{
		if (pthread_detach(philo->death_monitor) != 0)
			return (ft_putstr("pthread detach error", 2), end_child(prog, 0));
	}
	if (pthread_detach(philo->observer) != 0)
		ft_putstr("pthread detach error", 2);
	if (philo->done)
		end_child(prog, 1);
	else
		end_child(prog, 2);
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

void	ft_sleep(t_philo *philo)
{
	sem_wait(philo->end);
	if (*philo->stop)
	{
		sem_post(philo->end);
		return ;
	}
	sem_post(philo->end);
	sem_wait(philo->meal);
	philo->meals_eaten++;
	sem_post(philo->meal);
	philo_message(philo, SLEEPING_MSG);
	ft_usleep(philo->time_to_sleep);
}

int	ft_eat(t_philo *philo)
{
	if (!(philo->id % 2) && philo->time_to_die <= philo->time_to_eat)
		return (ft_usleep(philo->time_to_die), 0);
	sem_wait(philo->forks);
	philo_message(philo, FORK_MSG);
	if (philo->nb_philos == 1)
		return (ft_usleep(philo->time_to_die), sem_post(philo->forks), 0);
	sem_wait(philo->end);
	if (!*philo->stop)
		sem_wait(philo->forks);
	else
		return (sem_post(philo->forks), sem_post(philo->end), 0);
	sem_post(philo->end);
	sem_wait(philo->end);
	if (*philo->stop)
		return (sem_post(philo->end), sem_post(philo->forks),
			sem_post(philo->forks), 0);
	sem_post(philo->end);
	philo_message(philo, FORK_MSG);
	philo_message(philo, EATING_MSG);
	sem_wait(philo->meal);
	philo->last_meal = get_current_time();
	sem_post(philo->meal);
	ft_usleep(philo->time_to_eat);
	return (sem_post(philo->forks), sem_post(philo->forks), 1);
}
