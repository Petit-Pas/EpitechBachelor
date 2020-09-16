/*
** create_list_shape.c for tetris in /home/angevil124/prog/PSU/PSU_2016_tetris/benoit
**
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Tue Feb 21 09:09:51 2017 Benoit
** Last update Mon Mar 13 12:43:49 2017 Benoit
*/

#include <ncurses.h>
#include <stdlib.h>
#include "tetris.h"

void	put_center_coordinates(t_list *to_copy,
			       t_piece_falling *to_fill, t_map *map)
{
  to_fill->center_x_next = to_copy->data.size_x / 2
    + (map->size_max.col / 2 - to_copy->data.size_x / 2) + 1;
  to_fill->center_y_next = (to_copy->data.size_y + 1) / 2;
  to_fill->color_next = to_copy->data.color;
  to_fill->longest_x_next = to_copy->data.size_x;
}

int	create_tab_shape(t_list *to_copy,
			 t_piece_falling *to_fill, t_map *map, int i)
{
  int	x;
  int	y;

  y = 0;
  if (!(to_fill->coords_next = malloc(sizeof(unsigned char) *
				      ((to_copy->data.amount * 2) + 1))))
    return (84);
  while (y != to_copy->data.size_y)
    {
      x = 0;
      while (to_copy->data.shape[y][x] != '\0')
	{
	  if (to_copy->data.shape[y][x] == '*')
	    {
  	      to_fill->coords_next[i++] =
		(x + ((map->size_max.col / 2) - to_copy->data.size_x / 2)) + 49;
  	      to_fill->coords_next[i++] = y + 49;
  	    }
  	  x++;
  	}
      y++;
    }
  to_fill->coords_next[i] = '\0';
  put_center_coordinates(to_copy, to_fill, map);
  return (0);
}

void	put_first_center_coordinates(t_list *to_copy,
				     t_piece_falling *to_fill, t_map *map)
{
  to_fill->center_x = to_copy->data.size_x / 2 + (map->size_max.col / 2);
  to_fill->center_y = (to_copy->data.size_y + 1) / 2;
  to_fill->color = to_copy->data.color;
  to_fill->longest_x = to_copy->data.size_x;
}

int	create_first_tab_shape(t_list *to_copy,
			       t_piece_falling *to_fill, t_map *map, int i)
{
  int	x;
  int	y;

  i = 0;
  y = 0;
  if (!(to_fill->coords = malloc(sizeof(unsigned char) *
				 ((to_copy->data.amount * 2) + 1))))
    return (84);
  while (y != to_copy->data.size_y)
    {
      x = 0;
      while (to_copy->data.shape[y][x] != '\0')
	{
	  if (to_copy->data.shape[y][x] == '*')
	    {
  	      to_fill->coords[i++] = (x + (map->size_max.col / 2)) + 48;
  	      to_fill->coords[i++] = y + 49;
  	    }
  	  x++;
  	}
      y++;
    }
  to_fill->coords[i] = '\0';
  put_first_center_coordinates(to_copy, to_fill, map);
  return (0);
}

int	fill_tab_shape(t_list *new_one, t_piece_falling *to_fill, t_map *map)
{
  free(to_fill->coords);
  to_fill->coords = (unsigned char *)my_strcpy((char *)to_fill->coords_next);
  free(to_fill->coords_next);
  to_fill->center_x = to_fill->center_x_next;
  to_fill->center_y = to_fill->center_y_next;
  to_fill->color = to_fill->color_next;
  to_fill->longest_x = to_fill->longest_x_next;
  return (create_tab_shape(new_one, to_fill, map, 0));
}
