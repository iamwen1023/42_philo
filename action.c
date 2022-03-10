#include "philo.h"

int take_fork(t_philo *p)
{
    int firstfork;
    int secondfork;

    if (check_dead(p) || check_end(p))
        return (1);
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
    //if check dead in prinf nsg
    pthread_mutex_lock(&p->para->forks[firstfork]);  
    p->lfork = 1;
    printf_msg(p, 1);   
    pthread_mutex_lock(&p->para->forks[secondfork]);
    p->rfork = 1;
    printf_msg(p, 1);
    return (0);
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
    if (check_dead(p) || check_end(p))
        return (1);
    p->lastmeal = get_time();
    printf_msg(p, 3);
    if (p->para->t_dead <= p->para->t_eat)
    {
        ft_usleep(p->para->t_dead);
        printf_msg(p, 6);
        pthread_mutex_lock(&p->para->dead);
        p->para->if_dead = 1;
        pthread_mutex_unlock(&p->para->dead);
        // pthread_mutex_lock(&p->para->dead);
        // if (!p->para->if_dead)
        //     printf_msg(p, 6);
        // p->para->if_dead = 1;
        // pthread_mutex_unlock(&p->para->dead);
        remove_fork(p);
        return (1);
    }
    pthread_mutex_lock(&p->para->dead);
    p->meals = p->meals + 1;
    pthread_mutex_unlock(&p->para->dead);
    ft_usleep(p->para->t_eat);
    remove_fork(p);
    if (check_dead(p) || check_end(p))
        return (1);
    return (0);
}

int ft_sleep(t_philo *p)
{
    if (check_dead(p) || check_end(p))
        return (1);
    if (p->para->t_dead <= p->para->t_slp || \
        p->para->t_dead <= p->para->t_eat + p->para->t_slp)
    {
        printf_msg(p, 4);
        ft_usleep(p->para->t_dead - p->para->t_eat);
        printf_msg(p, 6);
        pthread_mutex_lock(&p->para->dead);
        p->para->if_dead = 1;
        pthread_mutex_unlock(&p->para->dead);
        // pthread_mutex_lock(&p->para->dead);
        // if (!p->para->if_dead)
        //     printf_msg(p, 6);
        // p->para->if_dead = 1;
        // pthread_mutex_unlock(&p->para->dead);
        return (1);
    }
    printf_msg(p, 4);
    ft_usleep(p->para->t_slp);
    if (check_dead(p))
        return (1);
    return (0);
}

int thinking(t_philo *p)
{
    int time;

    if (check_dead(p) || check_end(p))
        return (1);
    printf_msg(p, 5);
    if ((get_time() + (unsigned long)p->para->t_eat) < (p->lastmeal + (unsigned long)p->para->t_dead))
    {
        ft_usleep(p->para->t_eat);
    }
    time = p->para->t_dead - p->para->t_eat;
    time -= p->para->t_slp;
    if (p->para->t_dead <= p->para->t_eat * 2 || \
        (p->para->t_dead <= (p->para->t_eat * 2 + p->para->t_slp) && \
        p->para->n % 2 != 0))
    {
        ft_usleep((unsigned long)time);
        printf_msg(p, 6);
        pthread_mutex_lock(&p->para->dead);
        p->para->if_dead = 1;
        pthread_mutex_unlock(&p->para->dead);
        // pthread_mutex_lock(&p->para->dead);
        // if (!p->para->if_dead)
        //     printf_msg(p, 6);
        // p->para->if_dead = 1;
        // pthread_mutex_unlock(&p->para->dead);
    }
    return (0);
}