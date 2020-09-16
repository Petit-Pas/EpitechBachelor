/*
** new_main.c for raytracer2 in /home/angevil124/prog/graphical/raytracer2
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat May 27 09:50:15 2017 Benoit Hoffman
** Last update Sun May 28 14:11:19 2017 bastien bedu
*/

#include		<SFML/Graphics/RenderWindow.h>
#include		<SFML/Graphics/Sprite.h>
#include		<SFML/Graphics/Texture.h>
#include		<SFML/System/Vector2.h>
#include		<stdlib.h>
#include		"graph.h"
#include		"my.h"
#include		"my_struct.h"

void			aff_ray(t_window *window,
				t_my_framebuffer *old_buffer,
				int blurring)
{
  t_my_framebuffer	*frame;

  frame = my_framebuffer_create(SCREEN_WIDTH, SCREEN_HEIGHT);
  if (!frame)
    {
      sfRenderWindow_clear(window->window, sfBlack);
      sfRenderWindow_drawSprite(window->window, window->sprite, NULL);
      sfRenderWindow_display(window->window);
      while (sfRenderWindow_isOpen(window->window))
	{
	  if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
	    sfRenderWindow_close(window->window);
	}
    }
  else
    {
      anti_aliasing(window, frame, old_buffer, blurring);
      my_framebuffer_destroy(frame);
    }
}

int			my_strcomp(char *str, char *str2)
{
  int			i;

  i = 0;
  if (str2 == NULL || str == NULL)
    return (0);
  while (str[i] != '\0' && str[i] != '=' && str[i] == str2[i])
    i++;
  if (str[i] == '=' && str2[i] == '\0')
    {
      return (1);
    }
  return (0);
}

int			is_in(char **env, char *str)
{
  int			i;

  i = 0;
  while (env != NULL && env[i] != NULL && my_strcomp(env[i], str) == 0)
    i++;
  if (env[i] != NULL)
    return (1);
  return (0);
}

void			init_all(t_window *window)
{
  window->window = create_window("Raytracer", SCREEN_WIDTH, SCREEN_HEIGHT);
  window->sprite = sfSprite_create();
  window->texture = sfTexture_create(SCREEN_WIDTH, SCREEN_HEIGHT);
  sfSprite_setTexture(window->sprite, window->texture, sfTrue);
}

int			main(int ac, char **av, char **env)
{
  t_window		window;
  t_my_framebuffer	*frame;
  t_fig			*fig;

  fig = parsing(ac, av);
  if (fig == NULL || is_in(env, "DISPLAY") == 0)
    return (84);
  init_all(&window);
  frame = my_framebuffer_create(SCREEN_WIDTH, SCREEN_HEIGHT);
  if (window.window == NULL || frame == NULL
      || window.sprite == NULL || window.texture == NULL)
    return (84);
  if (you_can_thread_those(frame, fig, &window, av) == 84)
    {
      my_putstr(2, "error in thread\n");
      return (84);
    }
  sfTexture_updateFromPixels(window.texture, frame->pixels, frame->width,
			     frame->height, 0, 0);
  aff_ray(&window, frame, fig->shine);
  sfRenderWindow_destroy(window.window);
  my_framebuffer_destroy(frame);
  free_list(fig);
  return (0);
}
