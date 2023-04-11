/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:40:08 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/11 01:48:47 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"philo_bonus.h"

void	dine(t_philo *ph)
{
	sem_wait(ph->right_fork);
	printf("%ld %d has taken a fork\n", get_time() - ph->start_time, ph->id);
	sem_wait(ph->left_fork);
	printf("%ld %d has taken a fork\n", get_time() - ph->start_time, ph->id);
	printf("%ld %d is eating\n", get_time() - ph->start_time, ph->id);
	sem_wait(ph->sem1);
	ph->last_meal = get_time();
	sem_post(ph->sem1);
	ft_usleep(ph->t_to_eat);
	sem_wait(ph->sem1);
	ph->m++;
	sem_post(ph->sem1);
	sem_post(ph->right_fork);
	sem_post(ph->left_fork);
}

void	*philos_routine(t_philo *ph)
{
	pthread_t	thread;
	pthread_create(&thread, NULL, is_died_or_full, &ph);
	printf("%ld %d is thinking\n", get_time() - ph->start_time, ph->id);
	if (ph->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		dine(ph);
		sem_wait(ph->sem0);
		printf("%ld %d is sleeping\n", get_time() - ph->start_time, ph->id);
		sem_post(ph->sem0);
		ft_usleep(ph->t_to_sleep);
		sem_wait(ph->sem0);
		printf("%ld %d is thinking\n", get_time() - ph->start_time, ph->id);
		sem_post(ph->sem0);
	}
}

void	init_all(t_philo *ph, t_sem *sem, t_info info)
{
	sem->forks = malloc(sizeof(sem_t) * info.nb_ph);
	ft_init_vars(ph, &info);
	ft_init_sem(ph, &sem->sem0, &sem->sem1, sem->forks);
}

int	main(int ac, char **av)
{
	pthread_t		*threads;
	t_philo			*philo;
	t_info			info;
	t_sem			*sem;

	if (ac > 1 && check_args(av))
	{
		init_vars(av, &info);
		threads = malloc(sizeof(pthread_t) * info.nb_ph);
		philo = malloc(sizeof(t_philo) * info.nb_ph);
		philo->pid = malloc(sizeof(pid_t) * info.nb_ph);
		sem = malloc(sizeof(sem));
		init_all(philo, sem, info);
		process_create(philo);
		waitpid(-1, NULL, 0);
		// threads_join(philo, threads);
		// destroy_sem(&info, sem);
		// ft_free(philo, sem, threads);
	}
	return (0);
}
