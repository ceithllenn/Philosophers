/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 07:31:38 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/31 11:17:46 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_msg
{
	FORK_MSG,
	EATING_MSG,
	SLEEPING_MSG,
	THINKING_MSG,
	DEAD_MSG
}			t_msg;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	int				nb_philos;
	size_t			start;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}				t_philo;

typedef struct s_data
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*forks;
	t_philo			**philos;
}				t_data;

/*ARGUMENTS.C*/
size_t	ft_strlen(const char *src);
void	ft_putstr(char *s, int fd);
int		is_n(char *s);
int		check_arguments(char **argv);

/*EXIT.C*/
void	ft_exit(t_data *data);

/*INIT.C*/
void	init_threads(t_data *data);
t_philo	*get_philo(t_data *data, t_philo *philo, char **argv);
t_philo	*get_forks(t_philo *philo, pthread_mutex_t *forks);
t_philo	**init_philos(t_data *data, char **argv);
void	init(char **argv);

/*MONITORING.C*/
void	*monitoring(void *arg);
void	philo_message(t_philo *philo, t_msg msg);
int		is_dead(t_philo *philo, size_t time_to_die);
int		ft_dead_flag(t_philo **philos);
int		is_over(t_philo **philos);

/*PHILO_ROUTINE.C*/
void	*philo_routine(void *arg);
int		dead_loop(t_philo *philo);
void	ft_delay(t_philo *philo);
void	ft_sleep(t_philo *philo);
int		ft_eat(t_philo *philo);

/*UTILS.C*/
void	free_philo(t_philo **philo);
size_t	get_current_time(void);
void	ft_usleep(size_t t);
int		ft_atoi(const char *nptr);
int		solo_philo(t_philo *philo);

#endif