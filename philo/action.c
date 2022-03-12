/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:14:55 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/03/12 16:22:09 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *p)
{
	int	firstfork;
	int	secondfork;

	if (check_dead(p))
		return (1);
	if (p->index % 2 == 0)
	{
		ft_usleep(1);
		firstfork = p->index;
		secondfork = (p->index + 1) % p->para->n;
	}
	else
	{
		secondfork = p->index;
		firstfork = (p->index + 1) % p->para->n;
	}
	pthread_mutex_lock(&p->para->forks[firstfork]);
	p->lfork = 1;
	printf_msg(p, 1);
	pthread_mutex_lock(&p->para->forks[secondfork]);
	p->rfork = 1;
	printf_msg(p, 1);
	return (0);
}

void	remove_fork(t_philo *p)
{
	int	firstfork;
	int	secondfork;

	if (p->index % 2 == 0)
	{
		firstfork = p->index;
		secondfork = (p->index + 1) % p->para->n;
	}
	else
	{
		secondfork = p->index;
		firstfork = (p->index + 1) % p->para->n;
	}
	if (p->lfork == 1)
	{
		p->lfork = 0;
		pthread_mutex_unlock(&p->para->forks[firstfork]);
	}
	if (p->rfork == 1)
	{
		p->rfork = 0;
		pthread_mutex_unlock(&p->para->forks[secondfork]);
	}
}

int	eat(t_philo *p)
{
	if (check_dead(p))
		return (1);
	p->lastmeal = get_time();
	printf_msg(p, 3);
	if (p->para->t_dead <= p->para->t_eat)
	{
		ft_usleep(p->para->t_dead);
		printf_msg(p, 6);
		pthread_mutex_lock(&p->para->dead);
		p->para->if_dead = 1;
		pthread_mutex_unlock(&p->para->dead);
		return (1);
	}
	p->meals = p->meals + 1;
	pthread_mutex_lock(&p->para->dead);
	if (p->para->n_must > 0 && p->meals == p->para->n_must)
		p->para->totalmeals += 1;
	pthread_mutex_unlock(&p->para->dead);
	if (check_end(p))
		return (1);
	ft_usleep(p->para->t_eat);
	remove_fork(p);
	if (check_dead(p))
		return (1);
	return (0);
}

int	ft_sleep(t_philo *p)
{
	if (check_dead(p))
		return (1);
	if (p->para->t_dead <= p->para->t_slp || \
		p->para->t_dead <= p->para->t_eat + p->para->t_slp)
	{
		printf_msg(p, 4);
		ft_usleep(p->para->t_dead - p->para->t_eat);
		printf_msg(p, 6);
		pthread_mutex_lock(&p->para->dead);
		p->para->if_dead = 1;
		pthread_mutex_unlock(&p->para->dead);
		return (1);
	}
	printf_msg(p, 4);
	ft_usleep(p->para->t_slp);
	if (check_dead(p))
		return (1);
	return (0);
}

int	thinking(t_philo *p)
{
	int				time;

	if (check_dead(p))
		return (1);
	printf_msg(p, 5);
	time = p->para->t_dead - p->para->t_eat - p->para->t_slp;
	if (p->para->t_dead <= p->para->t_eat * 2 || \
	(p->para->t_dead <= (p->para->t_eat * 2 + p->para->t_slp) && \
	p->para->n % 2 != 0))
	{
		ft_usleep((unsigned long)time);
		printf_msg(p, 6);
		pthread_mutex_lock(&p->para->dead);
		p->para->if_dead = 1;
		pthread_mutex_unlock(&p->para->dead);
		return (1);
	}
	return (0);
}
