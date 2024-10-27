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
    data->must_eat = -1;
    if (error)
        return (1);
    return (0);
}

struct timeval get_timeval()
{
    struct timeval  time;

//    time = malloc(sizeof(struct timeval));
    gettimeofday(&time, NULL);
//    timer.mutex = malloc(sizeof(pthread_mutex_t));
//    pthread_mutex_init(timer.mutex, NULL);
    return (time);
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

//t_lst_philo *initialize_philo(size_t index)
//{
//    t_lst_philo *philo;
//
//    philo = malloc(sizeof(t_lst_philo));
//    philo =
//}
//
//t_lst_philo *initialize_philosophers_lst(size_t number_of_philosophers)
//{
//    size_t i;
//    t_lst_philo *philo_lst;
//    t_lst_philo *new_philo;
//
//    i = 0;
//    while (i < number_of_philosophers)
//    {
//         new_philo = initialize_philo(i);
//         if (!new_philo)
//         {
//             ft_lst_philo_clear(philo_lst);
//             return (NULL);
//         }
//         ft_lst_philo_addback(&philo_lst, new_philo);
//    }
//    return (philo_lst);
//}
//
//t_lst_philo initialize_philo(size_t index, struct timeval reftime, pthread_mutex_t left_fork, st)
//{
//
//}

pthread_mutex_t *init_mutex()
{
    pthread_mutex_t *mutex;

    mutex = malloc(sizeof(pthread_mutex_t));
    if (!mutex)
    {
        error_manager(MEM_ERR);
        return (NULL);
    }
    if (pthread_mutex_init(mutex, NULL))
    {
        error_manager(MUTEX);
        free(mutex);
        return (NULL);
    }
    return (mutex);
}

int clear_mutex(pthread_mutex_t **mutex)
{
    if (pthread_mutex_destroy(*mutex))
    {
        error_manager(MUTEX);
        return (1);
    }
    free(*mutex);
    *mutex = NULL;
    return (0);
}

void clear_philo_tab(t_lst_philo *philo_tab, size_t philo_count)
{
//    t_lst_philo *current;
//    t_lst_philo *next;
//
//    if (!philo_tab)
//        return;
//    current = philo_tab;
//    while (current)
//    {
//        next = current->next;
//        clear_mutex(&current->right_fork);
//        free(current);
//        current = next;
//    }

}
//
//t_lst_philo *initialize_philosopher(size_t philo_id, t_main_data data, pthread_mutex_t *left_fork)
//{
//    t_lst_philo *philo;
//
//    philo = malloc(sizeof(t_lst_philo));
//    philo->id = philo_id;
//    philo->print_mutex = data.print_mutex;
//    philo->last_meal = data.ref_time;
//    philo->ref_time = data.ref_time;
//    philo->left_fork = left_fork;
//    philo->right_fork = init_mutex();
//    if (!philo->right_fork)
//    {
//        free(philo);
//        error_manager(MUTEX);
//        return (NULL);
//    }
//    philo->next = NULL;
//    philo->state = THINK;
//    return (philo);
//}

int initialize_philosopher(t_lst_philo *philo, size_t philo_id, t_main_data data, pthread_mutex_t *left_fork)
{
    philo->id = philo_id;
    philo->print_mutex = data.print_mutex;
    philo->last_meal = data.ref_time;
    philo->ref_time = data.ref_time;
    philo->left_fork = left_fork;
    philo->right_fork = init_mutex();
    if (!philo->right_fork)
    {
        error_manager(MUTEX);
        return (1);
    }
    philo->next = NULL;
    philo->state = THINK;
    return (0);
}

t_lst_philo *initialize_philosophers_tab(size_t number_of_philosophers, t_main_data data)
{
    t_lst_philo *philo_tab;
    pthread_mutex_t *left_fork;
    size_t i;

    i = 0;
    left_fork = NULL;
    philo_tab = malloc((number_of_philosophers + 1) * sizeof(t_lst_philo));
    while(i < number_of_philosophers)
    {
        if (initialize_philosopher(&(philo_tab[i]), i, data, left_fork))
        {
            clear_philo_tab(philo_tab, i);
            return (NULL);
        }
        left_fork = philo_tab[i].right_fork;
        i++;
    }
    //let or delete?
    if (number_of_philosophers > 1)
        philo_tab->left_fork = left_fork;
    return (philo_tab);
}

int initialize_data(t_main_data *data)
{
    data->ref_time = get_timeval();
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

void    ft_printf(pthread_mutex_t *print_mutex, size_t id)
{
    pthread_mutex_lock(print_mutex);
    printf("hey im philo #%zu\n", id);
    pthread_mutex_unlock(print_mutex);
}

void	*test_routine(void *arg)
{
    t_lst_philo *philo;

    if (!arg)
        return (NULL);
    philo = arg;
    ft_printf(philo->print_mutex, philo->id);
    return (NULL);
}


int	launch_philos_threads(t_main_data *data)
{
    t_lst_philo *current;

    current = data->philosophers;
    while (current)
    {
        if (pthread_create(&(current->thread), NULL,
                           &test_routine, current))
            return (error_manager(THR_ISSUE));
        current = current->next;
    }
    return (0);
}

void clear_data(t_main_data *data)
{
    clear_mutex(&(data->death.mutex));
    clear_mutex(&(data->print_mutex));
    clear_philo_tab(data->philosophers);
}

int	join_philos_threads(t_main_data *data)
{
    t_lst_philo *current;

    current = data->philosophers;
    while (current)
    {
        if (pthread_join(current->thread, NULL))
            return (error_manager(THR_ISSUE));
        current = current->next;
    }
    return (0);
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
