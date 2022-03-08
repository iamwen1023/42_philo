#include "philo.h"

void take_fork(t_philo *p)
{
    unsigned long tf;
    int firstfork;
    int secondfork;

    tf = get_time() - (p->para->t_start);
    if (p->index % 2)
    {
        ft_usleep(1);
        firstfork = p->index;
        secondfork = (p->index + 1) % p->para->n;
    }
    else
    {
        secondfork = p->index;
        firstfork = (p->index + 1) % p->para->n;
    }
    pthread_mutex_lock(&p->para->forks[firstfork]);
    p->lfork = 1;
    printf_msg(tf, p, 1);   
    pthread_mutex_lock(&p->para->forks[secondfork]);
    p->rfork = 1;
    printf_msg(tf, p, 2);
}

void remove_fork(t_philo *p)
{
    int firstfork;
    int secondfork;

    secondfork = p->index;
    firstfork = (p->index + 1) % p->para->n;
    if (p->lfork == 1)
    {
        pthread_mutex_unlock(&p->para->forks[firstfork]);
        p->lfork = 0;
    }
    if (p->rfork == 1)
    {
        pthread_mutex_unlock(&p->para->forks[secondfork]);
        p->rfork = 0;
    }

}

int eat(t_philo *p)
{
    unsigned long tf;

    tf = get_time() - (p->para->t_start);
    if (check_dead(p, tf) || check_end(p))
        return (1);
    p->lastmeal = tf;
    p->meals = p->meals + 1;
    printf_msg(tf, p, 3);
    ft_usleep(p->para->t_eat);
    remove_fork(p);
    return (0);
}

int ft_sleep(t_philo *p)
{
    unsigned long tf;

    tf = get_time() - (p->para->t_start);
    if (check_dead(p, tf) || check_end(p))
        return (1);
    printf_msg(tf, p, 4);
    // died during sleep
    if (tf - p->lastmeal > (unsigned long)p->para->t_dead)
    {
        ft_usleep((unsigned long)(p->lastmeal + p->para->t_dead));
        printf_msg(p->lastmeal + p->para->t_dead, p, 6);
        return (1);
    }
    ft_usleep(p->para->t_slp);
    return (0);
}

int thinking(t_philo *p)
{
    int time;
    unsigned long tf;

    time = p->para->t_dead - p->para->t_eat;
    time -= p->para->t_slp;
    tf = get_time() - (p->para->t_start);
    if (check_dead(p, tf) || check_end(p))
        return (1);
    printf_msg(tf, p, 5);
    if (p->para->t_dead <= p->para->t_eat * 2 || \
        (p->para->t_dead <= (p->para->t_eat * 2 + p->para->t_slp) && \
        p->para->n % 2 != 0))
    {
        ft_usleep((unsigned long)time);
        printf_msg((unsigned long)time, p, 6);

    }
    //printf("[%lu ms] #%d is thinking\n", tf, p->index);
    return (0);
}