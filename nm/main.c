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
  void	*file;

  if ((ac < 2
       && !(file = parse_file("a.out")))
      || !(file = parse_file(av[1]))
      || !run_elf((Elf64_Ehdr *) file))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
