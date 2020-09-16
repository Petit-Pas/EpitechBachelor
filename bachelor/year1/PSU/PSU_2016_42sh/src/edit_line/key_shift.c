/*
** key_shift.c for  in /home/januar_m/delivery/PSU/PSU_2016_42sh
** 
** Made by Martin Januario
** Login   <martin.januario@epitech.eu>
** 
** Started on  Thu May 18 19:44:16 2017 Martin Januario
** Last update Fri May 19 14:53:11 2017 Martin Januario
*/

#include	<curses.h>
#include	<term.h>
#include	"edit.h"

static void	move_cursor(t_key *keys, char *str, int i)
{
  printf(tgetstr(str, NULL));
  keys->idx += i;
  fflush(stdout);
}

void		key_sleft_(t_key *keys, __attribute__ ((unused)) char *str,
			       char **line)
{
  unsigned int	check;
  unsigned int	save;
  unsigned int	cpt;

  check = 0;
  save = 0;
  cpt = 0;
  while (*line && keys->idx > 0)
    {
      if ((*line)[keys->idx] != ' ' && cpt != 0)
	{
	  if (save == cpt)
	    save = 0;
	  check += 1;
	}
      else
	save += 1;
      if (check >= 1 && save >= 1)
	{
	  move_cursor(keys, "nd", 1);
	  return ;
	}
      move_cursor(keys, "le", -1);
      cpt++;
    }
}

void		key_sright_(t_key *keys, __attribute__ ((unused)) char *str,
				char **line)
{
  unsigned int	check;
  unsigned int	save;
  unsigned int	cpt;

  check = 0;
  save = 0;
  cpt = 0;
  while (*line && (*line)[keys->idx] != '\0')
    {
      if ((*line)[keys->idx] != ' ' && cpt != 0)
	{
	  if (save == cpt)
	    save = 0;
	  check += 1;
	}
      else
	save += 1;
      if (check >= 1 && save >= 1)
	return ;
      printf(tgetstr("nd", NULL));
      fflush(stdout);
      keys->idx++;
      cpt++;
    }
}
