/*
** objdump.h for  in /home/broggi_t/projet/nm-objdump
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sat Apr 25 07:57:55 2015 broggi_t
** Last update Sat Apr 25 07:57:55 2015 broggi_t
*/

#ifndef OBJDUMP_H_
# define OBJDUMP_H_

# include <elf.h>

# define MAGIC_NUMBER	"\177ELF"

typedef struct		s_machine
{
  uint16_t const	key;
  char const *const	str;
}			t_machine;

typedef struct		s_elf
{
  Elf64_Ehdr const	*ehdr;
  Elf64_Shdr const	*shdr;
  unsigned int		len;
  void			*end;
  char const		*strtab;
  char const		*file_name;
}			t_elf;

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS	0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE	1
# endif

# define IS_PRINTABLE(x)	(x >= ' ' && x <= '~')
# define SIZE(x)		(sizeof(x) / sizeof(*x))

# define STRTAB (void *)elf->ehdr + elf->shdr[elf->ehdr->e_shstrndx].sh_offset

int	parse_file(char const *const file, t_elf *const elf);

int	write_header(t_elf *const elf);

int	write_data(t_elf *const elf);

#endif /* !OBJDUMP_H_ */
