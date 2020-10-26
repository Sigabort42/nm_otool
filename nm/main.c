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

int	run(char *file)
{
  int		fd;
  char		*ptr;
  struct stat	buf;

  if ((fd = open(file, O_RDONLY)) < 0)
    {
      ft_putstr("Error open file");
      return (fd);
    }
  if (fstat(fd, &buf) < 0)
    {
      ft_putstr("Error fstat");
      return (fd);
    }
  if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
    {
      ft_putstr("Error mmap");
      return (fd);
    }
  nm(ptr);
  if (munmap(ptr, buf.st_size) < 0)
    {
      ft_putstr("Error munmmap");
      return (fd);
    }
  return (0);
}


int	main(int ac, char **av)
{
  if (ac < 2)
    return (run("a.out"));
  else
    return (run(av[1]));
  return (0);
}
