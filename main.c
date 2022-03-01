
#include "philo.h"

void *routine(void *arg)
{
    t_philo *p;

    p = (t_philo *)(arg);
    unsigned long time;

    while(1)
    {
        take_fork(p);
        eat(p);
        sleep(p);
        think(p);
        //break;
    }
    printf("hello\n");
    return 0;
}

unsigned long get_time()
{
	struct timeval	tv;
	unsigned long	time;

	gettimeofday(&tv, NULL);
	time = 1000 * (unsigned long)(tv.tv_sec);
	time += (unsigned long)(tv.tv_usec) / 1000;
	return (time);
}
int init_philo(t_para *para)
{
    int i;

    i = -1;
    while (++i < para->n)
    {
        para->philos[i].index = i;
        para->philos[i].para = para;
        para->philos[i].lastmeal = 0;
        para->philos[i].summeal = 0;
        para->philos[i].lfork.index = i;
        para->philos[i].rfork.index = (i + 1) % para->n;
        para->philos[i].lfork.state = 0;
        para->philos[i].rfork.state = 0;  
    }
    return (0);
}
int initial(t_para *para, int ac, char **av)
{
    int i;

    i = -1;
    para->n = ft_atoi(av[1]);
    para->t_eat = ft_atoi(av[2]);
    para->t_slp = ft_atoi(av[3]);
    para->t_dead = ft_atoi(av[4]);
    if (av[5])
        para->t_must = ft_atoi(av[5]);
    else
        para->t_must = 0;
    para->philos = (t_philo*)malloc(para->n * sizeof(*(para->philos)));
    if (!para->philos)
        return (1);
    if (init_philo(para))
        return (1);
    para->forks = malloc(para->n * sizeof(pthread_mutex_t));
    if (!para->forks)
        return (1);
    while(++i < para->n)
        pthread_mutex_init(&para->forks[i], NULL);
    return (0);
}

int    run(t_para *para)
{
    int             i;
    void		    *philo;

    i = -1;
    para->t_start = get_time();
    printf("time start:%lu\n", para->t_start);
    while(++i < para->n)
    {
        philo = (void *)&para->philos[i];
        pthread_create(&para->philos->thread, NULL, routine, (void *)philo);
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
    //t_philo *philo;
    t_para para;
    int i;

    i = -1;
    if (ac < 5)
    {
        printf("At least 4 arguments!\n");   
        return (1);
    }
    if (initial(&para, ac, av))
        return (1);
    if (run(&para))
        return (1);
    // create and join two loop for paralell
    // while(++i < para.n)
    // {
    //     philo[i].index = i;
    //     philo[i].para = &para;
    //     philo[i].time = 0;
    //     pthread_mutex_init(&philo[i].mutex, NULL);
    //     pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]);
    // }
    // i= 0;
    // while(++i < para.n)
    // {
    //     pthread_join(philo[i].thread, NULL);
    // }
    // i= 0;
    // while(++i < para.n)
    // {
    //     pthread_mutex_destroy(&philo[i].mutex);
    // }
    // if (th)
    //     free(th);
//number_of_philosophers time_to_die time_to_eat time_to_sleep
//[number_of_times_each_philosopher_must_eat]
    printf("end\n");
    return (0);
}