/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:32:25 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/05 22:51:37 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_settings(t_settings *settings, int argc, char **argv)
{
	settings->n_philos = (ft_atoi(argv[1]));
	settings->time_to_die = (long)(ft_atoi(argv[2]));
	settings->time_to_eat = (long)(ft_atoi(argv[3]));
	settings->time_to_sleep = (long)(ft_atoi(argv[4]));
	if (argc == 6)
		settings->times_must_eat = (int)(ft_atoi(argv[5]));
	else
		settings->times_must_eat = -1;
	pthread_mutex_init(&settings->write_lock, NULL);
	pthread_mutex_init(&settings->stop_lock, NULL);
	settings->simulation_stopped = 0;
}

void	set_forks(t_philo *p, pthread_mutex_t *forks, t_settings *stngs, int i)
{
	if (i % 2 == 0)
	{
		p[i].first_fork = &forks[(i + 1) % stngs->n_philos];
		p[i].second_fork = &forks[i];
	}
	else
	{
		p[i].first_fork = &forks[i];
		p[i].second_fork = &forks[(i + 1) % stngs->n_philos];
	}
}

pthread_mutex_t	*init_forks(t_settings *settings)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * settings->n_philos);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < settings->n_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo	*init_philo(t_settings *settings, pthread_mutex_t *forks)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * settings->n_philos);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < settings->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = 0;
		set_forks(philo, forks, settings, i);
		philo[i].settings = settings;
		i++;
	}
	return (philo);
}

int	init_threads(t_philo *philo)
{
	int	i;
	int	n;

	n = philo->settings->n_philos;
	i = 0;
	philo->settings->start_time = get_time_ms();
	while (i < n)
	{
		philo[i].last_meal_time = get_time_ms();
		if (pthread_create(&philo[i].thread, NULL, &routine,
				(void *)&philo[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}
