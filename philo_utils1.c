/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:14:47 by nettalha          #+#    #+#             */
/*   Updated: 2023/03/27 12:51:26 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	is_died_or_full(t_philo *ph, t_info *info)
{
	int	i;
	int	n;

	while (1)
	{
		i = 0;
		n = 0;
		while (i < ph->nb_philos)
		{
			if (get_time() - ph[i].last_meal >= ph[i].t_to_die)
			{
				printf("%ld %d died\n", get_time() - ph[i].start_time, ph[i].id);
				return (0);
			}
			if (ph[i].meals != 0 && ph[i].meals >= ph[i].nb_meals && ph[i].nb_meals != -1)
				n++;
			i++;
		}
		if (n == info->nb_ph)
			return (0);
	}
}

void	ft_init_forks(t_philo *ph, int nb_ph, void	*mutex, pthread_mutex_t	*f)
{
	int	i;

	i = 0;
	while (i < nb_ph)
	{
		pthread_mutex_init(mutex, NULL);
		ph[i].mutex = &mutex;
		pthread_mutex_init(&f[i], NULL);
		ph[i].right_fork = &f[i];
		ph[i].left_fork = &f[(i + 1) % nb_ph];
		i++;
	}
}

void	ft_init_vars(t_philo *ph, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_ph)
	{
		ph[i].id = i + 1;
		ph[i].meals = 0;
		ph[i].last_meal = 0;
		ph[i].nb_meals = info->nb_meals;
		ph[i].nb_philos = info->nb_ph;
		ph[i].start_time = get_time();
		ph[i].t_to_die = info->time_to[0];
		ph[i].t_to_eat = info->time_to[1];
		ph[i].t_to_sleep = info->time_to[2];
		i++;
	}
}

void	destroy_mutex(t_info *info, pthread_mutex_t	*f, pthread_mutex_t	m)
{
	int	i;

	i = 0;
	while (i < info->nb_ph)
		pthread_mutex_destroy(&f[i++]);
	pthread_mutex_destroy(&m);
}
