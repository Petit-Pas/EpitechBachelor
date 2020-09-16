/*
** additional_fill_map.c for navy.c in /home/angevil124/prog/PSU/PSU_2016_navy
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Jan 31 08:45:12 2017 Benoit
** Last update Thu Feb  2 09:40:34 2017 Benoit
*/

#include <stdlib.h>
#include "navy.h"

int     is_alpha_or_num(char c, int mode)
{
  if (mode == 1)
    {
      if (c >= 'A' && c <= 'Z')
        return (1);
      else
        return (0);
    }
  if (c >= '0' && c <= '9')
    return (1);
  else
    return (0);
}

int     init_map(char **map)
{
  int   i;

  i = 2;
  map[0] = my_strcpy(" |A B C D E F G H");
  map[1] = my_strcpy("-+---------------");
  if (map[0] == NULL || map[1] == NULL)
    return (84);
  while (i != 10)
    {
      map[i] = my_strcpy(" |. . . . . . . .");
      if (map[i] == NULL)
        return (84);
      i++;
    }
  map[i] = NULL;
  i = 2;
  while (i != 10)
    {
      map[i][0] = (i - 1 + 48);
      i++;
    }
  return (0);
}

int     check_boats(char **boat)
{
  int   i;

  i = 0;
  while (boat[i] != NULL)
    {
      if (my_strlen(boat[i]) != 7)
        return (84);
      if (boat[i][0] - 48 != (i + 2))
        return (84);
      if (boat[i][1] != ':' && boat[i][4] != ':')
        return (84);
      if (is_alpha_or_num(boat[i][2], 1) == 0 ||
	  is_alpha_or_num(boat[i][3], 0) == 0)
        return (84);
      boat[i][2] -= 16;
      if (is_alpha_or_num(boat[i][5], 1) == 0 ||
	  is_alpha_or_num(boat[i][6], 0) == 0)
        return (84);
      boat[i][5] -= 16;
      i++;
    }
  return (0);
}

int     is_in_map(char *boat)
{
  if (boat[2] < '1' || boat[2] > '8')
    return (84);
  if (boat[3] < '1' || boat[3] > '8')
    return (84);
  if (boat[5] < '1' || boat[5] > '8')
    return (84);
  if (boat[6] < '1' || boat[6] > '8')
    return (84);
}

void	purify_boats(char **boat)
{
  int	i;

  i = 0;
  while (boat[i] != NULL)
    {
      change_coordinates(boat[i], 2);
      change_coordinates(boat[i], 5);
      i++;
    }
  change_boats(boat);
}
