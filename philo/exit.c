#include "philosophers.h"

void clear_philo_tab(t_philo **philo_tab, size_t philo_count)
{
    size_t i;

    i = 0;
    while (i < philo_count)
    {
        clear_mutex(&((*philo_tab)[i].right_fork));
        i++;
    }
    free(*philo_tab);
    *philo_tab = NULL;
}


void clear_data(t_main_data *data)
{
    clear_mutex(&data->death.mutex);
    clear_mutex(&data->print_mutex);
    clear_philo_tab(&data->philosophers, data->number_of_philosophers);
}

