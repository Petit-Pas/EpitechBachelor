/*
** globing2.c for 42sh in /home/angevil124/prog/PSU/PSU_2016_42sh
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Wed May 17 13:43:51 2017 Benoit Hoffman
** Last update Wed May 17 13:46:27 2017 Benoit Hoffman
*/

#include	<stdlib.h>
#include	<string.h>
#include	"globing.h"

void		modif_command_globing(t_globing *globings, int *nidx,
					  char *command, int *idx)
{
  globings->new_command = realloc(globings->new_command, *nidx + 2);
  globings->new_command[(*nidx)++] = command[*idx];
}

int		init_globing(char *command, t_globing *globings, int *idx,
				int *nidx)
{
  *idx = 0;
  *nidx = 0;
  globings->new_command = malloc(strlen(command) + 1);
  if (!globings->new_command || !command)
    return (1);
  return (0);
}
