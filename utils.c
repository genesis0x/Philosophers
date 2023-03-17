/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:13:59 by nettalha          #+#    #+#             */
/*   Updated: 2023/03/12 12:14:03 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += (str[i] - 48);
		i++;
	}
	return (res * sign);
}

int	countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count + 1);
}

int	countletter(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i + 1);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	int		i;
	int		j;

	ptr = malloc((countwords(s, c)) * sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s)
		{
			ptr[i] = malloc(countletter(s, c) * sizeof(char));
			j = 0;
			while (*s != '\0' && *s != c)
				ptr[i][j++] = *s++;
			ptr[i][j] = '\0';
			i++;
		}
	}
	ptr[i] = NULL;
	return (ptr);
}

