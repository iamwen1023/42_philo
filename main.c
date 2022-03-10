#include "philo.h"

void first_thinking(t_philo *p)
{
    pthread_mutex_lock(&p->para->dead);
    if (!p->para->if_dead)
    {
        pthread_mutex_unlock(&p->para->dead);
        printf_msg(p, 5);
        return ;
    }
    pthread_mutex_unlock(&p->para->dead);
}

void *routine(void *arg)
{
    t_philo         *p;

    p = (t_philo *)(arg);
    if (p->para->n == 1)
    {
        printf_msg(p, 1);
        ft_usleep((unsigned long)p->para->t_dead);
        printf_msg(p, 6);
        return (NULL);
    }
    //first_thinking(p);
    while(!check_dead(p) && !check_end(p))
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
    return 0;
}

int    run(t_para *para)
{
    int     i;
    void    *philo;

    i = -1;
    para->t_start = get_time();
    while(++i < para->n)
    {
        para->philos[i].lastmeal = para->t_start;
        philo = (void *)&para->philos[i];
        if (pthread_create(&para->philos[i].thread, NULL, routine, (void *)philo))
            return (1);
    }
    i= -1;
    while(++i < para->n)
    {
        if (pthread_join(para->philos[i].thread, NULL))
            return (1);
    }
    return (0);
}

int main(int ac, char** av)
{
    t_para para;

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
