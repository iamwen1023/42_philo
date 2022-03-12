/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:15:10 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/03/12 14:04:01 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_aug(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (ft_atoi(av[i]) <= 0 || !if_num(av[i]))
			return (1);
		if (i == 1 && ft_atoi(av[i]) > 200)
			return (1);
	}
	return (0);
}

int	check_dead(t_philo *p)
{
	if (get_time() - p->lastmeal >= (unsigned long)p->para->t_dead)
	{
		printf_msg(p, 6);
		pthread_mutex_lock(&p->para->dead);
		p->para->if_dead = 1;
		pthread_mutex_unlock(&p->para->dead);
		return (1);
	}
	pthread_mutex_lock(&p->para->dead);
	if (p->para->if_dead)
	{
		pthread_mutex_unlock(&p->para->dead);
		return (1);
	}
	pthread_mutex_unlock(&p->para->dead);
	return (0);
}

int	check_end(t_philo *p)
{
	if (p->para->n_must < 0)
		return (0);
	pthread_mutex_lock(&p->para->dead);
	if (p->para->totalmeals == p->para->n)
	{
		p->para->if_dead = 1;
		pthread_mutex_unlock(&p->para->dead);
		return (1);
	}
	pthread_mutex_unlock(&p->para->dead);
	return (0);
}
