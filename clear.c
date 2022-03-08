#include "philo.h"

void free_para(t_para *para)
{
    int i;

    i = -1;
    if (para)
    {
        if (para->philos)
            free(para->philos);
        while(para->forks && ++i < para->n)
        {
            pthread_mutex_lock(&para->forks[i]);
            pthread_mutex_unlock(&para->forks[i]);
            pthread_mutex_destroy(&para->forks[i]);
        }
        if (para->forks)
            free(para->forks);
        pthread_mutex_lock(&para->msg);
        pthread_mutex_unlock(&para->msg);
        pthread_mutex_destroy(&para->msg);
        pthread_mutex_lock(&para->dead);
        pthread_mutex_unlock(&para->dead);
        pthread_mutex_destroy(&para->dead);
    }
}