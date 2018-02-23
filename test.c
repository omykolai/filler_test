/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 15:06:52 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/23 14:40:06 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "../get_next_line/get_next_line.h"

float	g_average;

bool	set_res(char **res1, char **res2)
{
	char	*line;
	bool	print1;
	char	*str;

	print1 = false;
	while (get_next_line(0, &line))
	{
		if ((str = strstr(line, "egfault")))
			printf("\x1b[1;31m" "segfault\n" "\x1b[0m");
		else if ((str = strstr(line, "rror")))
			printf("\x1b[1;31m" "error\n" "\x1b[0m");
		else if (print1)
		{
			free(*res1);
			*res1 = line;
		}
		else
		{
			free(*res2);
			*res2 = line;
		}
		if (((print1 = !print1) || 1) && str)
			exit(1);
	}
	return (print1);
}

void	print_procent(float n, char *s)
{
	printf("%s: ", s);
	if (n < 25.f)
		printf("\x1b[31m");
	else if (n < 50.f)
		printf("\x1b[91m");
	else if (n < 75.f)
		printf("\x1b[32m");
	else
		printf("\x1b[1;92m");
	printf("%.2f%%\n", n);
	printf("\x1b[0m");
}

float	print_result(float r1, float r2, float average)
{
	float result;

	if (r1 == r2)
		result = 50.f;
	else
		result = (r1 * 100) / (r1 + r2);
	print_procent(result, "result");
	if (result > 0)
		average += result;
	return (average);
}

void	print_average(void)
{
	int fd;

	fd = open("a", O_TRUNC | O_WRONLY | O_CREAT, 0666);
	dprintf(fd, "%.2f", g_average);
	close(fd);
}

int		main(int argc, char **argv)
{
	char	*res1;
	char	*res2;
	int		r1;
	int		r2;
	bool	one_is_first;

	res1 = NULL;
	res2 = NULL;
	if (argc == 3)
	{
		if (argv[2][0] == '0')
		{
			one_is_first = set_res(&res1, &res2);
			r1 = atoi(strstr(one_is_first ? res1 : res2, "fin: ") + 5);
			r2 = atoi(strstr(one_is_first ? res2 : res1, "fin: ") + 5);
			g_average = print_result(r1, r2, atof(argv[1]));
			print_average();
		}
		else
		{
			printf("-------------\n");
			print_procent(atof(argv[1]), "average");
		}
	}
	return (0);
}
