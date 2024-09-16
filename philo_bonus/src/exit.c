/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:03:03 by elvallet          #+#    #+#             */
/*   Updated: 2024/09/04 09:03:35 by elvallet         ###   ########.fr       */
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
	sem_unlink("/sem_forks");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_write");
	sem_unlink("/sem_meal");
	free(prog);
}

void	ft_exit(t_prog *prog)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 2)
		{
			while (i < prog->philos[0]->nb_philos)
			{
				kill(prog->philos[i]->pid, SIGKILL);
				i++;
			}
		}
		else
		{
			while (++i < prog->philos[0]->nb_philos)
				waitpid(-1, &status, 0);
		}
	}
	ft_free_all(prog);
}
