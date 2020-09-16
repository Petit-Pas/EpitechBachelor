/*
** basic_free.c for lib in /home/angevil124/lib
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sun Jan 22 15:57:52 2017 benoit
** Last update Mon Feb 13 10:16:24 2017 Benoit
*/

#include <stdlib.h>
#include "navy.h"

int	free_tab(char **tab, int return_value)
{
  int   i;

  i = 0;
  if (tab != NULL)
    {
      while (tab[i] != NULL)
        {
          free(tab[i]);
          i++;
        }
      free(tab);
    }
  return (return_value);
}

char	*free_and_return(char *to_free, char *to_return)
{
  free(to_free);
  return (to_return);
}

int	free_all(char **morse, t_map *map)
{
  free_tab(morse, 0);
  free_tab(map->map_perso, 0);
  free_tab(map->map_ennemy, 0);
  free(map);
  return (0);
}
