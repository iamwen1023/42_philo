#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_para {
    int n;
	int t_eat;
	int t_slp;
    int t_dead;
    int n_must;
    int totalmeals;
    unsigned long   t_start;
    pthread_mutex_t *forks;
    pthread_mutex_t msg;
    pthread_mutex_t dead;
    struct s_philo  *philos;
}	t_para;

typedef struct s_philo 
{
    int index;
    int meals;
    t_para  *para;
    pthread_t   thread;
    unsigned long   lastmeal;
    int lfork;
    int rfork;
}	t_philo;

int	ft_atoi(const char *str);
int if_num(char *c);
void init_philo(t_para *para);
int initial(t_para *para, char **av);
void take_fork(t_philo *p);
void remove_fork(t_philo *p);
int thinking(t_philo *p);
int eat(t_philo *p);
int ft_sleep(t_philo *p);
void    ft_usleep(unsigned long time);
unsigned long get_time();
void    printf_msg(unsigned long tv, t_philo *p, int i);
int check_dead(t_philo *p, unsigned long tf);
int check_end(t_philo *p);
int check_aug(int ac, char **av);
void free_para(t_para *para);