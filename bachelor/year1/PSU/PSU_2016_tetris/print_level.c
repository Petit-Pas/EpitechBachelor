/*
** print_level.c for tetris in /home/angevil124/prog/PSU/PSU_2016_tetris
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Mar  7 12:03:08 2017 Benoit
** Last update Tue Mar  7 12:04:06 2017 Benoit
*/

#include <ncurses.h>
#include "tetris.h"

void	print_level(t_map *map)
{
  if (map->level == 20)
    {
      mvprintw((LINES - map->size_max.row) / 2 + 3,
               (((COLS / 2) - map->size_max.col) - 20),
               "Level    MAXIMUM");
    }
  else
    {
      mvprintw((LINES - map->size_max.row) / 2 + 3,
               (((COLS / 2) - map->size_max.col) - 20),
               "Level       %02i", map->level);
    }
}
