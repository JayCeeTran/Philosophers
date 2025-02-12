#include "philo.h"

static int  check_white(char c)
{
    if (c == '\n' || c == '\r' || c == ' ' || c == '\f' || c == '\v'
        || c == '\t')
        return (1);
    return (0);
}

static int  check_sign(const char *str, int *i)
{
    int sign;

    sign = 1;
    while (str[(*i)])
    {
        if (check_white(str[(*i)]))
            (*i)++;
        else
            break ;
    }
    if (str[(*i)] == '-')
    {
        sign *= -1;
        (*i)++;
    }
    else if (str[(*i)] == '+')
        (*i)++;
    return (sign);
}

int ft_atoi(const char *str)
{
    int     i;
    int     sign;
    int     value;
    long    temp;

    value = 0;
    i = 0;
    sign = check_sign(str, &i);
    if (*str == '\0')
        return (0);
    while (str[i] <= '9' && str[i] >= '0')
    {
        temp = value;
        if (temp > INT_MAX)
            return (-1);
        else if (temp < INT_MIN)
            return (0);
        value = value * 10 + (str[i++] - 48);
    }
    return (value * sign);
}
