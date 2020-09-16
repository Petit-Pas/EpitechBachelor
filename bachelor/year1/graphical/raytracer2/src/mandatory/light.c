/*
** light.c for raytracer2 in /home/bastien/delivery/MUL/raytracer1/SRC
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Thu Feb 23 11:38:29 2017 bastien bedu
** Last update Fri May 26 07:59:38 2017 Benoit Hoffman
*/

#include	<SFML/System/Vector3.h>
#include	<math.h>

float		get_light_coef(sfVector3f light, sfVector3f normal)
{
  double	div;

  div = sqrt(powf(light.x, 2) + powf(light.y, 2) + powf(light.z, 2)) *
    sqrt(powf(normal.x, 2) + powf(normal.y, 2) + powf(normal.z, 2));
  if ((int)(div * 100000) == 0)
    return (0);
  div = (light.x * normal.x + light.y * normal.y +
	 light.z * normal.z) / div;
  if (div < 0)
    return (0);
  return ((float)(div));
}

float		true_get_light_coef(sfVector3f light, sfVector3f normal)
{
  double	div;
  double	dis;

  dis = sqrt(powf(light.x, 2) + powf(light.y, 2) + powf(light.z, 2));
  div = dis * sqrt(powf(normal.x, 2) + powf(normal.y, 2) + powf(normal.z, 2));
  if ((int)(div * 100000) == 0)
    return (0.1f);
  div = (light.x * normal.x + light.y * normal.y +
	 light.z * normal.z) / div;
  if (div < 0)
    return (0.1f);
  else if (div <= 0.11)
    div = 0.11;
  return ((float)(div));
}
