/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:41:56 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/11 01:38:17 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<pthread.h>
# include<semaphore.h>
# include<sys/time.h>

typedef struct s_philo
{
	int		id;
	int		t_to_eat;
	int		t_to_sleep;
	int		t_to_die;
	long	last_meal;
	long	start_time;
	int		nb_m;
	int		m;
	int		nb_ph;
	void	*sem0;
	void	*sem1;
	void	*right_fork;
	void	*left_fork;
	pid_t	*pid;
}t_philo;

typedef struct s_info
{
	int		time_to[3];
	int		nb_meals;
	int		nb_ph;
}t_info;

typedef struct s_sem
{
	sem_t	*forks;
	sem_t	sem0;
	sem_t	sem1;
}t_sem;

long	get_time(void);
void	ft_usleep(float time);
void	*is_died_or_full(void *void_ph);
int		ft_atoi(const char *str);
int		check_args(char **av);
void	init_vars(char **av, t_info *info);
void	ft_init_vars(t_philo *ph, t_info *info);
void	destroy_sem(t_info *info, t_sem	*sem);
void	ft_free(t_philo *ph, t_sem *sem, pthread_t *th);
void	ft_init_sem(t_philo *ph, void	*s0, void *s1, sem_t *f);
void	process_create(t_philo *philos);
void	threads_join(t_philo *philos, pthread_t *threads);
void	threads_detach(t_philo *philos, pthread_t *threads);
void	*philos_routine(t_philo *ph);
#endif
