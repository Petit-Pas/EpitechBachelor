/*
** main.c for  in /home/januar_m/delivery/PSU/edit_line
**
** Made by Martin Januario
** Login   <martin.januario@epitech.eu>
**
** Started on  Wed May 17 15:35:14 2017 Martin Januario
** Last update Fri May 19 15:43:02 2017 Sahel Lucas--Saoudi
*/

#include	<sys/ioctl.h>
#include	<term.h>
#include	<curses.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	"edit.h"

static void		get_cols(t_key *keys)
{
  struct winsize	w;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  keys->cols = w.ws_col;
}

static char		*ctrl_d(char *line)
{
  printf("\n");
  reset_command(NULL, 2);
  return ((line == NULL) ? strdup("") : line);

}

char		*loop_read(t_key *keys)
{
  char		str[8];
  char		*line;
  int		size;

  prompt(keys->shell->status % 255);
  keys->idx = 0;
  line = NULL;
  get_cols(keys);
  size = read(0, &str, 7);
  while (size > 0)
    {
      str[size] = '\0';
      if (strcmp(str, "\n") == 0)
	return (ctrl_d(line));
      if ((my_strlen(str) == 1 && str[0] == 4 && my_strlen(line) == 0))
	return (NULL);
      if (check_is_key(keys, str, &line) == 0 &&
	  my_strlen(line) + my_strlen(str) < keys->cols)
	line = move_line(line, str, keys);
      get_cols(keys);
      size = read(0, &str, 7);
    }
  return (line);
}
