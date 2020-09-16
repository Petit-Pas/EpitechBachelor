/*
** key_pole.c for  in /home/januar_m/delivery/PSU/PSU_2016_42sh
** 
** Made by Martin Januario
** Login   <martin.januario@epitech.eu>
** 
** Started on  Thu May 18 14:22:24 2017 Martin Januario
** Last update Fri May 19 14:53:26 2017 Martin Januario
*/

#include	<curses.h>
#include	<term.h>
#include	<string.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	"edit.h"

void		key_end_(t_key *keys, char *str, char **line)
{
  while (keys->idx < my_strlen(*line))
    {
      printf(tgetstr("nd", NULL));
      fflush(stdout);
      keys->idx++;
    }
  (void) str;
}

void		key_begin_(t_key *keys, char *str, char **line)
{
  while (keys->idx > 0)
    {
      printf(tgetstr("le", NULL));
      fflush(stdout);
      keys->idx--;
    }
  (void) str;
  (void) line;
}
