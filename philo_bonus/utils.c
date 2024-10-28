#include "philosophers.h"

unsigned int get_time_in_ms(unsigned long int ref_time)
{
    struct timeval  time;
    unsigned long int time_in_ms;

    gettimeofday(&time, NULL);
    time_in_ms = time.tv_sec * 1000;
    time_in_ms += time.tv_usec / 1000;
    return (time_in_ms - ref_time);
}

void    ft_printf(t_philo philo, enum e_philo_state state)
{
    static char *actions[5] = {
        " has taken a fork",
        " is eating",
        " is sleeping",
        " is thinking",
        " died",
};
    unsigned long int now;

    now = get_time_in_ms(philo.data.ref_time);
    pthread_mutex_lock(philo.data.print_mutex);
    printf("%zu %zu", now, philo.id);
    printf("%s\n", actions[state]);
    pthread_mutex_unlock(philo.data.print_mutex);
}

