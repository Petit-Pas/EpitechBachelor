/*
** manage_loop.c for my_sokoban in /home/angevil124/prog/PSU/PSU_2016_my_sokoban
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Dec 12 16:22:20 2016 benoit
** Last update Wed Dec 14 13:08:33 2016 benoit
*/

#include "functions.h"

void	print_resize(t_map *map)
{
  while (LINES < map->row || COLS - 1 < map->col)
    {
      clear();
      refresh();
      mvprintw(LINES / 2 - 1, (COLS - 1) / 2, "resize");
      usleep(10);
      if (getch() == 410)
      	print_resize(map);
    }
}

void	refresh_window(t_map *map)
{
  clear();
  refresh();
  print_tab(map);
  usleep(10);
}
