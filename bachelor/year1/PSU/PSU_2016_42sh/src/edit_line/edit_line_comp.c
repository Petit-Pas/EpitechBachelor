/*
** edit_line_comp.c for PSU_2016_42sh in /home/shintaro/Work/Epitech/delivery/PSU_2016_42sh
**
** Made by Thomas GRANDJEAN
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Fri May 19 15:49:18 2017 Thomas GRANDJEAN
** Last update Fri May 19 21:53:38 2017 Sahel Lucas--Saoudi
*/

#include	<sys/ioctl.h>
#include	<term.h>
#include	<curses.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	"edit.h"

static char		*my_concat(char *line, char *str, t_key *keys)
{
  char			*tmp;

  if (line == NULL)
  {
    tmp = strdup(str);
    return (tmp);
  }
  else
  {
    tmp = malloc(my_strlen(str) + my_strlen(line) + 2);
    if (!tmp)
      return (NULL);
  }
  tmp[0] = '\0';
  strncat(tmp, line, keys->idx);
  strcat(tmp, str);
  strcat(tmp, &line[keys->idx]);
  return (tmp);
}

static void		print_line(char *str)
{
  printf(tgetstr("im", NULL));
  printf(str);
  printf(tgetstr("ei", NULL));
  fflush(stdout);
}

char		*move_line(char *line, char *str, t_key *keys)
{
  line = my_concat(line, str, keys);
  if (line == NULL)
    return (NULL);
  keys->idx += my_strlen(str);
  print_line(str);
  return (line);
}
