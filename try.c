#include <pthread.h>
//#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "libft/libft.h"

uint64_t
	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int main()
{
    struct timeval	tv;
    struct timeval	tv2;

    gettimeofday(&tv, NULL);
    gettimeofday(&tv2, NULL);   
    printf("time:%ld, %d\n", tv.tv_sec, tv.tv_usec);
    printf("dif:%llu\n", (tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));

    return 0;
}

