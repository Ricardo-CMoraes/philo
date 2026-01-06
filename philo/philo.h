/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:19:47 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/04 21:30:23 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define PHILO_MAX 200

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

typedef struct s_settings
{
	int		n_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		times_must_eat;
	long			start_time;
	pthread_mutex_t write_lock;
	pthread_mutex_t stop_lock;
	int				simulation_stopped;
}	t_settings;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_settings		*settings;
}	t_philo;

//aux
int	ft_atoi(const char *str);
long get_time_ms(void);
void print_action(t_philo *philo, const char *msg);
void precise_usleep(long time_to_wait, t_philo *philo);
int is_simulation_over(t_philo *p);



//validate
int	is_number(char *arg);
int	check_args(char **argv);

//init
void	init_settings(t_settings *settings, int argc, char **argv);
pthread_mutex_t	*init_forks(t_settings *settings);
t_philo	*init_philo(t_settings *settings, pthread_mutex_t *forks);
int	init_threads(t_philo *philo);

//clean
void    clean_all(t_philo	*philo, pthread_mutex_t	*forks);

//routine
void 	eat_routine(t_philo	*philo);
void	sleep_routine(t_philo	*philo);
void	*routine(void *arg);

//monitor
void set_simulation_stop(t_philo *p);
int is_philo_dead(t_philo *philo);
void monitor_routine(t_philo *philo);


#endif