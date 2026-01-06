/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:04:26 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/04 22:07:31 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void set_simulation_stop(t_philo *p)
{
    pthread_mutex_lock(&p->settings->stop_lock);
    p->settings->simulation_stopped = 1;
    pthread_mutex_unlock(&p->settings->stop_lock);
}

int is_philo_dead(t_philo *philo)
{
	long now;
	long last_meal;
	
	pthread_mutex_lock(&philo->settings->stop_lock);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->settings->stop_lock);
	
	now = get_time_ms();
	if (now - last_meal >= philo->settings->time_to_die)
	{
		set_simulation_stop(philo);
		pthread_mutex_lock(&philo->settings->write_lock);
		printf("%ld %d died\n", now - philo->settings->start_time, philo->id);
		pthread_mutex_unlock(&philo->settings->write_lock);
		return (1);
	}
	return (0);
}

void monitor_routine(t_philo *philo)
{
	int i;
	long finished_eating;
	
	while (1)
	{
		i = 0;
		while (i < philo[0].settings->n_philos)
		{
			if (is_philo_dead(&philo[i]))
                return ;
			if (philo[i].settings->times_must_eat != -1)
            {
                pthread_mutex_lock(&philo[i].settings->stop_lock);
                if (philo[i].meals_eaten >= philo[i].settings->times_must_eat)
                    finished_eating++;
                pthread_mutex_unlock(&philo[i].settings->stop_lock);
            }
			i++;
		}
		if (philo[0].settings->times_must_eat!= -1 && finished_eating == philo[0].settings->n_philos)
        {
            set_simulation_stop(&philo[0]);
            return ;
        }
	}
}

