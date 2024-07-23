/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 07:31:38 by elvallet          #+#    #+#             */
/*   Updated: 2024/07/23 09:26:01 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_fork
{
	int				id;
	int				fork;
}				t_fork;

typedef struct s_philo
{
	int		id;
	int		meals_eaten;
	int		dead;
	t_fork	*right;
	t_fork	*left;	
}				t_philo;

typedef struct s_data
{
	int		nb_philo;
	int		*dead;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meals_to_eat;
	t_fork	**forks;
	t_philo	**philos;	
}				t_data;

/*INIT.C*/
t_fork	**init_forks(t_data *data);
t_philo	**init_philos(t_data *data);
int		init(int argc, char **argv);

/*UTILS.C*/
void	free_split(void **data);
int		ft_atoi(const char *nptr);

#endif