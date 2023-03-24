/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:42:00 by nettalha          #+#    #+#             */
/*   Updated: 2023/03/24 22:30:17 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"philo.h"


void	dine(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
	pthread_mutex_lock(philo->left_fork);
	printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
	printf("%ld %d is eating\n", get_time() - philo->start_time, philo->id);
	philo->last_meal = get_time();
	usleep(philo->t_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *void_philo)
{
	t_philo	*philo;
	philo = (t_philo *)void_philo;
	printf("%ld %d is thinking\n", get_time() - philo->start_time, philo->id);

	if(philo->id % 2 == 0)
		usleep(1500);
	while(1)
	{
		dine(philo);
		pthread_mutex_lock(philo->mutex);
		printf("%ld %d is sleeping\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->mutex);
		usleep(philo->t_to_sleep * 1000);
		pthread_mutex_lock(philo->mutex);
		printf("%ld %d is thinking\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->mutex);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	*threads;
	t_philo		*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	int			time_to[3];
	int			nb_philos;
	int			i;
	int			r;

	if (ac > 1)
	{
		time_to[0] = ft_atoi(av[2]);
		time_to[1] = ft_atoi(av[3]);
		time_to[2] = ft_atoi(av[4]);
		nb_philos = ft_atoi(av[1]);
		philo = malloc(sizeof(t_philo) * nb_philos);
		forks = malloc(sizeof(pthread_mutex_t) * nb_philos);
		philo = malloc(sizeof(t_philo) * nb_philos);
		threads = malloc(sizeof(pthread_t) * nb_philos);
		pthread_mutex_init(&mutex, NULL);
		if (ac < 2)
		{
			printf("it should be atleast one philo");
			return 1;
		}
		i = 0;
		while (i < nb_philos)
		{
			philo[i].id = i;
			philo[i].right_fork = &forks[i];
			philo[i].left_fork = &forks[(i + 1) % nb_philos];
			philo[i].nb_philos = nb_philos;
			philo[i].start_time = get_time();
			philo[i].t_to_die = time_to[0];
			philo[i].t_to_eat = time_to[1];
			philo[i].t_to_sleep = time_to[2];
			pthread_mutex_init(&forks[i], NULL);
			i++;
		}
		i = 0;
		while (i < philo->nb_philos)
		{
			philo[i].mutex = &mutex;
			philo[i].last_meal = get_time();
			r = pthread_create(&threads[i], NULL, philo_routine, &philo[i]);
			if (r)
			{
				printf("Failed to create thread %d\n", i);
				exit(1);
			}
			i++;
		}
		i = 0;
		while (1)
		{
			i = 0;
			while (i < philo->nb_philos)
			{
				if (get_time() - philo[i].last_meal >= philo[i].t_to_die)
				{
					printf("%ld %d died\n", get_time() - philo[i].start_time, philo[i].id);
					pthread_mutex_destroy(&forks[i]);
					pthread_mutex_destroy(&mutex);
					return (0);
				}
				i++;
			}
		}
		i = 0;
		while (i < philo->nb_philos)
		{
			pthread_join(threads[i], NULL);
			i++;
		}
		free(threads);
		free(forks);
		free(philo);
	}
	return (1);
}
