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
    if (time >= (unsigned long)p->para->t_dead && !p->para->if_dead)
    {
        printf_msg(p, 6);
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
    if (p->para->if_dead)
    {
        pthread_mutex_unlock(&p->para->dead);
        return (1);
    }
    if (!p->para->n_must)
    {
        pthread_mutex_unlock(&p->para->dead);
        return (0);
    }   
    while (++i < p->para->n)
    {
        if (p->meals < p->para->n_must)
        {
            printf("meals:%d %d\n", p->index, p->meals);
            pthread_mutex_unlock(&p->para->dead);
            return (0);
        }
    }
    pthread_mutex_unlock(&p->para->dead);
    return (1);
}