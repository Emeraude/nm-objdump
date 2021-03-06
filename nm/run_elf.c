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
#include <malloc.h>
#include <string.h>
#include <elf.h>
#include "nm.h"

static t_symbol		*get_sym(t_elf *const elf)
{
  t_symbol		*sym_list;
  Elf64_Sym const	*tmp;
  register int		i;

  if (!(sym_list = malloc(sizeof(t_symbol) * (elf->sym.end - elf->sym.start))))
    {
      perror("malloc");
      return (NULL);
    }
  memset(sym_list, 0, sizeof(t_symbol) *(elf->sym.end - elf->sym.start));
  tmp = elf->sym.start;
  i = 0;
  while (tmp < elf->sym.end)
    {
      if (tmp->st_info != STT_FILE && tmp->st_info != STT_SECTION
	  && tmp->st_info != STT_NOTYPE)
	{
	  if ((void *)&elf->sym.strtab[tmp->st_name] > elf->end)
	    return (fprintf(stderr, "Error : invalid file\n") * 0 + NULL);
	  if (fill_symbol(elf, tmp, &sym_list[i++]) == -1)
	    return (NULL);
	}
      ++tmp;
    }
  return (sym_list);
}

static int	print_sym(t_elf *const elf)
{
  t_symbol	*sym_list;
  register int	i;

  if (!(sym_list = get_sym(elf)))
    return (0);
  sort_sym(sym_list, elf->sort);
  i = -1;
  while (sym_list[++i].value
	 || sym_list[i].type
	 || sym_list[i].name)
    {
      if (sym_list[i].value)
	printf("%016x %c %s\n", sym_list[i].value,
	       sym_list[i].type, sym_list[i].name);
      else
	printf("%18c %s\n", sym_list[i].type, sym_list[i].name);
    }
  free(sym_list);
  return (1);
}

int		run_elf(t_elf *const elf)
{
  register int	i;

  if ((void *)(elf->shdr = ELF_SHDR) > elf->end)
    return (fprintf(stderr, "Error : invalid file\n") && 0);
  i = -1;
  while (++i != elf->ehdr->e_shnum)
    {
      if ((void *)&(elf->shdr[i]) > elf->end)
	return (fprintf(stderr, "Error : invalid file\n") && 0);
      if (elf->shdr[i].sh_type == SHT_SYMTAB)
	{
	  if ((void *)(elf->sym.start = SYM_START) > elf->end
	      || (void *)(elf->sym.end = SYM_END) > elf->end
	      || (void *)(elf->sym.strtab = SYM_STR) > elf->end)
	    return (fprintf(stderr, "Error : invalid file\n") && 0);
	}
    }
  if (elf->sym.end < elf->sym.start)
    return (fprintf(stderr, "no symbols\n") || 1);
  return (print_sym(elf));
}
