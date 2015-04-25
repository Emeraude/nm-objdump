/*
** fill_symbol.c for  in /home/broggi_t/projet/nm-objdump/nm
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sat Apr 25 04:59:21 2015 broggi_t
** Last update Sat Apr 25 04:59:21 2015 broggi_t
*/

#include <elf.h>
#include "nm.h"

void	fill_symbol(t_elf *const elf,
		    Elf64_Sym const *const sym,
		    t_symbol *const symbol)
{
  symbol->value = (unsigned int)sym->st_value;
  symbol->type = 42;
  symbol->name = &elf->sym.strtab[sym->st_name];
}
