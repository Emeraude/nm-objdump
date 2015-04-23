/*
** parse_elf.c for  in /home/broggi_t/projet/nm-objdump
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Wed Apr 22 23:46:00 2015 broggi_t
** Last update Wed Apr 22 23:46:00 2015 broggi_t
*/

#include <unistd.h>
#include <elf.h>

#include <stdio.h>
static void	foreach_ehdr(Elf64_Ehdr const *const ehdr,
			     Elf64_Shdr const *const shdr)
{
  register int	i;

  i = -1;
  printf("--->%d<---\n", SHT_SYMTAB);
  printf("===>%d<===\n", SHT_DYNSYM);
  while (++i != ehdr->e_shnum)
    {
      printf("%d\n", shdr[i].sh_type);
    }
}

int			run_elf(Elf64_Ehdr const *const ehdr)
{
  Elf64_Shdr const	*shdr;

  shdr = (Elf64_Shdr *)((void *)ehdr + ehdr->e_shoff);
  foreach_ehdr(ehdr, shdr);
  return (1);
}
