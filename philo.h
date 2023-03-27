/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:41:56 by nettalha          #+#    #+#             */
/*   Updated: 2023/03/26 21:47:42 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<pthread.h>
# include<sys/time.h>

typedef struct s_philo
{
	int		id;
	int		t_to_eat;
	int		t_to_sleep;
	int		t_to_die;
	long	last_meal;
	long	start_time;
	int		nb_meals;
	int		meals;
	int		nb_philos;
	void	*mutex;
	void	*right_fork;
	void	*left_fork;
}t_philo;

typedef struct s_info
{
	int		time_to[3];
	int		nb_meals;
	int		nb_ph;
}t_info;

long	get_time(void);
void	ft_usleep(float time);
int		is_died_or_full(t_philo *ph, t_info *info);
int		ft_atoi(const char *str);
int		check_args(char **av);
void	init_vars(char **av, t_info *info);
void	ft_init_vars(t_philo *ph, t_info *info);
void	destroy_mutex(t_info *info, pthread_mutex_t	*f, pthread_mutex_t	m);
void	ft_free(t_philo *ph, pthread_mutex_t *f, pthread_t *th);
void	ft_init_forks(t_philo *ph, int nb_ph, void	*mutex, pthread_mutex_t	*f);
void	threads_create(t_philo *philos, pthread_t	*threads);
void	threads_join(t_philo *philos, pthread_t *threads);
void	*philos_routine(void *void_philo);
#endif
