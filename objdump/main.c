/*
** main.c for  in /home/broggi_t/projet/nm-objdump/objdump
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Mon Apr 13 17:53:30 2015 broggi_t
** Last update Mon Apr 13 17:53:30 2015 broggi_t
*/

#include "objdump.h"

static int	args(int const ac,
		     char const *const *const av,
		     t_elf *const elf)
{
  int		i;

  i = 0;
  while (++i < ac)
    if (!parse_file(av[i], elf)
	|| !write_header(elf)
	|| !write_data(elf))
      return (0);
  return (1);
}

int	main(int const ac, char const *const *const av)
{
  t_elf	elf;

  if ((ac < 2
       && (!parse_file("a.out", &elf)
	   || !write_header(&elf)
	   || !write_data(&elf)))
      || !args(ac, av, &elf))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
