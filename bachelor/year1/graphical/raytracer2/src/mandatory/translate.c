/*
** translate.c for raytracer2 in /home/bastien/delivery/MUL/raytracer1/SRC
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Tue Feb 14 18:43:43 2017 bastien bedu
** Last update Fri May 26 08:00:35 2017 Benoit Hoffman
*/

#include	<SFML/System/Vector3.h>

sfVector3f	translate(sfVector3f to_translate, sfVector3f translations)
{
  sfVector3f	new;

  new.x = to_translate.x + translations.x;
  new.y = to_translate.y + translations.y;
  new.z = to_translate.z + translations.z;
  return (new);
}

sfVector3f	inv_translate(sfVector3f to_translate, sfVector3f translations)
{
  sfVector3f	new;

  new.x = to_translate.x - translations.x;
  new.y = to_translate.y - translations.y;
  new.z = to_translate.z - translations.z;
  return (new);
}
