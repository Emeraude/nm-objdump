/*
** nm.h for  in /home/broggi_t/projet/nm-objdump/includes
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Wed Apr 22 22:29:58 2015 broggi_t
** Last update Wed Apr 22 22:29:58 2015 broggi_t
*/

#ifndef NM_H_
# define NM_H_

# include <elf.h>

# define MAGIC_NUMBER	"\177ELF"

typedef struct		s_sym
{
  Elf64_Sym const	*start;
  Elf64_Sym const	*end;
  char const		*strtab;
}			t_sym;

typedef struct		s_symbol
{
  unsigned int		value;
  char			type;
  char const		*name;
}			t_symbol;

typedef struct		s_elf
{
  Elf64_Ehdr const	*ehdr;
  Elf64_Shdr const	*shdr;
  unsigned int		len;
  void			*end;
  t_sym			sym;
}			t_elf;

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS	0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE	1
# endif

int	parse_file(char const *const file, t_elf *const elf);

int	run_elf(t_elf *const elf);

void	fill_symbol(t_elf *const elf,
		    Elf64_Sym const *const sym,
		    t_symbol *const symbol);

#endif /* !NM_H_ */
