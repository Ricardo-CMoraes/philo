/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:42:00 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/04 21:53:13 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	nb;
	int	i;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == ' ' || ((str[i] >= 9) && (str[i] <= 13)))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
		if (str[i] == '-' || str[i] == '+')
			return (0);
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

long get_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void print_action(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&(philo->settings->write_lock));
	if (!is_simulation_over(philo))
		printf("%ld %d %s\n", get_time_ms() - philo->settings->start_time, philo->id, msg);
	pthread_mutex_unlock(&(philo->settings->write_lock)); 
}

void precise_usleep(long time_to_wait, t_philo *philo)
{
    long start_time;

    start_time = get_time_ms();
    while ((get_time_ms() - start_time) < time_to_wait)
    {
        if (is_simulation_over(philo))
            break;
        usleep(500);
    }
}

int is_simulation_over(t_philo *p)
{
    int stopped;

    pthread_mutex_lock(&p->settings->stop_lock);
    stopped = p->settings->simulation_stopped;
    pthread_mutex_unlock(&p->settings->stop_lock);
    return (stopped);
}
//has taken a fork
//is eating
//is sleeping
//is thinking
//diead