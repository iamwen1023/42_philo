#include <pthread.h>
//#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "libft/libft.h"

typedef struct s_fork {
    int index;
    int state;
}   t_fork;

typedef struct s_para {
    int n;
	int	t_eat;
	int t_slp;
    int t_dead;
    int t_must;
    unsigned long t_start;
    pthread_mutex_t *forks;
    struct s_philo *philos;
}	t_para;

typedef struct s_philo 
{
    int index;
    int summeal;
    t_para *para;
    pthread_t thread;
    unsigned long lastmeal;
    int count_eat;
    t_fork lfork;
    t_fork rfork;
    //char leftorright;
}	t_philo;

int take_fork(t_philo *p);
unsigned long get_time();
