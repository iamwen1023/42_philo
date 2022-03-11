#include "philo.h"

int check_aug(int ac, char **av)
{
    int i;

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

int check_dead(t_philo *p)
{
    unsigned long time;

    pthread_mutex_lock(&p->para->dead);
    time = get_time() - p->lastmeal;
    if (time >= (unsigned long)p->para->t_dead)
    {
        // pthread_mutex_unlock(&p->para->dead);
        // printf_msg(p, 6);
        // pthread_mutex_lock(&p->para->dead);
        time = get_time() - p->para->t_start;
        pthread_mutex_lock(&p->para->msg);
        printf("%lu %d died\n", time, p->index + 1);
        pthread_mutex_unlock(&p->para->msg);
        p->para->if_dead = 1;
        pthread_mutex_unlock(&p->para->dead);
        return (1);
    }
    pthread_mutex_unlock(&p->para->dead);
    return (0);
}

int check_end(t_philo *p)
{
    int i;

    i = -1;
    pthread_mutex_lock(&p->para->dead);
    if (!p->para->n_must || p->para->totalmeals < p->para->n_must)
    {
        pthread_mutex_unlock(&p->para->dead);
        return (0);
    }
    pthread_mutex_unlock(&p->para->dead);
    return (1);
}