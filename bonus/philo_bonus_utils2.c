/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:40:58 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/11 01:41:15 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

long	get_time(void)
{
	struct timeval	t;
	long			time;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

void	process_create(t_philo *ph)
{
	int		i;

	i = 0;
	while (i < ph->nb_ph)
	{
		ph->pid[i] = fork();
		if (ph->pid[i] == 0)
			philos_routine(&ph[i]);
		i++;
	}
	ft_usleep(1);
}

void	threads_join(t_philo *philos, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < philos->nb_ph)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	threads_detach(t_philo *philos, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < philos->nb_ph)
	{
		pthread_detach(threads[i]);
		i++;
	}
}

void	init_vars(char **av, t_info *info)
{
	info->time_to[0] = ft_atoi(av[2]);
	info->time_to[1] = ft_atoi(av[3]);
	info->time_to[2] = ft_atoi(av[4]);
	if (av[5])
		info->nb_meals = ft_atoi(av[5]);
	else
		info->nb_meals = -1;
	info->nb_ph = ft_atoi(av[1]);
}
