/*
** free.c for bsq in /home/angevil124/prog/CPE/CPE_2016_BSQ
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Dec  6 15:11:02 2016 benoit
** Last update Tue Dec  6 15:24:09 2016 benoit
*/

#include <stdlib.h>
#include "structs.h"

void	free_tab(char **tab, int nb)
{
  int	i;

  i = 0;
  while (i != nb)
    {
      free(tab[i]);
      i++;
    }
  free(tab);
}

void	free_map(t_map *map)
{
  int	i;

  i = 0;
  while (i != map->row)
    {
      free(map->map[i]);
      i++;
    }
  free(map->map);
  free(map);
}
