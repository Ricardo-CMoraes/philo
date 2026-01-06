/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:33:08 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/06 00:12:08 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_routine(t_philo	*philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_action(philo, "has taken a fork");
	if (philo->settings->n_philos == 1)
	{
		precise_usleep(philo->settings->time_to_die, philo);
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	pthread_mutex_lock(philo->second_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->settings->stop_lock);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->settings->stop_lock);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->settings->stop_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->settings->stop_lock);
	precise_usleep(philo->settings->time_to_eat, philo);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}

void	sleep_routine(t_philo	*philo)
{
	if (is_simulation_over(philo))
		return ;
	print_action(philo, "is sleeping");
	precise_usleep(philo->settings->time_to_sleep, philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(philo->settings->time_to_eat / 2, philo);
	while (!is_simulation_over(philo))
	{
		eat_routine(philo);
		sleep_routine(philo);
		print_action(philo, "is thinking");
		print_action(philo, "is thinking");
		if (philo->settings->n_philos % 2 != 0)
			precise_usleep(1, philo);
	}
	return (NULL);
}
