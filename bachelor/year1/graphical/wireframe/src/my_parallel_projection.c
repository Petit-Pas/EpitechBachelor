/*
** my_parallel_projection.c for my_parallel_projection.c in /home/angevil124/prog/graphical/bswireframe/projection
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Dec  2 15:53:36 2016 benoit
** Last update Sat Dec 10 13:33:06 2016 benoit
*/

#include <math.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>

sfVector2i	my_parallel_projection(sfVector3f pos3d, float angle)
{
  sfVector2i	result;
  float		true_angle;
  float		temp_x;
  float		temp_y;
  float		cosinus;
  float		sinus;

  temp_x = 0;
  temp_y = 0;
  true_angle = angle * M_PI / 180;
  cosinus = cos(true_angle);
  sinus = sin(true_angle);
  if (cosinus < 0)
    cosinus = cosinus * - 1;
  if (sinus < 0)
    sinus = sinus * - 1;
  temp_x += pos3d.x;
  temp_y = pos3d.y * sinus;
  temp_x -= pos3d.y * cosinus;
  temp_y -= pos3d.z;
  result.x = temp_x;
  result.y = temp_y;
  return (result);
}
