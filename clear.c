#include "philo.h"

void free_para(t_para *para)
{
    int i;

    i = -1;
    if (para)
    {
        printf("inside\n");
        if (para->philos)
            free(para->philos);
        if (para->forks)
        {
            while(++i < para->n)
                pthread_mutex_destroy(&para->forks[i]);
        }
        pthread_mutex_destroy(&para->msg);
        pthread_mutex_destroy(&para->dead);
        if (para->forks)
            free(para->forks);
        //free(para);
    }
}