/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elbenkri <elbenkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:04:01 by elbenkri          #+#    #+#             */
/*   Updated: 2020/10/27 13:04:02 by elbenkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./otool.h"

void			usage()
{
	ft_printf("Usage: ft_otool <file>\n");
}

void			print_error(int err)
{
	if (err == 1)
		ft_printf("Can't open file\n");
	else if (err == 2)
		ft_printf("Error for open file\n");
	else if (err == 3)
		ft_printf("Error memory\n");
	else if (err == 4)
		ft_printf("Error memory free\n");
}

int			run(char *file)
{
	struct stat	buf;
	int		fd;
	int		f;
	char		*ptr;

	f = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		f = 1;
	if (fstat(fd, &buf) < 0)
		f = 2;
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
		MAP_FAILED)
		f = 3;
	if (!f)
		otool(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		f = 4;
	return (f > 0) ? (f) : (0);
}

int			main(int ac, char **av)
{
	int		i;
	int		err;

	i = 1;
	if (ac < 2)
		usage();
	else
	{
		while (av[i])
		{
			ft_printf("%s\n", av[1]);
			ft_printf("Contens of (__TEXT,__text) section\n");
			if ((err = run(av[1])))
			{
				print_error(err);
				return (err);
			}
		}
		i++;
	}
	return (0);
}
