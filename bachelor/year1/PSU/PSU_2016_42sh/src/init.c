/*
** init.c for 42sh in /home/angevil124/prog/PSU/PSU_2016_42sh
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri May 19 13:50:52 2017 Benoit Hoffman
** Last update Fri May 19 14:18:26 2017 Benoit Hoffman
*/

#include		<stdio.h>
#include		<unistd.h>
#include		<stdlib.h>
#include		<term.h>
#include		"edit.h"

void		prompt(int nb)
{
  if (isatty(0) == 1)
  {
    printf("%03i >", nb);
    fflush(stdout);
  }
}

static int		print_error_and_return(char *str)
{
  dprintf(2, str);
  return (84);
}

int			initial_checks(char **env, t_key *keys,
				       struct termios *new,
				       struct termios *save)
{
  int			pos;

  keys->input = 0;
  pos = found_term(env);
  if (isatty(0) == 1 && pos == -1)
  {
    keys->input = 1;
    return (0);
  }
    if (isatty(0) == 1 && (tgetent(NULL, &env[pos][5]) < 0
                         || tcgetattr(0, new) < 0 || tcgetattr(0, save) < 0))
    return (print_error_and_return("Cannot set new Term.\n"));
  new->c_lflag &= ~(ICANON | ECHO);
  if (isatty(0) == 1 && tcsetattr(0, TCSANOW, new) == -1)
    return (print_error_and_return("Cannot set new attribute.\n"));
  if (isatty(0) == 1 && ini_keys(keys, &env[pos][5]) == 84)
    return (print_error_and_return("Cannot get keys.\n"));
  return (0);
}
