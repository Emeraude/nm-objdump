/*
** main.c for  in /home/broggi_t/projet/nm-objdump/nm
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Mon Apr 13 17:53:13 2015 broggi_t
** Last update Mon Apr 13 17:53:13 2015 broggi_t
*/

#include <stdio.h>
#include <elf.h>
#include "nm.h"

#if 0
static void	print_usage(char const *const bin_name)
{
  printf("Usage: %s [bin]\n", bin_name);
}
#endif

int	main(int const ac, char const *const *const av)
{
  t_elf elf;

  if ((ac < 2
       && !parse_file("a.out", &elf))
      || !parse_file(av[1], &elf)
      || !run_elf(&elf))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
