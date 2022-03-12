/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:15:36 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/03/12 14:41:36 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*case_one(t_philo *p)
{
	printf_msg(p, 1);
	ft_usleep((unsigned long)p->para->t_dead);
	printf_msg(p, 6);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)(arg);
	if (p->para->n == 1)
		return (case_one(p));
	printf_msg(p, 5);
	while (!check_dead(p))
	{
		if (take_fork(p))
		{
			remove_fork(p);
			return (NULL);
		}
		if (eat(p))
		{
			remove_fork(p);
			return (NULL);
		}
		if (ft_sleep(p))
			return (NULL);
		if (thinking(p))
			return (NULL);
	}
	return (0);
}

int	run(t_para *para)
{
	int		i;
	void	*p;

	i = -1;
	para->t_start = get_time();
	while (++i < para->n)
	{
		para->philos[i].lastmeal = para->t_start;
		p = (void *)&para->philos[i];
		if (pthread_create(&para->philos[i].thread, NULL, routine, (void *)p))
			return (1);
	}
	i = -1;
	while (++i < para->n)
	{
		if (pthread_join(para->philos[i].thread, NULL))
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_para	para;

	if (ac < 5 || ac > 6 || check_aug(ac, av))
	{
		printf("Arguments errors\n");
		return (1);
	}
	if (initial(&para, av))
	{
		printf("Something went wrong while executing\n");
		free_para(&para);
		return (1);
	}
	if (run(&para))
	{
		printf("Something went wrong while executing\n");
		free_para(&para);
		return (1);
	}
	free_para(&para);
	printf("end\n");
	return (0);
}
