/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:00:18 by dosokin           #+#    #+#             */
/*   Updated: 2024/01/24 18:20:30 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_manager(t_err error)
{
	if (error == ARG_NBR)
		write(2, "Error\nWrong number of arguments\nValid argument"
                " format:\n./philo [number_of_philosophers] [time_to_die]"
                "[time_to_eat] [time_to_sleep] [number_of_times_each_phil"
                "osopher_must_eat](optionnal)\n",
                    186);
	else if (error == NO_UINT)
		write(2,
            "Error\nPlease only use unsigned_ints as arguments respecting the following format\n./philo"
            "[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]"
            "\n [number_of_times_each_philosopher_must_eat](optionnal)\n",
            213);
	else if (error == MEM_ISSUE)
		write(2, "Error\nMemory problem encountred\n", 32);
	else if (error == ZERO_PHILO)
		write(2,
			"Error\nDoes philosophers are able to die if they dont even exist?\n",
			65);
	else if (error == THR_ISSUE)
		write(2, "Error\nInternal problem creating threads\n", 40);
	else if (error == MAX_THR)
		write(2, "Error\nNumber of philosophers cant exceed 32753 due to material concerns\n", 72);
	else if (error == MUTEX)
		write(2, "Error\nProblem wiht a mutex\n", 27);
	return (-1);
}


int	conventional_checks(t_par *parameters)
{
	if (parameters->number_of_philosophers == 0)
	{
		free(parameters);
		return (error_manager(ZERO_PHILO));
	}
	if (parameters->number_of_philosophers > 32753)
	{
		free(parameters);
		return (error_manager(MAX_THR));
	}
	return (1);
}


float	get_time(t_par *parameters)
{
	float current_time;
	struct timeval now;

	gettimeofday(&now, NULL);
	current_time = (((now.tv_sec - parameters->time_reference->tv_sec) * 1000) + ((double)(now.tv_usec - parameters->time_reference->tv_usec) / (double)1000));
	return (current_time);
}

int	primary_checks(int argc, char **argv)
{
	int	i;
	int	y;

	if (argc != 5 && argc != 6)
		return (error_manager(ARG_NBR));
	i = 1;
	while (i < argc)
	{
		y = 0;
		while (argv[i][y])
		{
			if (y == 0 && (argv[i][y] == '-' || argv[i][y] == '+'))
				y++;
			else if (!(argv[i][y] <= '9' && argv[i][y] >= '0'))
				return (error_manager(ARG_NBR));
			else
				y++;
		}
		if (y == 0)
			return (error_manager(NO_UINT));
		i++;
	}
	return (1);
}

t_fork *init_fork(void)
{
	t_fork *fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->fork_status = malloc(sizeof(t_fork_state));
	if (!fork->fork_status)
		return (NULL);
	*(fork->fork_status) = AVAILABLE;
	fork->mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(fork->mutex, NULL);
	return (fork);
}

t_philo	**init_philosophers(t_par *parameters)
{
	int		i;
	t_philo	**philosophers;
	t_philo	*last_philosopher;

	i = 0;
	philosophers = malloc(parameters->number_of_philosophers * sizeof(t_philo *));
	last_philosopher = NULL;
	while (i < parameters->number_of_philosophers)
	{
		philosophers[i] = malloc(sizeof(t_philo));
        if (!philosophers[i])
            return (NULL);
        philosophers[i]->philosopher_id = i + 1;
		philosophers[i]->last = last_philosopher;
		philosophers[i]->right_fork = init_fork();
		if (philosophers[i]->last)
		{
			philosophers[i]->last->next = philosophers[i];
			philosophers[i]->left_fork = philosophers[i]->last->right_fork;
		}
		philosophers[i]->last_meal = malloc(sizeof(struct timeval));
		philosophers[i]->prm = parameters;
		last_philosopher = philosophers[i];
		i++;
	}
	philosophers[--i]->next = philosophers[0];
	philosophers[0]->last = philosophers[i];
	philosophers[0]->left_fork = philosophers[i]->right_fork;
	return (philosophers);
}

t_par	*arg_manager(int argc, char **argv)
{
	t_par	*parameters;
	int		flag_error;

	flag_error = 1;
	if (primary_checks(argc, argv) == -1)
		return (NULL);
	parameters = malloc(sizeof(t_par));
	if (!parameters)
	{
		error_manager(MEM_ISSUE);
		return (NULL);
	}
	parameters->number_of_philosophers = ft_atoui_safe(argv[1], &flag_error);
	parameters->time_to_die = ft_atoui_safe(argv[2], &flag_error);
	parameters->time_to_eat = ft_atoui_safe(argv[3], &flag_error);
	parameters->time_to_sleep = ft_atoui_safe(argv[4], &flag_error);
	if (argc == 6)
		parameters->must_eat = ft_atoui_safe(argv[5], &flag_error);
	else
		parameters->must_eat = INT_MAX;
	if (flag_error == -1)
	{
		free(parameters);
		error_manager(NO_UINT);
		return (NULL);
	}
	if (conventional_checks(parameters) == -1)
		return (NULL);
	parameters->philosophers = init_philosophers(parameters);
	parameters->time_reference = malloc(sizeof(struct timeval));
	return (parameters);
}

void	deinit(t_par *parameters, int philo_number)
{
	int	i;

	i = 0;
	while (i < philo_number)
	{
		free(parameters->philosophers[i]->right_fork);
		parameters->philosophers[i]->right_fork = NULL;
		free(parameters->philosophers[i]);
		parameters->philosophers[i] = NULL;
		i++;
	}
	free(parameters->philosophers);
	free(parameters);
}

void *lock_forks(void *void_fork_mutex)
{
	pthread_mutex_t *fork_mutex;

	fork_mutex = (pthread_mutex_t*)void_fork_mutex;
	pthread_mutex_lock(fork_mutex);
	return (NULL);
}

void *unlock_forks(void *void_fork_mutex)
{
	pthread_mutex_t *fork_mutex;

	fork_mutex = (pthread_mutex_t*)void_fork_mutex;
	pthread_mutex_unlock(fork_mutex);
	return (NULL);
}


int	lock_philosopher_forks(t_philo *philosophers)
{
	pthread_t left;
	pthread_t right;

	if (philosophers->philosopher_id % 2 == 0)
	{
		pthread_create(&left, NULL, &lock_forks, philosophers->left_fork->mutex);
		pthread_create(&right, NULL, &lock_forks, philosophers->right_fork->mutex);
	}
	else
	{
		pthread_create(&right, NULL, &lock_forks, philosophers->right_fork->mutex);
		pthread_create(&left, NULL, &lock_forks, philosophers->left_fork->mutex);
	}
	pthread_join(left, NULL);
	pthread_join(right, NULL);
	//printf("%d locked forks\n", philosophers->philosopher_id);
	return (1);
}

int unlock_philosopher_forks(t_philo *philosophers)
{
	pthread_t left;
	pthread_t right;

	pthread_create(&left, NULL, &unlock_forks, philosophers->left_fork->mutex);
	pthread_create(&right, NULL, &unlock_forks, philosophers->right_fork->mutex);
	pthread_join(left, NULL);
	pthread_join(right, NULL);
	return (1);
}

int	take_forks(t_philo *philosophers)
{
	int x;

	if (lock_philosopher_forks(philosophers) == -1)
		return (-1);
	if (*(philosophers->left_fork->fork_status) && *(philosophers->right_fork->fork_status))
	{
		*(philosophers->left_fork->fork_status) = UNAVAILABLE;
		printf("%f %d has taken a fork\n", get_time(philosophers->prm), philosophers->philosopher_id);
		*(philosophers->right_fork->fork_status) = UNAVAILABLE;
		printf("%f %d has taken a fork\n", get_time(philosophers->prm), philosophers->philosopher_id);
		x = 1;
	}
	else
		x = 0;
	if (unlock_philosopher_forks(philosophers) == -1)
		return (-1);
	return (x);
}

int	release_forks(t_philo *philosophers)
{
	if (lock_philosopher_forks(philosophers) == -1)
		return (-1);
	*(philosophers->left_fork->fork_status) = AVAILABLE;
	*(philosophers->right_fork->fork_status) = AVAILABLE;
	if (unlock_philosopher_forks(philosophers) == -1)
		return (-1);
	return (0);
}

float get_chrono(struct timeval *reference)
{
	float chrono;
	struct timeval now;

	gettimeofday(&now, NULL);
	chrono = (((now.tv_sec - reference->tv_sec) * 1000) + ((double)(now.tv_usec - reference->tv_usec) / (double)1000));
	return (chrono);
}

int	philosopher_thinking(t_philo *philosophers)
{
	int k;
	float	chrono;

	k = take_forks(philosophers);
	if (philosophers->prm->someone_died > 0)
		return (0);
	if (k == -1)
		return (-1);
	while (k != 1)
	{
		if (philosophers->prm->someone_died > 0)
			return (0);
		chrono = get_chrono(philosophers->last_meal);
		//printf("chrono :%f\n", chrono);
		if (chrono >= philosophers->prm->time_to_die)
		{
			philosophers->prm->someone_died++;
			printf("%f %d died\n", get_time(philosophers->prm), philosophers->philosopher_id);
			return (0);
		}
		if (philosophers->prm->someone_died > 0)
			return (0);
		k = take_forks(philosophers);
		usleep(500000);
	}
	return (1);
}

int	philosopher_eating(t_philo *philosophers)
{
	int	k;

	printf("%f %d is eating\n", get_time(philosophers->prm), philosophers->philosopher_id);
	gettimeofday(philosophers->last_meal, NULL);
	if (philosophers->prm->someone_died > 0)
		return (0);
	usleep(philosophers->prm->time_to_eat * 1000);
	if (philosophers->prm->someone_died > 0)
		return (0);
	k = release_forks(philosophers);
	if (k == -1)
		return (-1);
	return (1);
}

int	philosopher_sleeping(t_philo *philosophers)
{
	printf("%f %d is sleeping\n", get_time(philosophers->prm), philosophers->philosopher_id);
	if (philosophers->prm->someone_died > 0)
		return (0);
	usleep(philosophers->prm->time_to_sleep * 1000);
	return (1);
}

void    *routine(void *arg)
{
	t_philo *philosophers;
	int	eat_time;

	eat_time = 0;
	philosophers = (t_philo*)arg;
	gettimeofday(philosophers->last_meal, NULL);
	while (philosophers->prm->someone_died == 0)
	{
		if (philosophers->prm->someone_died > 0)
			return (0);
		if (philosopher_thinking(philosophers) == -1)
			return (NULL);
		if (philosophers->prm->someone_died > 0)
			return (philosophers);
		if (philosopher_eating(philosophers) == -1)
			return (NULL);
		eat_time++;
		if (eat_time >= philosophers->prm->must_eat)
			break ;
		if (philosophers->prm->someone_died > 0)
			return (0);
		philosopher_sleeping(philosophers);
	}
    return (philosophers);
}

int	main(int argc, char **argv)
{
	t_par	*parameters;
	int i;

	parameters = arg_manager(argc, argv);
	if (!parameters)
		return (-1);
    i = 0;
	gettimeofday(parameters->time_reference, NULL);
    while (i < parameters->number_of_philosophers)
    {
        if (pthread_create(&(parameters->philosophers[i]->thread), NULL, &routine, parameters->philosophers[i]) != 0)
			return (error_manager(THR_ISSUE));
		i++;
	}
    i = 0;
    while (i < parameters->number_of_philosophers)
    {
        if (pthread_join(parameters->philosophers[i]->thread, NULL) != 0)
			return (error_manager(THR_ISSUE));
        i++;
    }
	deinit(parameters, parameters->number_of_philosophers);
	return (1);
}
