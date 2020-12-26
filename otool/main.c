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

void			usage(void)
{
	ft_printf("Usage: ft_otool <file>\n");
}

void			print_error(int err)
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
	char		*ptr;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (1);
	if (fstat(fd, &buf) < 0)
		return (2);
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
		MAP_FAILED)
		return (3);
	otool(ptr);
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
		usage();
	else
	{
		while (av[i])
		{
			ft_printf("%s:\n", av[1]);
			ft_printf("(__TEXT,__text) section\n");
			if ((err = run(av[1])))
			{
				print_error(err);
				return (err);
			}
			i++;
		}
	}
	return (0);
}
