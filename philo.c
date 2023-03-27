/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:42:00 by nettalha          #+#    #+#             */
/*   Updated: 2023/03/26 22:18:11 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_free(t_philo *ph, pthread_mutex_t *f, pthread_t *th)
{
	free(th);
	free(f);
	free(ph);
}

void	dine(t_philo *ph)
{
	pthread_mutex_lock(ph->right_fork);
	printf("%ld %d has taken a fork\n", get_time() - ph->start_time, ph->id);
	pthread_mutex_lock(ph->left_fork);
	printf("%ld %d has taken a fork\n", get_time() - ph->start_time, ph->id);
	printf("%ld %d is eating\n", get_time() - ph->start_time, ph->id);
	ph->last_meal = get_time();
	ft_usleep(ph->t_to_eat);
	ph->meals++;
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

int	main(int ac, char **av)
{
	pthread_t		*threads;
	t_philo			*philo;
	t_info			info;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;

	if (ac > 1 && check_args(av))
	{
		init_vars(av, &info);
		philo = malloc(sizeof(t_philo) * info.nb_ph);
		forks = malloc(sizeof(pthread_mutex_t) * info.nb_ph);
		threads = malloc(sizeof(pthread_t) * info.nb_ph);
		ft_init_vars(philo, &info);
		ft_init_forks(philo, info.nb_ph, &mutex, forks);
		threads_create(philo, threads);
		ft_usleep(10);
		if (!is_died_or_full(philo, &info))
		{
			destroy_mutex(&info, forks, mutex);
			return (1);
		}
		threads_join(philo, threads);
		ft_free(philo, forks, threads);
	}
	return (0);
}
