/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:16:39 by elvallet          #+#    #+#             */
/*   Updated: 2024/09/04 09:02:13 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	philo_loop(t_philo *philo)
{
	ft_delay(philo);
	while (1)
	{
		if (!ft_eat(philo))
			break ;
		sem_wait(philo->dead);
		if (philo->dead_flag)
		{
			sem_post(philo->dead);
			break ;
		}
		sem_post(philo->dead);
		ft_usleep(1);
		ft_sleep(philo);
		sem_wait(philo->dead);
		if (philo->dead_flag)
		{
			sem_post(philo->dead);
			break ;
		}
		sem_post(philo->dead);
		philo_message(philo, THINKING_MSG);
	}
}

void	philo_routine(t_prog *prog, t_philo *philo)
{
	if (pthread_create(&philo->observer, NULL, &monitoring, philo) != 0)
		return (ft_putstr("pthread_create error\n", 2), end_child(prog, 0));
	philo_loop(philo);
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
	sem_wait(philo->dead);
	if (philo->dead_flag)
		return ((void)sem_post(philo->dead));
	sem_post(philo->dead);
	philo_message(philo, SLEEPING_MSG);
	sem_wait(philo->meal);
	philo->meals_eaten++;
	sem_post(philo->meal);
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
	sem_wait(philo->dead);
	sem_wait(philo->forks);
	if (philo->dead_flag)
		return (sem_post(philo->dead), sem_post(philo->forks),
			sem_post(philo->forks), 0);
	sem_post(philo->dead);
	philo_message(philo, FORK_MSG);
	philo_message(philo, EATING_MSG);
	sem_wait(philo->meal);
	philo->last_meal = get_current_time();
	sem_post(philo->meal);
	ft_usleep(philo->time_to_eat);
	return (sem_post(philo->forks), sem_post(philo->forks), 1);
}
