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

static int	check_magic_number(t_elf *const elf)
{
  if (elf->len < sizeof(Elf64_Ehdr)
      || memcmp(elf->ehdr, MAGIC_NUMBER, sizeof(MAGIC_NUMBER) - 1))
    {
      fprintf(stderr, "File format not recognized\n");
      return (0);
    }
  return (1);
}

int	parse_file(char const *const file, t_elf *const elf)
{
  char	err[300];
  int	fd;

  if ((fd = open(file, O_RDONLY)) == -1)
    {
      sprintf(err, "open \"%s\"", file);
      perror(err);
      return (0);
    }
  if ((elf->len = lseek(fd, 0, SEEK_END)) == (unsigned)-1)
    {
      perror("lseek");
      return (0);
    }
  if (!(elf->ehdr = mmap(NULL, elf->len, PROT_READ, MAP_SHARED, fd, 0)))
    {
      perror("mmap");
      return (0);
    }
  elf->end = (void *)elf->ehdr + elf->len;
  return (check_magic_number(elf));
}
