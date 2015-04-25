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

int	main(int const ac, char const *const *const av)
{
  t_elf	elf;

  if ((ac < 2
       && !parse_file("a.out", &elf))
      || !parse_file(av[1], &elf)
      || !write_header(&elf)
      || !write_data(&elf))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
