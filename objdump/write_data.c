/*
** write_data.c for  in /home/broggi_t/projet/nm-objdump/objdump
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sat Apr 25 09:01:59 2015 broggi_t
** Last update Sat Apr 25 09:01:59 2015 broggi_t
*/

#include <stdio.h>
#include <string.h>
#include "objdump.h"

#define IS_PRINTABLE(x)	(x >= ' ' && x <= '~')

void		print_hexa(uint8_t const *const data, int const size)
{
  register int	i;

  i = -1;
  while (++i < 16)
    {
      if (i < size)
	printf("%02x", data[i]);
      else
	printf("  ");
      if (!((i + 1) % 4))
	printf(" ");
    }
  printf(" ");
}

void		print_ascii(uint8_t const *const data, int const size)
{
  register int	i;

  i = -1;
  while (++i < 16)
    {
      if (i < size)
	printf("%c", IS_PRINTABLE(data[i]) ? data[i] : '.');
      else
	printf(" ");
    }
  printf("\n");
}

void	print_data(t_elf *const elf, int const i, int const j)
{
  if (!elf->shdr[i].sh_addr)
    printf(" %04x ",
	   (int)(elf->shdr[i].sh_addr + j - elf->shdr[i].sh_offset));
  else
    printf(" %x ",
	   (int)(elf->shdr[i].sh_addr + j - elf->shdr[i].sh_offset));
  print_hexa((unsigned char *)elf->ehdr + j,
	     elf->shdr[i].sh_offset + elf->shdr[i].sh_size - j);
  print_ascii((unsigned char *)elf->ehdr + j,
	      elf->shdr[i].sh_offset + elf->shdr[i].sh_size - j);
}

int	write_data(t_elf *const elf)
{
  int	i;
  int	j;

  i = -1;
  while (++i < elf->ehdr->e_shnum)
    {
      if ((void *)&elf->shdr[i] > elf->end
	  || (void *)&elf->strtab[elf->shdr[i].sh_name] > elf->end)
	return (fprintf(stderr, "Error : invalid file\n") && 0);
      if ((!elf->shdr[i].sh_addr
	   && strcmp(&elf->strtab[elf->shdr[i].sh_name], ".comment"))
	  || !strcmp(&elf->strtab[elf->shdr[i].sh_name], ".bss"))
      	continue ;
      printf("Contents of section %s:\n", &elf->strtab[elf->shdr[i].sh_name]);
      j = elf->shdr[i].sh_offset;
      while ((unsigned)j < elf->shdr[i].sh_offset + elf->shdr[i].sh_size)
	{
	  print_data(elf, i, j);
	  j += 16;
	}
    }
  return (1);
}
