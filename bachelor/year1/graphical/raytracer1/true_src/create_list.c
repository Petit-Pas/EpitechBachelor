/*
** create_list.c for raytracer1 in /home/angevil124/prog/graphical/bsraytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Feb 11 08:03:34 2017 Benoit
** Last update Sun Feb 26 09:01:26 2017 Benoit
*/

#include <stdlib.h>
#include "framebuffer.h"

int	add_sphere_to_list(sfVector3f pos, sfColor color,
			   t_elements **list, float radius)
{
  t_elements	*elem;

  if (!(elem = malloc(sizeof(*elem))))
    return (84);
  elem->type = 0;
  elem->upward = 0;
  elem->pos = pos;
  elem->real_color = color;
  elem->radius = radius;
  elem->next = *list;
  *list = elem;
}

int	add_plane_to_list(sfVector3f pos, sfColor color, t_elements **list)
{
  t_elements	*elem;

  if (!(elem = malloc(sizeof(*elem))))
    return (84);
  elem->type = 1;
  elem->pos = pos;
  elem->real_color = color;
  elem->radius = 0;
  elem->upward = 1;
  elem->next = *list;
  *list = elem;
}

int	add_cylinder_to_list(sfVector3f pos, sfColor color,
			     t_elements **list, float radius)
{
  t_elements	*elem;

  if (!(elem = malloc(sizeof(*elem))))
    return (84);
  elem->type = 2;
  elem->pos = pos;
  elem->real_color = color;
  elem->radius = radius;
  elem->upward = 0;
  elem->next = *list;
  *list = elem;
}

int	add_cone_to_list(sfVector3f pos, sfColor color,
			 t_elements **list, float radius)
{
  t_elements	*elem;

  if (!(elem = malloc(sizeof(*elem))))
    return (84);
  elem->type = 3;
  elem->pos = pos;
  elem->real_color = color;
  elem->radius = radius;
  elem->upward = 0;
  elem->next = *list;
  *list = elem;
}

t_elements	*create_list_element()
{
  t_elements	*list;
  sfColor	color;
  sfVector3f	pos;
  sfVector3f	rotation;

  color.r = 255;
  color.g = 0;
  color.b = 0;
  color.a = 255;

  pos.x = 150;
  pos.y = -150;
  pos.z = 150;

  rotation.x = 35;
  rotation.y = 0;
  rotation.z = 0;
  list = NULL;
  return (list);
}

