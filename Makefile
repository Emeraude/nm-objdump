##
## Makefile for  in /home/broggi_t/projet/nm-objdump
## 
## Made by broggi_t
## Login   <broggi_t@epitech.eu>
## 
## Started on  Mon Apr 13 17:50:20 2015 broggi_t
## Last update Mon Apr 13 17:50:20 2015 broggi_t
##

NAMENM	=	my_nm
NAMEOBJ	=	my_objdump

DIRNM	=	nm
DIROBJ	=	objdump

SRCSNM	=	$(DIRNM)/fill_symbol.c		\
		$(DIRNM)/main.c			\
		$(DIRNM)/run_elf.c		\
		$(DIRNM)/parse_file.c

SRCSOBJ	=	$(DIROBJ)/main.c		\
		$(DIROBJ)/parse_file.c		\
		$(DIROBJ)/write_data.c		\
		$(DIROBJ)/write_header.c

CFLAGS	+=	-W -Wall -Wextra -Werror
CFLAGS	+=	-I includes

CC	=	gcc

RM	=	rm -f

OBJSNM	=	$(SRCSNM:.c=.o)
OBJSOBJ	=	$(SRCSOBJ:.c=.o)

%.o: %.c
		@printf "[\033[0;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.'
		@$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

all:		nm objdump

nm:		$(NAMENM)

objdump:	$(NAMEOBJ);

$(NAMENM):	$(OBJSNM)
		@$(CC) $(OBJSNM) -o $(NAMENM) $(LDFLAGS)
		@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAMENM) | tr ' ' '.'

$(NAMEOBJ):	$(OBJSOBJ)
		@$(CC) $(OBJSOBJ) -o $(NAMEOBJ) $(LDFLAGS)
		@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAMEOBJ) | tr ' ' '.'

clean:
		@$(RM) $(OBJSNM)
		@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(OBJSNM) | tr ' ' '.'
		@$(RM) $(OBJSOBJ)
		@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(OBJSOBJ) | tr ' ' '.'

fclean:		clean
		@$(RM) $(NAMENM)
		@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(NAMENM) | tr ' ' '.'
		@$(RM) $(NAMEOBJ)
		@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(NAMEOBJ) | tr ' ' '.'

re:		fclean all

.PHONY:		all clean fclean re
