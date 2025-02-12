#include "philo.h"

static int	extra_loop(char *s, int *i, long long *val);
static int	validate_av(char *s);
static int	validate_arguments(char **av);

int	save_arguments_in_struct(t_data *data, char **av)
{
	if(!validate_arguments(av))
	{
		invalid_argument();
		return(0);
	}
	data->philos = ft_atoi(av[1]);
	data->ms_die = ft_atoi(av[2]);
	data->ms_eat = ft_atoi(av[3]);
	data->ms_sleep = ft_atoi(av[4]);
	data->must_eat = ft_atoi(av[5]);
	printf("%d	%d	%d	%d\n", data->philos, data->ms_die, data->ms_eat, data->ms_sleep);	
	return(1);
}

static int	validate_arguments(char **av)
{
	int i = 1;
	while(av[i])
	{
		if(!validate_av(av[i]))
			return(0);
		i++;
	}
	return(1);
}

static int	validate_av(char *s)
{
	int i;
	long long val;

	i = 0;
	val = 0;
	if(s[i] == '\0')
		return(0);
	while(s[i] == ' ')
		i++;
	if(!extra_loop(s, &i, &val))
		return(0);
	while(s[i])
	{
		if(s[i] != ' ')
			return(0);
		i++;
	}
	if(val == 0)
		return(0);
	return(1);
}

static int	extra_loop(char *s, int *i, long long *value)
{
	int j;
	
	j = 0;
	while(s[(*i)])
	{
		if(s[(*i)] == '+')
			(*i)++;
		if(s[(*i)] == ' ')
			break;
		(*value) = (*value) * 10 + (s[(*i)] - '0');
		if(s[(*i)] < '0' || s[(*i)] > '9' || (*value) > 2147483647 || j  > 10)
			return(0);
		(*i)++;
		j++;
	}
	return(1);
}
