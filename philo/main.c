/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:00:18 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/29 11:25:55 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
//
//static int	freeze(t_philo *philosophers)
//{
//	int	impair;
//
//	impair = 0;
//	if (philosophers->main->number_of_philosophers % 2 == 0)
//	{
//		if (philosophers->id % 2 == 0)
//			usleep(50);
//	}
//	else
//	{
//		impair = 1;
//		if (philosophers->id % 3 == 0)
//			impair = 1;
//		else if (philosophers->id % 3 == 1)
//			usleep(philosophers->main->time_to_eat * 980
//				- philosophers->id);
//		else if (philosophers->id % 3 == 2)
//			usleep(philosophers->main->time_to_eat
//				+ philosophers->main->time_to_sleep * 980
//				- philosophers->id);
//	}
//	return (impair);
//}
//
//static int	daily_routine(t_philo *philosophers, int must_eat, int eat_time)
//{
//	philosopher_thinking(philosophers);
//	if (is_dead(philosophers) == 1)
//		return (1);
//	philosopher_eating(philosophers);
//	if (is_dead(philosophers) == 1)
//		return (1);
//	if (must_eat)
//	{
//		if (eat_time >= must_eat)
//			return (1);
//	}
//	philosopher_sleeping(philosophers);
//	if (is_dead(philosophers) == 1)
//		return (1);
//	return (0);
//}
//
//void	*routine(void *arg)
//{
//	t_philo	*philosophers;
//	int		impair;
//	int		must_eat;
//	int		eat_time;
//
//	eat_time = 0;
//	philosophers = (t_philo *)arg;
//	must_eat = philosophers->main->must_eat;
//	impair = freeze(philosophers);
//	while (1)
//	{
//		if (impair)
//			usleep(100);
//		eat_time++;
//		if (daily_routine(philosophers, must_eat, eat_time) == 1)
//			break ;
//	}
//	return (philosophers);
//}

int get_args(int argc, char **argv, t_main_data *data)
{
    bool error;

    if (argc != 5 && argc != 6)
        return (error_manager(ARG_NBR));
    error = false;
    argv++;
    data->number_of_philosophers = ft_safe_atoi(*argv, &error);
    argv++;
    data->time_to_die = ft_safe_atoi(*argv, &error);
    argv++;
    data->time_to_eat = ft_safe_atoi(*argv, &error);
    argv++;
    data->time_to_sleep = ft_safe_atoi(*argv, &error);
    argv++;
    if (argc == 6)
        data->must_eat = ft_safe_atoi(*argv, &error);
    else
        data->must_eat = -1;
    if (error)
        return (1);
    return (0);
}

int check_arg_validity(t_main_data data)
{
    if (!data.number_of_philosophers)
    {
        error_manager(ZERO_PHILO);
        return (1);
    }
    return (0);
}

void    ft_printf(t_philo philo, enum e_philo_action action)
{
    static char *actions[5] = {
            " has taken a fork",
            " is eating",
            " is sleeping",
            " is thinking",
            " died",
    };
    unsigned long now;

    now = get_time_in_ms();
    pthread_mutex_lock(philo.main_data.print_mutex);
    printf("%zu %zu", now, philo.id);
    printf("%s\n", actions[action]);
    pthread_mutex_unlock(philo.main_data.print_mutex);
}

void	*test_routine(void *arg) {
    t_philo *philo;

    if (!arg)
        return (NULL);
    philo = arg;
    ft_printf(*philo, philo->id % 5);
    return (NULL);
}

bool check_for_death(t_philo *philo)
{
    bool is_death;

    pthread_mutex_lock(philo->main_data.death.mutex);
    is_death = philo->main_data.death.is_death;
    pthread_mutex_unlock(philo->main_data.death.mutex);
    return (is_death);
}

void *routine(void *arg)
{
    t_philo *philo;

    if (!arg)
        return (NULL);
    philo = arg;
    ft_printf(*philo, TAKE_FORK);
    while (philo->main_data.must_eat < 0 || philo->main_data.must_eat--)
    {
        printf("%d\n", philo->main_data.must_eat);
        sleep(5);
    }
    return (NULL);
}

int	main(int argc, char **argv)
{
	t_main_data     data;

    if (get_args(argc, argv, &data) == ERROR)
        return (EXIT_FAILURE);
    if (check_arg_validity(data) == ERROR)
        return (EXIT_FAILURE);
    if (initialize_data(&data) == ERROR)
        return (EXIT_FAILURE);
    if (launch_philos_threads(&data) == ERROR)
		return (EXIT_FAILURE);
	if (join_philos_threads(&data) == ERROR)
		return (EXIT_FAILURE);
    clear_data(&data);
	return (EXIT_SUCCESS);
}
