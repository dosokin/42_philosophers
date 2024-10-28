#include "philosophers.h"

pthread_mutex_t	*init_mutex(void)
{
	pthread_mutex_t	*mutex;

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

int	clear_mutex(pthread_mutex_t **mutex)
{
	if (!mutex || !*mutex)
		return (1);
	if (pthread_mutex_destroy(*mutex))
	{
		error_manager(MUTEX);
		return (1);
	}
	free(*mutex);
	*mutex = NULL;
	return (0);
}
