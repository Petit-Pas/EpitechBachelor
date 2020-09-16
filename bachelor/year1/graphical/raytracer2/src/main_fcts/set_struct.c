/*
** set_struct.c for raytracer2 in /home/bastien/delivery/MUL/raytracer1
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Sun Mar 19 09:44:07 2017 bastien bedu
** Last update Fri May 26 07:57:37 2017 Benoit Hoffman
*/

#include	<SFML/Graphics/Color.h>
#include	<SFML/System/Vector3.h>
#include	"my.h"

void		set_color(sfColor *color, int r, int g, int b)
{
  color->r = nb_max(r, 255);
  color->g = nb_max(g, 255);
  color->b = nb_max(b, 255);
}

void		set_vector(sfVector3f *vector, float x, float y, float z)
{
  vector->x = x;
  vector->y = y;
  vector->z = z;
}
