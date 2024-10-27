#include "philosophers.h"

unsigned int get_time_in_ms()
{
    struct timeval  time;
    unsigned long int time_in_ms;

    gettimeofday(&time, NULL);
    time_in_ms = time.tv_sec * 1000;
    time_in_ms += time.tv_usec / 1000;
    return (time_in_ms);
}