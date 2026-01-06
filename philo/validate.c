/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <ric.costamoraes@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 17:44:42 by rida-cos          #+#    #+#             */
/*   Updated: 2026/01/05 23:51:59 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (write(2, "Error: Wrong number of argument\n", 33));
	if (ft_atoi(argv[1]) > PHILO_MAX || !(is_number(argv[1]))
		|| ft_atoi(argv[1]) <= 0)
		return (write(2, "Invalid number of philosophers\n", 32), 1);
	if (ft_atoi(argv[2]) <= 0 || !(is_number(argv[2])))
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || !(is_number(argv[3])))
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || !(is_number(argv[4])))
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || !(is_number(argv[5]))))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}
