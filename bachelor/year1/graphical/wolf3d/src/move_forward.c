/*
** move_forward.c for bswolf3d in /home/angevil124/prog/graphical/bswolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Dec 15 09:08:56 2016 benoit
** Last update Tue Dec 20 13:11:28 2016 benoit
*/

#include "fcts_and_strcts.h"

sfVector2f	move_forward(sfVector2f pos, float direction, float distance)
{
  direction = direction * M_PI / 180;
  pos.x = pos.x + distance * cos(direction);
  pos.y = pos.y + distance * sin(direction);
  return (pos);
}
