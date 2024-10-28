#include "philosophers.h"

static void	clear_philo(t_philo *philo)
{
	if (philo->dead.mutex)
		clear_mutex(&philo->dead.mutex);
	if (philo->end.mutex)
		clear_mutex(&philo->end.mutex);
	if (philo->satiated.mutex)
		clear_mutex(&philo->satiated.mutex);
	if (philo->right_fork)
		clear_mutex(&philo->right_fork);
}

void	clear_philo_tab(t_philo **philo_tab, size_t philo_count)
{
	size_t	i;

	if (!philo_tab || !*philo_tab)
		return ;
	i = 0;
	while (i < philo_count)
	{
		clear_philo(&(*philo_tab)[i]);
		i++;
	}
	free(*philo_tab);
	*philo_tab = NULL;
}

void	clear_data(t_main_data *data)
{
	clear_mutex(&data->print_mutex);
	clear_philo_tab(&data->philosophers, data->number_of_philosophers);
}
