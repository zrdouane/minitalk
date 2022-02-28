/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrdouane <zrdouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:10:21 by zrdouane          #+#    #+#             */
/*   Updated: 2022/02/27 01:59:29 by zrdouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_char(pid_t pid, char c)
{
	int	bit;

	bit = 7;
	while (bit != -1)
	{
		if (c & (1 << bit))
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		bit--;
		usleep(500);
	}
}

static void	send_str(pid_t pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
}

static int	ft_atoi(const char *str)
{
	char				neg;
	unsigned long long	num;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	neg = (*str == '-');
	if (*str == '+' || *str == '-')
		str++;
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if (num > LONG_MAX - 1 && neg == 1)
		return (0);
	if (num > LONG_MAX && neg == 0)
		return (-1);
	if (neg)
		return (-num);
	else
		return (num);
}

int	main(int argc, char*argv[])
{
	pid_t	pid;
	char	*str;

	if (argc < 3)
	{
		ft_putstr_color_fd(ANSI_COLOR_RED, "client: invalid arguments.\n", 2);
		ft_putstr_color_fd(ANSI_COLOR_YELLOW, \
		"correct format: [./client <PID> <STR>].\n", 2);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	send_str(pid, str);
	return (0);
}
