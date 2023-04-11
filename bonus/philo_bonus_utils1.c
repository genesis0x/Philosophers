/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:40:42 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/11 01:32:46 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

void	*is_died_or_full(void *void_ph)
{
	t_philo	*ph;

	ph = (t_philo *)void_ph;
	while (1)
	{
		sem_wait(ph->sem1);
		if (get_time() - ph->last_meal >= ph->t_to_die)
		{
			sem_wait(ph->sem0);
			printf("%ld %d died\n", get_time() - ph->start_time, ph->id);
			exit(0);
		}
		if (ph->m != 0 && ph->m >= ph->nb_m && ph->nb_m != -1)
			exit(0);
		sem_post(ph->sem1);
	}
}

void	ft_init_sem(t_philo *ph, void *s0, void *s1, sem_t *f)
{
	int	i;

	sem_open(s0, 1, 1);
	sem_open(s1, 1, 1);
	i = 0;
	while (i < ph[i].nb_ph)
	{
		ph[i].sem0 = s0;
		ph[i].sem1 = s1;
		sem_open((void*)&f[i], 1, 1);
		ph[i].right_fork = &f[i];
		ph[i].left_fork = &f[(i + 1) % ph[i].nb_ph];
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

void	destroy_sem(t_info *info, t_sem	*sem)
{
	int	i;

	i = 0;
	while (i < info->nb_ph)
	{
		sem_close(&sem->forks[i]);
		i++;
	}
	sem_close(&sem->sem0);
	sem_close(&sem->sem1);
}

void	ft_free(t_philo *ph, t_sem *sem, pthread_t *th)
{
	free(th);
	free(ph);
	free(sem->forks);
	free(sem);
}
