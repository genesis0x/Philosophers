/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:42:00 by nettalha          #+#    #+#             */
/*   Updated: 2023/03/17 22:28:58 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"philo.h"

pthread_mutex_t	mutex;

void	dine(t_philo *philo)
{
	pthread_mutex_lock(&mutex);
	printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
	printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(&mutex);
	printf("%ld %d is eating\n", get_time() - philo->start_time, philo->id);
	usleep(philo->t_to_eat);
}

void	*philo_routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if(philo->id % 2 == 0)
		usleep(1500);
	printf("%ld %d is thinking \n", get_time() - (philo)->start_time, philo->id);
	while(1)
	{
		dine(philo);
		pthread_mutex_lock(&mutex);
		printf("%ld %d is sleeping\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(&mutex);

		usleep(philo->t_to_sleep);

		pthread_mutex_lock(&mutex);
		printf("%ld %d is thinking\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	*threads;
	t_philo		*philos;
	int			nb_philos;
	int			time_to[3];
	int			i;

	if (ac > 1)
	{
		nb_philos = ft_atoi(av[1]);
		time_to[0] = ft_atoi(av[2]);
		time_to[1] = ft_atoi(av[3]);
		time_to[2] = ft_atoi(av[4]);
		threads = malloc(sizeof(pthread_t) * nb_philos);
		philos = malloc(sizeof(t_philo) * nb_philos);
		pthread_mutex_init(&mutex, NULL);
		if (ac < 2)
		{
			printf("it should be atleast one philo");
			return 1;
		}
		i = nb_philos - 1;
		while (i >= 0)
		{
			philos[i].start_time = get_time();
			philos[i].id = i + 1;
			philos[i].t_to_die = time_to[0];
			philos[i].t_to_eat = time_to[1];
			philos[i].t_to_sleep = time_to[2];
			i--;
		}
		i = 0;
		while (i < nb_philos)
		{
			pthread_create(&threads[i], NULL, philo_routine, &philos[i]);
			i++;
		}
		i = 0;
		while (i < nb_philos)
		{
			pthread_join(threads[i], NULL);
			i++;
		}
		pthread_mutex_destroy(&mutex);
		free(threads);
		free(philos);
	}
	return (1);
}
