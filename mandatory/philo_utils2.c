/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 22:40:54 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/11 15:09:04 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long	get_time(void)
{
	struct timeval	t;
	long			time;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

void	threads_create(t_philo *philos, pthread_t *threads)
{
	int	i;
	int	r;

	i = 0;
	while (i < philos->nb_ph)
	{
		philos[i].last_meal = get_time();
		r = pthread_create(&threads[i], NULL, philos_routine, (void *)(&philos[i]));
		if (r)
		{
			printf("Failed to create thread %d\n", i);
			exit(1);
		}
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
