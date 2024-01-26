#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int i;
	struct timeval reference;
	struct timeval now;
    long time;

    gettimeofday(&reference, NULL);
    i = 0;
    while (i < 100)
    {
        gettimeofday(&now, NULL);
        time = ((now.tv_sec - reference.tv_sec) * 1000) + ((double)(now.tv_usec - reference.tv_usec) / (double)1000);
        // printf("time: %f\n", time);
        // printf("now time sec: %f", now.tv_sec);
        // printf("now time: %f\n", now.tv_usec);
        // printf("reference s time: %f   ", reference.tv_sec);
        // printf("reference ms time: %f\n", reference.tv_usec);
        printf("current time: %f    ", ((now.tv_sec - reference.tv_sec) * 1000));
        printf("current time: %f\n", now.tv_usec - reference.tv_usec);
        printf("REAT = %f\n\n", (((now.tv_sec - reference.tv_sec) * 1000) + ((double)(now.tv_usec - reference.tv_usec) / (double)1000)));
        sleep(1);
        i++;
    }
    return (0);
}