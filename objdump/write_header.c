/*
** write_header.c for  in /home/broggi_t/projet/nm-objdump/objdump
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sat Apr 25 08:02:57 2015 broggi_t
** Last update Sat Apr 25 08:02:57 2015 broggi_t
*/

#include <stdio.h>
#include <elf.h>
#include "objdump.h"

#define SIZE(x)	(sizeof(x) / sizeof(*x))

static char const		*machine_name(t_elf *const elf)
{
  register int			i;
  static t_machine const	machines[] = {{EM_NONE, "None"},
					      {EM_M32, "WE32100"},
					      {EM_SPARC, "Sparc"},
					      {EM_386, "Intel 80386"},
					      {EM_68K, "MC68000"},
					      {EM_88K, "MC88000"},
					      {EM_860, "Intel 80860"},
					      {EM_MIPS, "MIPS R3000"},
					      {EM_PARISC, "HPPA"},
					      {EM_SPARC32PLUS, "Sparc v8+"},
					      {EM_PPC, "PowerPC"},
					      {EM_PPC64, "PowerPC64"},
					      {EM_S390, "IBM S/390"},
					      {EM_ARM, "ARM"},
					      {EM_SH, "Renesas / SuperH SH"},
					      {EM_SPARCV9, "Sparc v9"},
					      {EM_IA_64, "Intel IA-64"},
					      {EM_X86_64, "i386:x86-64"}};

  i = -1;
  while ((unsigned)++i < SIZE(machines))
    if (machines[i].key == elf->ehdr->e_machine)
      return (machines[i].str);
  return ("i386:x86-64");
}

int	write_header(t_elf *const elf)
{
  printf("\n%s:     file format %s\n", elf->file_name, "elf64-x86-64");
  printf("architecture: %s, flags 0x%08x:\n", machine_name(elf),
	 elf->ehdr->e_flags);
  printf("start address 0x%016lx\n\n", elf->ehdr->e_entry);
  return (1);
}
