/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:53:18 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/31 11:19:23 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	init_childs(t_prog *prog, t_philo **philos)
{
	int			i;

	i = 0;
	while (i < philos[0]->nb_philos)
	{
		philos[i]->pid = fork();
		if (!philos[i]->pid)
			philo_routine(prog, philos[i]);
		else if (philos[i]->pid == -1)
			return (ft_putstr("Error : fork\n", 2), ft_exit(prog));
		i++;
	}
	ft_exit(prog);
}

t_philo	*get_philo(t_prog *prog, t_philo *philo, char **argv)
{
	philo->nb_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->start = get_current_time();
	philo->last_meal = get_current_time();
	if (argv[5])
		philo->meals_to_eat = ft_atoi(argv[5]);
	else
		philo->meals_to_eat = -1;
	philo->meals_eaten = 0;
	philo->dead_flag = 0;
	philo->done = 0;
	philo->stop = &prog->stop;
	philo->forks = prog->forks;
	philo->meal = prog->meal;
	philo->dead = prog->dead;
	philo->write = prog->write;
	philo->end = prog->end;
	return (philo);
}

t_philo	**init_philos(t_prog *prog, char **argv)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (free_philo(philos), NULL);
		philos[i]->id = i + 1;
		philos[i] = get_philo(prog, philos[i], argv);
		i++;
	}
	prog->philos = philos;
	return (philos);
}

void	init(char **argv)
{
	t_prog	*prog;

	prog = malloc(sizeof(t_prog));
	if (!prog)
		return ;
	sem_unlink("/sem_meal");
	sem_unlink("/sem_forks");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_write");
	sem_unlink("/sem_end");
	prog->forks = sem_open("/sem_forks", O_CREAT, 0644, ft_atoi(argv[1]));
	prog->end = sem_open("/sem_end", O_CREAT, 0644, 1);
	prog->meal = sem_open("/sem_meal", O_CREAT, 0644, 1);
	prog->dead = sem_open("/sem_dead", O_CREAT, 0644, 1);
	prog->write = sem_open("/sem_write", O_CREAT, 0644, 1);
	prog->stop = 0;
	prog->philos = init_philos(prog, argv);
	if (!prog->philos)
		return (free(prog));
	init_childs(prog, prog->philos);
}
