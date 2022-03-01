#include "philo.h"


int take_fork(t_philo *p)
{
    unsigned long time;
    unsigned long tf;

    //printf("index:%d\n", p->index);
    time = get_time();
    tf = time - (p->para->t_start);
    //printf("time start:%lu\n", p->para->t_start);
    pthread_mutex_lock(&p->para->forks[p->lfork.index]);
    printf("%ld %d has a lfork\n", tf, p->index);
    // usleep(p->para->t_eat);
    // printf("%d is eating for %d", p->index, p->para->t_eat);
    
    pthread_mutex_lock(&p->para->forks[p->rfork.index]);
    printf("%ld %d has a rfork\n", tf, p->index);
    // usleep(p->para->t_eat);
    // printf("%d is eating for %d", p->index, p->para->t_eat);
    
    
    return (0);
}

int eat(t_philo *p)
{
    unsigned long tf;

    //check if time is more than "need to eat"
    //should be die?
    tf = get_time() - (p->para->t_start);
    usleep(p->para->t_eat);
    printf("%ld %d is eating\n", tf, p->index);
    pthread_mutex_unlock(&p->para->forks[p->lfork.index]);
    pthread_mutex_unlock(&p->para->forks[p->rfork.index]);
    return (0);
}