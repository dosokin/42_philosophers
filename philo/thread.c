#include "philosophers.h"

int	launch_philos_threads(t_main_data *data)
{
    size_t i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        if (pthread_create(&(data->philosophers[i].thread), NULL,
                           &routine, &(data->philosophers[i])))
            return (error_manager(THR_ISSUE));
        i++;
    }
    return (0);
}


int	join_philos_threads(t_main_data *data)
{
    size_t i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        if (pthread_join(data->philosophers[i].thread, NULL))
        {
            error_manager(THR_ISSUE);
            return (1);
        }
        i++;
    }

    return (0);
}