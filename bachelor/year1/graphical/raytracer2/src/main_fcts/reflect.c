/*
** reflect.c for  in /home/bastien/delivery/MUL/raytracer2
** 
** Made by bastien bedu
** Login   <bastien.bedu@epitech.eu>
** 
** Started on  Sun May 28 00:02:51 2017 bastien bedu
** Last update Sun May 28 12:37:47 2017 bastien bedu
*/

#include        <SFML/System/Vector3.h>
#include        <stdlib.h>
#include        <math.h>
#include        "my.h"

void		reset_norm(sfVector3f *norm, float *z, float *y)
{
  sfVector3f	angle;

  *z = 0.0f;
  angle.x = 0.0f;
  if (norm->y != 0 && norm->x != 0)
    {
      *z = atan(norm->y / norm->x) * 180.0f / M_PI;
      angle.z = *z;
      angle.y = 0.0f;
      *norm = inv_rotate_xyz(*norm, angle);
    }
  *y = atan(norm->z / norm->x) * 180.0f / M_PI;
  angle.y = *y;
  angle.z = *z * -1;

}

sfVector3f	get_reflected_vector(sfVector3f incident, sfVector3f norm)
{
  sfVector3f	angle;
  float		z;
  float		y;

  set_vector(&incident, -1.0 * incident.x, -1.0 * incident.y,
	     -1.0 * incident.z);
  reset_norm(&norm, &z, &y);
  angle.x = 0.0f;
  angle.y = y;
  angle.z = z * -1;
  incident = rotate_zyx(incident, angle);
  set_vector(&angle, 180.0f, 0.0f, 0.0f);
  incident = rotate_zyx(incident, angle);
  set_vector(&angle, 0.0f, y, -1 * z);
  incident = inv_rotate_xyz(incident, angle);
  return (incident);
}

sfVector3f	get_refracted_vector(sfVector3f incident,
				     sfVector3f norm, t_fig *fig)
{
  sfVector3f	angle;
  float		z;
  float		y;
  float		x;
  float		ang_inter;

  reset_norm(&norm, &z, &y);
  set_vector(&angle, 0.0f, y, -1.0f * z);
  angle.x = 0.0f;
  angle.y = y;
  angle.z = z * -1;
  incident = rotate_zyx(incident, angle);
  x = 0.0f;
  if (incident.y != 0 && incident.x != 0)
    {
      x = atan(incident.y / incident.z) * 180.0f / M_PI;
      set_vector(&angle, x, 0.0f, 0.0f);
      incident = rotate_xyz(incident, angle);
    }
  ang_inter = atan(incident.z / incident.x) * 180.0f / M_PI;
  set_vector(&angle, 0.0, ang_inter - ang_inter / (1.0f / fig->density), 0.0f);
  incident = rotate_xyz(incident, angle);
  set_vector(&angle, x, y, -1.0f * z);
  incident = inv_rotate_xyz(incident, angle);
  return (incident);
}
