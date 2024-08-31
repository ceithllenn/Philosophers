/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:03:03 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/30 10:35:50 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

void	end_child(t_prog *prog, int i)
{
	ft_free_all(prog);
	exit(i);
}

void	ft_free_all(t_prog *prog)
{
	int	i;

	i = 1;
	while (i < prog->philos[0]->nb_philos)
	{
		free(prog->philos[i]);
		i++;
	}
	free(prog->philos[0]);
	free(prog->philos);
	sem_close(prog->forks);
	sem_close(prog->dead);
	sem_close(prog->write);
	sem_close(prog->meal);
	sem_close(prog->end);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_write");
	sem_unlink("/sem_meal");
	sem_unlink("/sem_end");
	free(prog);
}

void	ft_exit(t_prog *prog)
{
	int	i;
	int	status;

	status = 0;
	sem_wait(prog->dead);
	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == 2)
		sem_post(prog->dead);
	i = 0;
	while (i < prog->philos[0]->nb_philos)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	if (WEXITSTATUS(status != 2))
		sem_post(prog->dead);
	ft_free_all(prog);
}
