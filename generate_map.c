/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 15:28:31 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/22 21:39:04 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

int **g_map;

int		get_cluster_num(int mod)
{
	int		r1;
	int		r2;
	time_t	t;

	srand((unsigned)time(&t));
	rand();
	r1 = rand() % mod + 1;
	r2 = rand() % mod + 1;
	return (r1 % r2 + 1);
}

void	init_map(char *n_str, char *m_str, int *n, int *m)
{
	int		i;
	int		j;

	*n = atoi(n_str);
	*m = atoi(m_str);
	g_map = (int**)malloc(sizeof(int*) * *n);
	i = -1;
	while (++i < *n)
		g_map[i] = (int*)malloc(sizeof(int) * *m);
	i = -1;
	while (++i < *n)
	{
		j = -1;
		while (++j < *m)
			g_map[i][j] = '.';
	}
}

void	set_clusters(int cluster_num, int n, int m)
{
	int i;
	int j;

	while (cluster_num--)
	{
		i = (rand() % (n / 2) + n / 4);
		j = (rand() % (m / 2) + m / 4);
		g_map[i][j] = 'O';
		g_map[n - i - 1][m - j - 1] = 'X';
	}
}

void	write_map(int n, int m)
{
	int		i;
	int		j;
	int		fd;

	fd = open("map", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	i = -1;
	while (++i < n)
	{
		j = -1;
		while (++j < m)
			dprintf(fd, "%c", g_map[i][j]);
		dprintf(fd, "\n");
	}
	close(fd);
}

int		main(int argc, char **argv)
{
	int n;
	int m;
	int	cluster_num;
	int **g_map;

	if (argc == 3)
	{
		init_map(argv[1], argv[2], &n, &m);
		cluster_num = get_cluster_num((n + m) / 10);
		set_clusters(cluster_num, n, m);
		write_map(n, m);
	}
	return (0);
}
