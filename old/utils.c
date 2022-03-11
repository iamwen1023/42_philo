#include "philo.h"
void    printf_msg(t_philo *p, int i)
{
    unsigned long tf;
    char *str;

    str = NULL;
    pthread_mutex_lock(&p->para->dead);
    if (p->para->if_dead || \
        (p->para->n_must && p->para->totalmeals == p->para->n_must))
    {
        pthread_mutex_unlock(&p->para->dead);
        return ;
    }
    pthread_mutex_unlock(&p->para->dead);
    if (i == 1)
        str="has taken a fork\n";
    else if (i == 3)
        str="is eating\n";
    else if (i == 4)
        str="is sleeping\n";
    else if (i == 5)
        str="is thinking\n";
    else if (i == 6)
        str="died\n";
    tf = get_time() - p->para->t_start;
    pthread_mutex_lock(&p->para->msg);
    printf("%lu %d %s", tf, p->index + 1, str);
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


