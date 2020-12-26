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

void                    print_error(int err)
{
        if (err == 1)
                ft_printf("%s\n", "Can't open file");
	else if (err == 2)
                ft_printf("%s\n", "Error for open file");
	else if (err == 3)
                ft_printf("%s\n", "Error memory");
	else if (err == 4)
	        ft_printf("%s\n", "Error memory free");
}

int			run(char *file)
{
	struct stat	buf;
	int		fd;
	int		f;
	char		*ptr;

	f = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (1);
	if (fstat(fd, &buf) < 0)
		return (2);
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
		MAP_FAILED)
		return (3);
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (4);
	return (0);
}

int			main(int ac, char **av)
{
	int		i;
	int		err;

	i = 1;
	if (ac < 2)
		return (run("a.out"));
	else
		while (av[i])
		{
			ft_printf("%s\n", av[i]);
			if ((err = run(av[i])))
			{
				print_error(err);
				return (err);
			}
			i++;
		}
	return (0);
}
