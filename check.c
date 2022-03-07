#include "philo.h"

int check_aug(int ac, char **av)
{
    int i;

    i = 0;
    while (++i < ac)
    {
        if (ft_atoi(av[i]) < 0 || !if_num(av[i]))
            return (1);
    }
    return (0);
}

int check_dead(t_philo *p, unsigned long tf)
{
    unsigned long time;

    time = tf - p->lastmeal;
    pthread_mutex_lock(&p->para->dead);
    if (time > (unsigned long)p->para->t_dead)
    {
        printf_msg(tf, p, 6);
        return (1);
    }
    pthread_mutex_unlock(&p->para->dead);
    return (0);
}

int check_end(t_philo *p)
{
    int i;

    i = -1;
    if (!p->para->n_must)
        return (0);
    pthread_mutex_lock(&p->para->dead);
    while (++i < p->para->n)
    {
        if (p->meals < p->para->totalmeals)
            return (0);
    }
    pthread_mutex_unlock(&p->para->dead);
    return (1);
}