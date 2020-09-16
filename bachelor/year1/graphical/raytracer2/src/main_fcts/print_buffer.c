/*
** print_buffer.c for raytracer2 in /home/angevil124/prog/graphical/raytracer2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri May 26 10:54:35 2017 Benoit Hoffman
** Last update Fri May 26 11:01:25 2017 Benoit Hoffman
*/

#include        <SFML/Graphics/RenderWindow.h>
#include	<SFML/Graphics/Sprite.h>
#include        <SFML/Graphics/Texture.h>
#include	<stdlib.h>
#include	"graph.h"

void		print_buffer(sfRenderWindow *window,
			     t_my_framebuffer *buffer,
			     sfTexture *texture,
			     sfSprite *sprite)
{
  sfTexture_updateFromPixels(texture, buffer->pixels, buffer->width,
			     buffer->height, 0, 0);
  sfRenderWindow_clear(window, sfBlack);
  sfRenderWindow_drawSprite(window, sprite, NULL);
  sfRenderWindow_display(window);
}
