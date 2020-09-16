/*
** key_del.c for  in /home/januar_m/delivery/PSU/edit_line
**
** Made by Martin Januario
** Login   <martin.januario@epitech.eu>
**
** Started on  Wed May 17 17:32:09 2017 Martin Januario
** Last update Fri May 19 14:52:22 2017 Martin Januario
*/

#include	<stdio.h>
#include	<curses.h>
#include	<term.h>
#include	<stdlib.h>
#include	<string.h>
#include	"edit.h"

void		key_del_(t_key *keys, __attribute__ ((unused)) char *str,
			 char **line)
{
  char		*tmp;
  int		idx;
  int		idx2;

  idx = 0;
  idx2 = 0;
  tmp = NULL;
  if (keys->idx <= 0)
    return ;
  tmp = strdup(*line);
  if (tmp == NULL)
    return ;
  while (tmp[idx] != '\0' && tmp[idx + 1] != '\0')
    {
      if (idx + 1 == keys->idx && idx2 == 0)
	idx2 = 1;
      (*line)[idx] = tmp[idx + idx2];
      idx++;
    }
  (*line)[idx] = '\0';
  keys->idx -= 1;
  free(tmp);
  printf(tgetstr("le", NULL));
  printf(tgetstr("dc", NULL));
  fflush(stdout);
}

void		key_sup_(t_key *keys, __attribute__ ((unused)) char *str,
			     char **line)
{
  char		*tmp;
  int		idx;
  int		idx2;

  idx = 0;
  idx2 = 0;
  tmp = NULL;
  if (!*line || keys->idx >= my_strlen(*line))
    return ;
  tmp = strdup(*line);
  if (tmp == NULL)
    return ;
  while (tmp[idx] != '\0' &&
	 tmp[idx + 1] != '\0')
    {
      if (idx == keys->idx)
	idx2 = 1;
      (*line)[idx] = tmp[idx + idx2];
      idx++;
    }
  (*line)[idx] = '\0';
  free(tmp);
  printf(tgetstr("dc", NULL));
  fflush(stdout);
}
