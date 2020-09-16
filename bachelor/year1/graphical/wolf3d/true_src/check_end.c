/*
** check_end.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Wed Dec 28 11:10:03 2016 benoit
** Last update Fri Feb  3 13:05:40 2017 Benoit
*/

#include "fcts_and_strcts.h"

int	is_on_end(t_map *map, t_player *player)
{
  if (map->map[(int)player->pos.y][(int)player->pos.x] == 3)
    {
      my_putstr("Congratulations, you won!\n");
      return (1);
    }
  else
    return (0);
}
