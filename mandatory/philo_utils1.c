/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:14:47 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/11 15:28:59 by nettalha         ###   ########.fr       */
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
		while (i < ph[i].nb_ph)
		{
			//pthread_mutex_lock(ph[i].mtx->mutex1);
			if (get_time() - ph[i].last_meal >= ph[i].t_to_die)
			{
				//pthread_mutex_lock(ph[i].mtx->mutex2);
				printf("%ld %d died\n", get_time() - ph[i].start_time, ph[i].id);
				//pthread_mutex_unlock(ph[i].mutex);
				return (0);
			}
			if (ph[i].m != 0 && ph[i].m >= ph[i].nb_m && ph[i].nb_m != -1)
				n++;
			//pthread_mutex_unlock(ph[i].mtx->mutex1);
			i++;
		}
		if (n == info->nb_ph)
			return (0);
	}
}

void	ft_init_mutex(t_philo *ph)
{
	int	i;
	ph->mtx->forks = malloc(sizeof(pthread_mutex_t) * ph->nb_ph);
	ph->mtx->mutex1 = malloc(sizeof(pthread_mutex_t));
	//ph->mtx->mutex2 = malloc(sizeof(pthread_mutex_t));
	if ((pthread_mutex_init(ph->mtx->mutex1, NULL)) < 0)
		printf("init failed\n");
	//if (pthread_mutex_init(ph->mtx->mutex2, NULL) < 0)
	//	printf("init failed\n");
	i = 0;
	while (i < ph->nb_ph)
	{
		pthread_mutex_init(&ph->mtx->forks[i], NULL);
		ph[i].right_fork = &ph->mtx->forks[i];
		ph[i].left_fork = &ph->mtx->forks[(i + 1) % ph->nb_ph];
		i++;
	}
}

void	ft_init_vars(t_philo *ph, t_info *info)
{
	int		i;
	long	time;

	i = 0;
	time = get_time();
	while (i < info->nb_ph)
	{
		ph[i].id = i + 1;
		ph[i].m = 0;
		ph[i].last_meal = 0;
		ph[i].nb_m = info->nb_meals;
		ph[i].nb_ph = info->nb_ph;
		ph[i].start_time = time;
		ph[i].t_to_die = info->time_to[0];
		ph[i].t_to_eat = info->time_to[1];
		ph[i].t_to_sleep = info->time_to[2];
		i++;
	}
}

void	destroy_mutex(t_info *info, t_mutex	*mtx)
{
	int	i;

	i = 0;
	while (i < info->nb_ph)
	{
		pthread_mutex_destroy(&mtx->forks[i]);
		i++;
	}
	pthread_mutex_destroy(mtx->mutex1);
	//pthread_mutex_destroy(mtx->mutex2);
}

void	ft_free(t_philo *ph, t_mutex *mtx, pthread_t *th)
{
	free(th);
	free(ph);
	free(mtx->forks);
	free(mtx);
}
