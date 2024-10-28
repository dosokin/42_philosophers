#include "philosophers.h"

int	launch_philos_threads(t_main_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&(data->philosophers[i].thread), NULL,
					&philo_routine, &(data->philosophers[i])))
				return (error_manager(THR_ISSUE));
		}
	}
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (i % 2)
		{
			if (pthread_create(&(data->philosophers[i].thread), NULL,
					&philo_routine, &(data->philosophers[i])))
				return (error_manager(THR_ISSUE));
		}
	}
	pthread_create(&data->supervision_thread, NULL, &supervision, data);
	return (0);
}

int	join_philos_threads(t_main_data *data)
{
	size_t	i;

	i = 0;
	if (pthread_join(data->supervision_thread, NULL))
	{
		error_manager(THR_ISSUE);
		return (1);
	}
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
