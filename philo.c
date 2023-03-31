/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:42:00 by nettalha          #+#    #+#             */
/*   Updated: 2023/03/29 13:06:34 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_free(t_philo *ph, t_mutex *mtx, pthread_t *th)
{
	free(th);
	free(ph);
	free(mtx);
	free(mtx->forks);
	free(mtx->mutex);
	free(mtx->mutex0);
}

void	dine(t_philo *ph)
{
	pthread_mutex_lock(ph->right_fork);
	printf("%ld %d has taken a fork\n", get_time() - ph->start_time, ph->id);
	pthread_mutex_lock(ph->left_fork);
	printf("%ld %d has taken a fork\n", get_time() - ph->start_time, ph->id);
	printf("%ld %d is eating\n", get_time() - ph->start_time, ph->id);
	pthread_mutex_lock(ph->mutex0);
	ph->last_meal = get_time();
	pthread_mutex_unlock(ph->mutex0);
	ft_usleep(ph->t_to_eat);
	pthread_mutex_lock(ph->mutex0);
	ph->m++;
	pthread_mutex_unlock(ph->mutex0);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
}

void	*philos_routine(void *void_philo)
{
	t_philo	*ph;

	ph = (t_philo *)void_philo;
	printf("%ld %d is thinking\n", get_time() - ph->start_time, ph->id);
	if (ph->id % 2 == 0)
		ft_usleep(1.5);
	while (1)
	{
		dine(ph);
		pthread_mutex_lock(ph->mutex);
		printf("%ld %d is sleeping\n", get_time() - ph->start_time, ph->id);
		pthread_mutex_unlock(ph->mutex);
		ft_usleep(ph->t_to_sleep);
		pthread_mutex_lock(ph->mutex);
		printf("%ld %d is thinking\n", get_time() - ph->start_time, ph->id);
		pthread_mutex_unlock(ph->mutex);
	}
}

void	mutex_malloc(t_mutex *mtx, t_info info)
{
	mtx->forks = malloc(sizeof(pthread_mutex_t) * info.nb_ph);
	mtx->mutex = malloc(sizeof(pthread_mutex_t) * info.nb_ph);
	mtx->mutex0 = malloc(sizeof(pthread_mutex_t));
}

int	main(int ac, char **av)
{
	pthread_t		*threads;
	t_philo			*philo;
	t_info			info;
	t_mutex			*mtx;

	if (ac > 1 && check_args(av))
	{
		init_vars(av, &info);
		threads = malloc(sizeof(pthread_t) * info.nb_ph);
		philo = malloc(sizeof(t_philo) * info.nb_ph);
		mtx = malloc(sizeof(mtx));
		mutex_malloc(mtx, info);
		ft_init_vars(philo, &info);
		ft_init_mutex(philo, mtx->mutex, mtx->mutex0, mtx->forks);
		threads_create(philo, threads);
		ft_usleep(10);
		if (!is_died_or_full(philo, &info))
		{
			destroy_mutex(&info, mtx->forks, mtx->mutex);
			return (1);
		}
		threads_join(philo, threads);
		ft_free(philo, mtx, threads);
	}
	return (0);
}
