/*
** basic_key.c for  in /home/januar_m/delivery/PSU/edit_line
**
** Made by Martin Januario
** Login   <martin.januario@epitech.eu>
**
** Started on  Wed May 17 17:30:27 2017 Martin Januario
** Last update Fri May 19 21:56:15 2017 Sahel Lucas--Saoudi
*/

#include	<stdio.h>
#include	<curses.h>
#include	<string.h>
#include	<term.h>
#include	<stdlib.h>
#include	"edit.h"
#include	"history.h"

void		key_left_(t_key *keys, char *str, char **line)
{
  if (keys->idx < 1)
    return ;
  keys->idx -= 1;
  printf(tgetstr("le", NULL));
  fflush(stdout);
  (void) str;
  (void) line;
}

void		key_right_(t_key *keys, char *str, char **line)
{
  if (keys->idx >= my_strlen(*line))
    return ;
  keys->idx += 1;
  printf(tgetstr("nd", NULL));
  fflush(stdout);
  (void) str;
  (void) line;
}

char		*reset_command(char *command, int st)
{
  static char	*com = NULL;

  if (st == 1 && com == NULL)
    {
      if (command != NULL)
	{
	  com = strdup(command);
	  return (command);
	}
      else
	{
	  com = strdup("");
	  return (com);
	}
    }
  else if (st == 2)
    {
      com = NULL;
      return (command);
    }
  return (com);
}

void		key_top_(t_key *keys, char *str, char **line)
{
  char		*command;

  command = reset_command(*line, 1);
  keys->shell->command = *line;
  if (!command)
    return ;
  *line = history(command, keys->shell, -1);
  printf(tgetstr("dl", NULL));
  prompt(keys->shell->status);
  if (*line != NULL)
    printf("%s", *line);
  fflush(stdout);
  keys->idx = my_strlen(*line);
  (void) str;
}

void		key_bottom_(t_key *keys, char *str, char **line)
{
  char		*command;

  command = reset_command(*line, 1);
  keys->shell->command = *line;
  if (!command)
    return ;
  *line = history(command, keys->shell, 1);
  printf(tgetstr("dl", NULL));
  prompt(keys->shell->status);
  if (*line != NULL)
    printf("%s", *line);
  fflush(stdout);
  keys->idx = my_strlen(*line);
  (void) str;
}
