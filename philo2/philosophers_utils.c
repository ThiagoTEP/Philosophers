#include "philosophers.h"

long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(long time)
{
    long start = get_time();
    while ((get_time() - start) < time)
        usleep(50);
}

int ft_strlen(char *str)
{
    int len = 0;
    if (!str)
        return (0);
    while (str[len])
        len++;
    return (len);
}

int ft_atoi(const char *str)
{
    int i = 0;
    int res = 0;
    while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res);
}

void ft_putstr_error(char *str)
{
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
}
