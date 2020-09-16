/*
** window_create.c for raytracer2 in /home/bastien/delivery/MUL
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Fri Jan 27 14:40:24 2017 bastien bedu
** Last update Fri May 26 07:58:40 2017 Benoit Hoffman
*/

#include		<SFML/Graphics/RenderWindow.h>

sfRenderWindow		*create_window(char *name, int width, int height)
{
  sfRenderWindow	*window;
  sfVideoMode		mode;

  mode.width = width;
  mode.height = height;
  mode.bitsPerPixel = 32;
  window = sfRenderWindow_create(mode, name, sfResize | sfClose, NULL);
  return (window);
}
