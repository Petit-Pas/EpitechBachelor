/*
** check_validity.c for tetris in
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Wed Feb 22 13:40:52 2017 shintaro
** Last update Mon Mar 13 09:50:00 2017 Benoit
*/

#include <stdlib.h>
#include "tetris.h"

static int	free_tab_and_return(char *tab[14], int to_return, int length)
{
  int	i;

  i = 0;
  while (i <= length)
    {
      free(tab[i]);
      i++;
    }
  return (to_return);
}

int	check_validity_long(char *av, int i)
{
  char	*long_flag[14];

  long_flag[0] = my_strcpy("--help");
  long_flag[1] = my_strcpy("--level=*");
  long_flag[2] = my_strcpy("--key-left=*");
  long_flag[3] = my_strcpy("--key-right=*");
  long_flag[4] = my_strcpy("--key-turn=*");
  long_flag[5] = my_strcpy("--key-drop=*");
  long_flag[6] = my_strcpy("--key-quit=*");
  long_flag[7] = my_strcpy("--key-pause=*");
  long_flag[8] = my_strcpy("--map-size=*,*");
  long_flag[9] = my_strcpy("--without-next");
  long_flag[10] = my_strcpy("--debug");
  long_flag[11] = my_strcpy("-d");
  long_flag[12] = my_strcpy("-h");
  long_flag[13] = my_strcpy("-w");
  while (i <= 13 && long_flag[i] != NULL)
    {
      if (match(long_flag[i++], av) == 1)
	return (free_tab_and_return(long_flag, 0, 13));
    }
  if (i != 14)
    return (84);
  return (free_tab_and_return(long_flag, - 1, 13));
}

int	check_validity_short(char *av1, char *av2)
{
  char	*short_flag[10];
  int	i;

  i = 0;
  short_flag[0] = my_strcpy("-l");
  short_flag[1] = my_strcpy("-kl");
  short_flag[2] = my_strcpy("-kr");
  short_flag[3] = my_strcpy("-kt");
  short_flag[4] = my_strcpy("-kd");
  short_flag[5] = my_strcpy("-kq");
  short_flag[6] = my_strcpy("-kp");
  while (i <= 6 && short_flag[i] != NULL)
    {
      if (my_strcmp(av1, short_flag[i]) == 1 && av2 != NULL)
	return (free_tab_and_return(short_flag, 0, 6));
      i++;
    }
  if (i != 7)
    return (84);
  return (free_tab_and_return(short_flag, -1, 6));
}

int	check_validity(char **av)
{
  int	i;
  int	return_value;

  i = 1;
  while (av[i] != NULL)
    {
      return_value = check_validity_long(av[i], 0);
      if (return_value == 84)
	return (my_putstr("Malloc error\n", 2, 84));
      if (return_value == - 1)
	{
	  return_value = check_validity_short(av[i], av[i + 1]);
	  if (return_value == 84)
	    return (my_putstr("Malloc error\n", 2, 84));
	  if (return_value == - 1)
	    return (my_putstr("Input Validity Error\n", 2, 84));
	  else i += 2;
	}
      else
	i += 1;
    }
  return (0);
}
