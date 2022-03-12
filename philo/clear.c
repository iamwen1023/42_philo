/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:15:16 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/03/12 15:05:34 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_para(t_para *para)
{
	int	i;

	i = -1;
	if (para)
	{
		if (para->philos)
			free(para->philos);
		if (para->forks)
		{
			while (++i < para->n)
				pthread_mutex_destroy(&para->forks[i]);
		}
		pthread_mutex_destroy(&para->dead);
		if (para->forks)
			free(para->forks);
	}
}
