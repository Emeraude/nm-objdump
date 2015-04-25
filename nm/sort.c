/*
** sort.c for  in /home/broggi_t/projet/nm-objdump/nm
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Sun Apr 26 00:34:32 2015 broggi_t
** Last update Sun Apr 26 00:34:32 2015 broggi_t
*/

#include <string.h>
#include "nm.h"

static void	swap(t_symbol *const a, t_symbol *const b)
{
  t_symbol	c;

  memcpy(&c, a, sizeof(c));
  memcpy(a, b, sizeof(c));
  memcpy(b, &c, sizeof(c));
}

static int	yolo_cmp(char const *a, char const *b)
{
  while (strchr("_@", *a))
    ++a;
  while (strchr("_@", *b))
    ++b;
  return (strcasecmp(a, b));
}

void		sort_sym(t_symbol *const sym_list, int const sort)
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
	if (sort == 24)
	  {
	    if (strcmp(sym_list[i].name, sym_list[j].name) > 0)
	      swap(&sym_list[i], &sym_list[j]);
	  }
	else if (yolo_cmp(sym_list[i].name, sym_list[j].name) > 0)
	  swap(&sym_list[i], &sym_list[j]);
      ++j;
    }
}
