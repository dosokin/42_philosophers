#include "philosophers.h"

bool check_for_end(t_philo *philo)
{
    bool end;

    pthread_mutex_lock(philo->end.mutex);
    end = philo->end.boolean;
    pthread_mutex_unlock(philo->end.mutex);
    return (end);
}

void update_state(t_philo *philo, enum e_philo_state state) {
    philo->state = state;
    if (state == DEAD)
        ft_printf(*philo, DEAD);
    else if (state == EAT)
        ft_printf(*philo, EAT);
    else if (state == THINK)
        ft_printf(*philo, THINK);
    else if (state == SLEEP)
        ft_printf(*philo, SLEEP);
}

bool is_dead(t_philo *philo)
{
    unsigned long int now;

    now = get_time_in_ms(philo->data.ref_time);
    if (philo->last_meal + philo->data.time_to_die > now)
        return (false);
    pthread_mutex_lock(philo->dead.mutex);
    philo->dead.boolean = true;
    pthread_mutex_unlock(philo->dead.mutex);
    update_state(philo, DEAD);
    return (true);
}

int ft_sleep(t_philo *philo, unsigned long int time)
{
    unsigned long int sleep_start;

    sleep_start = get_time_in_ms(philo->data.ref_time);
    while (1)
    {
        if (get_time_in_ms(philo->data.ref_time) > sleep_start + time)
            break;
        if (check_for_end(philo) || is_dead(philo))
            return (1);
        usleep(3 * philo->data.number_of_philosophers);
    }
    return (0);
}