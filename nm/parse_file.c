/*
** parse_file.c for  in /home/broggi_t/projet/nm-objdump/nm
** 
** Made by broggi_t
** Login   <broggi_t@epitech.eu>
** 
** Started on  Wed Apr 22 22:25:27 2015 broggi_t
** Last update Wed Apr 22 22:25:27 2015 broggi_t
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <elf.h>
#include "nm.h"

static int	check_magic_number(char const *const content,
				   unsigned int const len)
{
  if (len < sizeof(Elf64_Ehdr)
      || memcmp(content, MAGIC_NUMBER, sizeof(MAGIC_NUMBER) - 1))
    {
      fprintf(stderr, "File format not recognized\n");
      return (0);
    }
  return (1);
}

void	*parse_file(char const *const file)
{
  void	*content;
  char	err[300];
  int	fd;
  int	len;

  if ((fd = open(file, O_RDONLY)) == -1)
    {
      sprintf(err, "open \"%s\"", file);
      perror(err);
      return (NULL);
    }
  if ((len = lseek(fd, 0, SEEK_END)) == -1)
    {
      perror("lseek");
      return (NULL);
    }
  if (!(content = mmap(NULL, len, PROT_READ, MAP_SHARED, fd, 0)))
    {
      perror("mmap");
      return (NULL);
    }
  return (check_magic_number(content, len) ? content : NULL);
}
