/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <elbenkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 19:49:24 by elbenkri          #+#    #+#             */
/*   Updated: 2020/10/21 19:49:29 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./nm.h"

int			run(char *file)
{
	struct stat	buf;
	int		fd;
	int		f;
	char		*ptr;

	f = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		f = -1;
	if (fstat(fd, &buf) < 0)
		f = -2;
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
		MAP_FAILED)
		f = -3;
	if (!f)
		nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		f = -4;
	return (f < 0) ? (f) : (0);
}

int			main(int ac, char **av)
{
	int		i;

	i = 1;
	if (ac < 2)
		return (run("a.out"));
	else
		while (av[i])
		{
			ft_printf("%s\n", av[i]);
			if (run(av[i]))
			{
				ft_printf("\nError file format: %s\n", av[i]);
				return (1);
			}
			i++;
		}
	return (0);
}
