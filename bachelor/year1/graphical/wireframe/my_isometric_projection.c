/*
** my_isometric_projection.c for my_isometric_projection in /home/angevil124/prog/graphical/bswireframe/projection
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sun Dec  4 09:59:23 2016 benoit
** Last update Fri Dec  9 10:24:48 2016 benoit
*/

#include <math.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>

float	abs_val(float nb)
{
  while (nb < 0)
    nb = nb * - 1;
  return (nb);
}

sfVector2i	my_isometric_projection(sfVector3f pos3d)
{
  sfVector2i	result;
  float		true_angle;
  float		temp_x;
  float		temp_y;
  float		cosinus;
  float		sinus;
  float		hyp;

  true_angle = 30 * M_PI / 180;
  cosinus = abs_val(cos(true_angle));
  sinus = abs_val(sin(true_angle));
  temp_x = pos3d.x * cosinus - (pos3d.y * cosinus);
  temp_y = pos3d.y * sinus + pos3d.x * sinus;
  hyp = sqrt(sinus * sinus + cosinus * cosinus);
  temp_y -= hyp * pos3d.z;
  result.x = temp_x;
  result.y = temp_y;
  return (result);
}
