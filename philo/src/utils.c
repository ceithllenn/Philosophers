/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:56:58 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/20 07:27:13 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philo(t_philo **philo)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		pthread_mutex_destroy(philo[i]->r_fork);
		free(philo[i]);
		i++;
	}
	free(philo);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t t)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < t)
		usleep(500);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	n = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = n * 10 + nptr[i] - '0';
		i++;
	}
	return (n);
}

int	solo_philo(t_philo *philo)
{
	ft_usleep(philo->time_to_die);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}
