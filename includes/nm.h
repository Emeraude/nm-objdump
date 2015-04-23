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

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS	0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE	1
# endif

void	*parse_file(char const *const file);

int	run_elf(Elf64_Ehdr const *const ehdr);

#endif /* !NM_H_ */
