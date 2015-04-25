/*
** fill_symbol.c for  in /home/broggi_t/projet/nm-objdump/nm
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sat Apr 25 04:59:21 2015 broggi_t
** Last update Sat Apr 25 04:59:21 2015 broggi_t
*/

#include <stdio.h>
#include <elf.h>
#include "nm.h"

#define SIZE(x)		(sizeof(x) / sizeof(*x))
#define LOWER(x)	(x >= 'A' && x <= 'Z' ? x + 0x20 : x)

char			get_type(t_elf *const elf, Elf64_Sym const *const sym)
{
  register int		i;
  static t_type const	types[] = {{'B', SHT_NOBITS, SHF_ALLOC | SHF_WRITE},
				   {'R', SHT_PROGBITS, SHF_ALLOC},
				   {'D', SHT_PROGBITS, SHF_ALLOC | SHF_WRITE},
				   {'U', SHT_NULL, 0},
				   {'T', SHT_PROGBITS,
				    SHF_ALLOC | SHF_EXECINSTR},
				   {'R', SHT_PROGBITS, 0}};

  i = -1;
  while ((unsigned)++i < SIZE(types))
    {
      if ((void *)&elf->shdr[sym->st_shndx] > elf->end)
	return (fprintf(stderr, "Error : invalid file\n") * 0 - 1);
      if (elf->shdr[sym->st_shndx].sh_type == types[i].type
	  && elf->shdr[sym->st_shndx].sh_flags == types[i].flags)
	return (types[i].ch);
    }
  return ('?');
}

int	fill_symbol(t_elf *const elf,
		    Elf64_Sym const *const sym,
		    t_symbol *const symbol)
{
  symbol->value = (unsigned int)sym->st_value;
  symbol->type = get_type(elf, sym);
  if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
    symbol->type = LOWER(symbol->type);
  if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    symbol->type = 'w';
  symbol->name = &elf->sym.strtab[sym->st_name];
  return (1);
}
