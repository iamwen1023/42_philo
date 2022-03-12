/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:15:42 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/03/12 14:31:05 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_msg(t_philo *p, int i)
{
	char	*str;

	str = NULL;
	if (i == 1)
		str = "has taken a fork\n";
	else if (i == 3)
		str = "is eating\n";
	else if (i == 4)
		str = "is sleeping\n";
	else if (i == 5)
		str = "is thinking\n";
	else if (i == 6)
		str = "died\n";
	pthread_mutex_lock(&p->para->dead);
	if (p->para->if_dead || p->para->totalmeals == p->para->n_must)
	{
		pthread_mutex_unlock(&p->para->dead);
		return ;
	}
	printf("%lu %d %s", get_time() - p->para->t_start, p->index + 1, str);
	pthread_mutex_unlock(&p->para->dead);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (1000 * (tv.tv_sec) + (tv.tv_usec) / 1000);
}

void	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(400);
}
