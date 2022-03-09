#include "philo.h"
void    printf_msg(t_philo *p, int i)
{
    unsigned long tf;

    pthread_mutex_lock(&p->para->msg);
    tf = get_time() - p->para->t_start;
    if (i == 1)
        printf("[%lu ms] #%d has a fork\n", tf, p->index + 1);
    else if (i == 2)
        printf("[%lu ms] #%d has a rfork\n", tf, p->index + 1);
    else if (i == 3)
        printf("[%lu ms] #%d is eating\n", tf, p->index + 1);
    else if (i == 4)
        printf("[%lu ms] #%d is sleeping\n", tf, p->index + 1);
    else if (i == 5)
        printf("[%lu ms] #%d is thinking\n", tf, p->index + 1);
    else if (i == 6)
        printf("[%lu ms] #%d died\n", tf, p->index + 1);
    pthread_mutex_unlock(&p->para->msg);
}

unsigned long get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL); 
	return (1000 * (unsigned long)(tv.tv_sec) + (unsigned long)(tv.tv_usec) / 1000);
}

void    ft_usleep(unsigned long time)
{
    unsigned long   start;

    start = get_time();
    while(get_time() - start < time)
        usleep(100);
}


