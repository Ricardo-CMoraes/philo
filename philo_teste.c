/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 22:19:15 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/01 18:32:21 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

void *computation(void *add);

int main()
{
	pthread_t	thread1;

	long value1 = 5;

	pthread_create(&thread1, NULL, computation, (void*) &value1);

	pthread_join(thread1, NULL);
	
	return (0);
}

void *computation(void *add)
{
	long *add_num = (long *) (add);
	
	printf("Add: %ld\n", *add_num);
	return (NULL);
}