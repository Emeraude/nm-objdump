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
#include <stdio.h>
#include <elf.h>
#include "nm.h"

static int		print_sym(t_elf *const elf)
{
  Elf64_Sym const	*tmp;

  tmp = elf->sym.start;
  while (tmp != elf->sym.end)
    {
      if ((void *)tmp > elf->end)
	return (fprintf(stderr, "Error : invalid file\n") && 0);
      if (tmp->st_info != STT_FILE
	  && tmp->st_info != STT_SECTION
	  && tmp->st_info != STT_NOTYPE)
	{
	  if ((void *)&elf->sym.strtab[tmp->st_name] > elf->end)
	    return (fprintf(stderr, "Error : invalid file\n") && 0);
	  if (tmp->st_value)
	    printf("%016x %c %s\n", (unsigned int)tmp->st_value, 42,
		   &elf->sym.strtab[tmp->st_name]);
	  else
	    printf("%18c %s\n", 42, &elf->sym.strtab[tmp->st_name]);
	}
      ++tmp;
    }
  return (1);
}

#define ELF_SHDR (Elf64_Shdr *)((void *)elf->ehdr + elf->ehdr->e_shoff))

#define SYM_START (Elf64_Sym *)((void *)elf->ehdr + elf->shdr[i].sh_offset))
#define SYM_END (Elf64_Sym *)((void *)elf->sym.start + elf->shdr[i].sh_size))
#define SYM_STR (char *)elf->ehdr + elf->shdr[elf->shdr[i].sh_link].sh_offset)

int		run_elf(t_elf *const elf)
{
  register int	i;

  if ((void *)(elf->shdr = ELF_SHDR > elf->end)
    return (fprintf(stderr, "Error : invalid file\n") && 0);
  i = -1;
  while (++i != elf->ehdr->e_shnum)
    {
      if ((void *)&(elf->shdr[i]) > elf->end)
	return (fprintf(stderr, "Error : invalid file\n") && 0);
      if (elf->shdr[i].sh_type == SHT_SYMTAB)
	{
	  if ((void *)(elf->sym.start = SYM_START > elf->end
	      || (void *)(elf->sym.end = SYM_END > elf->end
	      || (void *)(elf->sym.strtab = SYM_STR > elf->end)
	    return (fprintf(stderr, "Error : invalid file\n") && 0);
	}
    }
  return (print_sym(elf));
}
