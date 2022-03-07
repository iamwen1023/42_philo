#include "philo.h"

void init_philo(t_para *para)
{
    int i;

    i = -1;
    while (++i < para->n)
    {
        para->philos[i].index = i;
        para->philos[i].para = para;
        para->philos[i].lastmeal = 0;
        para->philos[i].meals = 0;
        para->philos[i].lfork = 0;
        para->philos[i].rfork = 0;
    }
}

int initial(t_para *para, char **av)
{
    int i;

    i = -1;
    para->n = ft_atoi(av[1]);
    para->t_dead = ft_atoi(av[2]);
    para->t_eat = ft_atoi(av[3]);
    para->t_slp = ft_atoi(av[4]);
    if (av[5])
        para->n_must = ft_atoi(av[5]);
    else
        para->n_must = 0;
    para->totalmeals = 0;
    para->philos = (t_philo*)malloc(para->n * sizeof(*(para->philos)));
    if (!para->philos)
        return (1);
    para->forks = malloc(para->n * sizeof(pthread_mutex_t));
    if (!para->forks)
        return (1);
    while(++i < para->n)
        pthread_mutex_init(&para->forks[i], NULL);
    pthread_mutex_init(&para->msg, NULL);
    pthread_mutex_init(&para->dead, NULL);
    init_philo(para);
    return (0);
}