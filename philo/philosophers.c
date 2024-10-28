#include "philosophers.h"

static int	philo_think(t_philo *philo)
{
	update_state(philo, THINK);
	if (philo->first_meal || philo->data.number_of_philosophers % 2)
	{
		philo->first_meal = false;
		if ((philo->id % 2 || philo->data.number_of_philosophers % 2)
			&& ft_sleep(philo, philo->data.time_to_eat / 2))
			return (1);
	}
	return (0);
}

static int	philo_eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	philo->last_meal = get_time_in_ms(philo->data.ref_time);
	update_state(philo, EAT);
	if (ft_sleep(philo, philo->data.time_to_eat))
	{
		release_forks(philo);
		return (1);
	}
	release_forks(philo);
	if (philo->data.must_eat != -1 && !--philo->data.must_eat)
	{
		pthread_mutex_lock(philo->satiated.mutex);
		philo->satiated.boolean = true;
		pthread_mutex_unlock(philo->satiated.mutex);
	}
	return (0);
}

static int	philo_sleep(t_philo *philo)
{
	if (check_for_end(philo))
		return (1);
	update_state(philo, SLEEP);
	if (ft_sleep(philo, philo->data.time_to_sleep))
		return (1);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	if (!arg)
		return (NULL);
	philo = arg;
	while (1)
	{
		if (philo_think(philo))
			break ;
		if (philo_eat(philo))
			break ;
		if (philo_sleep(philo))
			break ;
	}
	return (NULL);
}
