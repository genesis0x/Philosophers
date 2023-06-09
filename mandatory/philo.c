/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:42:00 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/11 15:28:34 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	dine(t_philo *ph)
{
	pthread_mutex_lock(ph->right_fork);
	printf("%ld %d has taken a fork\n", get_time() - ph->start_time, ph->id);
	pthread_mutex_lock(ph->left_fork);
	printf("%ld %d has taken a fork\n", get_time() - ph->start_time, ph->id);
	printf("%ld %d is eating\n", get_time() - ph->start_time, ph->id);
	//pthread_mutex_lock(ph->mtx->mutex2);
	ph->last_meal = get_time();
	//pthread_mutex_unlock(ph->mtx->mutex2);
	ft_usleep(ph->t_to_eat);
	//pthread_mutex_lock(ph->mtx->mutex2);
	ph->m++;
	// pthread_mutex_unlock(ph->mtx->mutex2);
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
		pthread_mutex_lock(ph->mtx->mutex1);
		printf("%ld %d is sleeping\n", get_time() - ph->start_time, ph->id);
		pthread_mutex_unlock(ph->mtx->mutex1);
		ft_usleep(ph->t_to_sleep);
		pthread_mutex_lock(ph->mtx->mutex1);
		printf("%ld %d is thinking\n", get_time() - ph->start_time, ph->id);
		pthread_mutex_unlock(ph->mtx->mutex1);
	}
}

void	init_all(t_philo *ph, t_info info)
{
	ph->mtx = (t_mutex *)malloc(sizeof(t_mutex));
	ft_init_vars(ph, &info);
	ft_init_mutex(ph);
}

int	main(int ac, char **av)
{
	pthread_t		*threads;
	(void)threads;
	t_philo			*philo;
	t_info			info;
	// t_mutex			*mtx;

	if (ac > 1 && check_args(av))
	{
		init_vars(av, &info);
		threads = malloc(sizeof(pthread_t) * info.nb_ph);
		philo = malloc(sizeof(t_philo) * info.nb_ph);
		philo->mtx = malloc(sizeof(t_mutex));
		init_all(philo, info);
		threads_create(philo, threads);
		if (!is_died_or_full(philo, &info))
		{
			threads_detach(philo, threads);
			destroy_mutex(&info, philo->mtx);
			ft_free(philo, philo->mtx, threads);
			return (1);
		}
		threads_join(philo, threads);
		destroy_mutex(&info, philo->mtx);
		// ft_free(philo, philo->mtx, threads);
	}
	return (0);
}
