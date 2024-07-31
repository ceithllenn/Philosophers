/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 07:31:38 by elvallet          #+#    #+#             */
/*   Updated: 2024/07/29 09:46:37 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef enum e_msg
{
	FORK_MSG, EATING_MSG, SLEEPING_MSG, THINKING_MSG, DEAD_MSG
}			t_msg;

typedef struct s_fork
{
	int				flag;
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			meals_eaten;
	int			finished;
	int			eating_rd;
	size_t		start;
	size_t		last_meal;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			meals_to_eat;
	int			*dead;
	t_fork		*left_fork;
	t_fork		right_fork;
	int			*flag;
}				t_philo;

typedef struct s_data
{
	pthread_t	monitoring;
	int			dead_flag;
	int			nb_philos;
	size_t		start;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			meals_to_eat;
	t_philo		**philos;
	int			flag;
}				t_data;

/*EXIT.C*/
void	ft_exit(t_data *data);

/*INIT.C*/
int		init_fork(t_philo *philo);
t_philo	*get_philo(t_data *data, t_philo *philo);
t_philo	**init_philos(t_data *data);
void	init(char **argv);
void	left_fork(t_data *data);

/*MONITORING.C*/
void	*monitoring(void *arg);
void	whos_eating(t_data *data);

/*PHILO_ROUTINE.C*/
void	*philo_routine(void *arg);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
int		is_alive(t_philo *philo);
void	philo_message(t_philo *philo, t_msg msg);

/*UTILS.C*/
void	free_philo(t_philo **philo);
size_t	get_current_time(void);
int		ft_atoi(const char *nptr);

#endif