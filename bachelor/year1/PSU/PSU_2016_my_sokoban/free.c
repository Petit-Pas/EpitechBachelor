/*
** free.c for my_sokoban in /home/angevil124/prog/CPE/CPE_2016_BSQ
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Dec  6 15:11:02 2016 benoit
** Last update Wed Dec 14 13:08:19 2016 benoit
*/

#include "functions.h"

int	free_map(t_map *map, t_player *player, int result)
{
  int	i;

  free(player);
  i = 0;
  while (i != map->row)
    {
      free(map->map_init[i]);
      free(map->map[i]);
      i++;
    }
  free(map->map);
  free(map->map_init);
  free(map);
  endwin();
  return (result);
}
