#include "philo.h"

void *routine(void *arg)
{
    t_philo *p;

    p = (t_philo *)(arg);
    if (p->para->n == 1)
    {
        printf_msg(get_time() - p->para->t_start, p, 1);
        ft_usleep((unsigned long)p->para->t_dead);
        printf_msg(p->para->t_dead, p, 6);
        return (NULL);
    }
    while(1)
    { 
        take_fork(p);
        if (eat(p))
            return (NULL);
        if (check_end(p))
            break;
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
        philo = (void *)&para->philos[i];
        pthread_create(&para->philos[i].thread, NULL, routine, (void *)philo);
    }
    i= -1;
    while(++i < para->n)
    {
        pthread_join(para->philos[i].thread, NULL);
    }
    return (0);
}

int main(int ac, char** av)
{
    t_para para;

    if (ac < 5 || check_aug(ac, av))
    {
        printf("Arguments errors!\n");   
        return (1);
    }
    if (initial(&para, av))
    {
        printf("Something went wrong while executing!\n"); 
        free_para(&para);
        return (1);
    }
    run(&para);
    free_para(&para);
    printf("end\n");
    return (0);
}