#include "philosophers.h"

static int initialize_philosopher(t_philo *philo, size_t philo_id, t_main_data data, pthread_mutex_t *left_fork)
{
    philo->id = philo_id;
    philo->last_meal = data.ref_time;
    philo->left_fork = left_fork;
    philo->right_fork = init_mutex();
    if (!philo->right_fork)
    {
        error_manager(MUTEX);
        return (1);
    }
    philo->state = THINK;
    philo->main_data = data;
    return (0);
}

static t_philo *initialize_philosophers_tab(size_t number_of_philosophers, t_main_data data)
{
    t_philo *philo_tab;
    pthread_mutex_t *left_fork;
    size_t i;

    i = 0;
    left_fork = NULL;
    philo_tab = malloc((number_of_philosophers) * sizeof(t_philo));
    while(i < number_of_philosophers)
    {
        if (initialize_philosopher(&(philo_tab[i]), i, data, left_fork))
        {
            clear_philo_tab(&philo_tab, i);
            return (NULL);
        }
        left_fork = philo_tab[i].right_fork;
        i++;
    }
    //let or delete?
    if (number_of_philosophers > 1)
        (*philo_tab).left_fork = left_fork;
    return (philo_tab);
}

int initialize_data(t_main_data *data)
{
    data->death.is_death = false;
    data->death.mutex = init_mutex();
    if (!data->death.mutex)
        return (1);
    data->print_mutex = init_mutex();
    if (!data->print_mutex)
        return (1);
    data->philosophers = initialize_philosophers_tab(data->number_of_philosophers, *data);
    if (!data->philosophers)
    {
        clear_mutex(&data->death.mutex);
        return (1);
    }
    return (0);
}