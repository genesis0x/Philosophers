/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:41:56 by nettalha          #+#    #+#             */
/*   Updated: 2023/03/17 22:20:24 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<pthread.h>
# include<sys/time.h>

long	get_time(void);
int		ft_atoi(const char *str);
char	**ft_split(const char *s, char c);

typedef	struct philo_s
{
	int		id;
	int		t_to_eat;
	int		t_to_sleep;
	int		t_to_die;
	long	start_time;
}t_philo;

#endif