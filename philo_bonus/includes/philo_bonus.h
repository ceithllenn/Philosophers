/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:46:56 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/31 11:18:09 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <pthread.h>

typedef enum e_msg
{
	FORK_MSG,
	EATING_MSG,
	SLEEPING_MSG,
	THINKING_MSG,
	DEAD_MSG
}				t_msg;

typedef struct s_philo
{
	pid_t		pid;
	pthread_t	observer;
	pthread_t	death_monitor;
	int			dead_flag;
	int			id;
	int			meals_eaten;
	int			nb_philos;
	int			done;
	int			*stop;
	size_t		start;
	size_t		last_meal;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			meals_to_eat;
	sem_t		*end;
	sem_t		*meal;
	sem_t		*forks;
	sem_t		*dead;
	sem_t		*write;
}				t_philo;

typedef struct s_prog
{
	int		stop;
	t_philo	**philos;
	sem_t	*end;
	sem_t	*meal;
	sem_t	*forks;
	sem_t	*dead;
	sem_t	*write;
}				t_prog;

/*ARGUMENTS.C*/
size_t	ft_strlen(const char *src);
void	ft_putstr(char *s, int fd);
int		is_n(char *s);
int		check_arguments(char **argv);

/*EXIT.C*/
void	end_child(t_prog *prog, int i);
void	ft_free_all(t_prog *prog);
void	ft_exit(t_prog *prog);

/*INIT.C*/
void	init_childs(t_prog *prog, t_philo **philos);
t_philo	*get_philo(t_prog *prog, t_philo *philo, char **argv);
t_philo	**init_philos(t_prog *prog, char **argv);
void	init(char **argv);

/*MONITORING.C*/
void	*monitoring(void *arg);
void	*death_monitor(void *arg);
void	philo_message(t_philo *philo, t_msg msg);
int		is_dead(t_philo *philo, size_t time_to_die);
int		is_over(t_philo *philo);

/*PHILO_ROUTINE.C*/
void	philo_routine(t_prog *prog, t_philo *philo);
void	ft_delay(t_philo *philo);
int		dead_loop(t_philo *philo);
void	ft_sleep(t_philo *philo);
int		ft_eat(t_philo *philo);

/*UTILS.C*/
void	free_philo(t_philo **philo);
size_t	get_current_time(void);
void	ft_usleep(size_t t);
int		ft_atoi(const char *nptr);

#endif