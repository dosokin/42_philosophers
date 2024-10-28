#include "philosophers.h"

static bool    is_everyone_satiated(t_main_data *data) {
    size_t      i;
    bool        satiated;

    satiated = true;
    i = 0;
    while (i < data->number_of_philosophers) {
        pthread_mutex_lock(data->philosophers[i].satiated.mutex);
        satiated = data->philosophers[i].satiated.boolean;
        pthread_mutex_unlock(data->philosophers[i].satiated.mutex);
        if (!satiated)
            return (false);
        i++;
    }
    return (true);
}

static bool    is_anyone_dead(t_main_data *data) {
    size_t      i;
    bool        dead;

    dead = true;
    i = 0;
    while (i < data->number_of_philosophers) {
        pthread_mutex_lock(data->philosophers[i].dead.mutex);
        dead = data->philosophers[i].dead.boolean;
        pthread_mutex_unlock(data->philosophers[i].dead.mutex);
        if (dead)
            return (true);
        i++;
    }
    return (false);
}

static void broadcast_end(t_main_data *data) {
    size_t i;

    i = 0;
    while (i < data->number_of_philosophers) {
        pthread_mutex_lock(data->philosophers[i].end.mutex);
        data->philosophers[i].end.boolean = true;
        pthread_mutex_unlock(data->philosophers[i].end.mutex);
        i++;
    }
}

void *supervision(void *arg) {
    t_main_data *data;

    data = arg;
    while (1) {
        if (data->must_eat != -1 && is_everyone_satiated(data))
            break;
        if (is_anyone_dead(data))
            break;
        usleep(3 * data->number_of_philosophers);
    }
    broadcast_end(data);
    return (NULL);
}