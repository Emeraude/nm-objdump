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

static void	swap(t_symbol *const a, t_symbol *const b)
{
  t_symbol	c;

  memcpy(&c, a, sizeof(c));
  memcpy(a, b, sizeof(c));
  memcpy(b, &c, sizeof(c));
}

static void	sort_sym(t_symbol *const sym_list)
{
  register int	i;
  register int	j;

  i = -1;
  while (sym_list[++i].value
	 || sym_list[i].type
	 || sym_list[i].name)
    {
      j = i - 1;
      while (sym_list[++j].value
	     || sym_list[j].type
	     || sym_list[j].name)
	if (strcmp(sym_list[i].name, sym_list[j].name) > 0)
	  swap(&sym_list[i], &sym_list[j]);
      ++j;
    }
}

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
  sort_sym(sym_list);
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

#define ELF_SHDR (Elf64_Shdr *)((void *)elf->ehdr + elf->ehdr->e_shoff)

#define SYM_START (Elf64_Sym *)((void *)elf->ehdr + elf->shdr[i].sh_offset)
#define SYM_END (Elf64_Sym *)((void *)elf->sym.start + elf->shdr[i].sh_size)
#define SYM_STR (char *)elf->ehdr + elf->shdr[elf->shdr[i].sh_link].sh_offset

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
