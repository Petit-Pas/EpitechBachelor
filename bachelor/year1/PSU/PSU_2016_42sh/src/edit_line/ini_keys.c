/*
** ini_keys.c for  in /home/januar_m/delivery/PSU/edit_line
**
** Made by Martin Januario
** Login   <martin.januario@epitech.eu>
**
** Started on  Wed May 17 15:50:20 2017 Martin Januario
** Last update Thu May 18 19:42:34 2017 Martin Januario
*/

#include	<stdio.h>
#include	<curses.h>
#include	<term.h>
#include	<unistd.h>
#include	"edit.h"

static int	check(char *str)
{
  if (str == (char *) -1)
    return (1);
  return (0);
}

int		ini_keys(t_key *keys, char *term)
{
  char		*tmp;
  int		ret;
  int		idx;

  idx = 0;
  if (setupterm(term, 1, &ret) == ERR)
    return (84);
  tmp = tigetstr("smkx");
  keys->key[0] = tigetstr("kcub1");
  keys->key[1] = tigetstr("kcuf1");
  keys->key[2] = tigetstr("kcuu1");
  keys->key[3] = tigetstr("kcud1");
  keys->key[4] = tigetstr("kdch1");
  keys->key[5] = tigetstr("khome");
  keys->key[6] = tigetstr("kend");
  keys->key[7] = tigetstr("kLFT");
  keys->key[8] = tigetstr("kRIT");
  keys->key[9] = NULL;
  while (keys->key[idx] != NULL)
    if (check(keys->key[idx++]) == 1)
      return (84);
  if (isatty(0) == 1 && !check(tmp))
    printf(tmp);
  return ((check(tmp) || idx != 9) ? 84 : 0);
}
