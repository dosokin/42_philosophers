#include "philosophers.h"

void	release_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

static void	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	ft_printf(*philo, FORK);
}

int	take_forks(t_philo *philo)
{
	if (philo->data.number_of_philosophers == 1)
	{
		take_fork(philo, philo->right_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (ft_sleep(philo, philo->data.time_to_die * 2));
	}
	if (philo->id % 2)
	{
		take_fork(philo, philo->left_fork);
		take_fork(philo, philo->right_fork);
	}
	else
	{
		take_fork(philo, philo->right_fork);
		take_fork(philo, philo->left_fork);
	}
	if (is_dead(philo))
	{
		release_forks(philo);
		return (1);
	}
	return (0);
}