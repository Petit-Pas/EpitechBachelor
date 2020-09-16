/*
** thread.c for raytracer2 in /home/angevil124/prog/graphical/raytracer2/threading/raytracer1
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue May  9 15:21:18 2017 Benoit Hoffman
** Last update Sun May 28 11:40:13 2017 Benoit Hoffman
*/

#include		<stdlib.h>
#include		<SFML/Graphics.h>
#include		<pthread.h>
#include		"graph.h"
#include		"my.h"
#include		"my_struct.h"

sfVector2i		get_vect(int x, int y)
{
  sfVector2i		vector;

  vector.x = x;
  vector.y = y;
  return (vector);
}

void			initiate_step(int *step, int amount, t_params **params)
{
  int			i;

  i = 0;
  while (i < amount)
    {
      step[i] = params[i]->step;
      i += 1;
    }
}

int			check_step(int *step, int amount)
{
  int			i;

  i = 0;
  while (i < amount)
    {
      if (step[i] != 1)
	return (0);
      i += 1;
    }
  return (1);
}

static void		wait_for_them(t_params **params, t_window *window,
				      t_my_framebuffer *frame, int amount)
{
  int			step[amount];
  int			i;

  i = 0;
  while (i < amount)
    step[i++] = 0;
  while (check_step(step, amount) == 0)
    {
      initiate_step(step, amount, params);
      sfTexture_updateFromPixels(window->texture, frame->pixels, frame->width,
				 frame->height, 0, 0);
      sfRenderWindow_clear(window->window, sfBlack);
      sfRenderWindow_drawSprite(window->window, window->sprite, NULL);
      sfRenderWindow_display(window->window);
      i = 0;
      while (i < 25000000)
	i += 1;
    }
}

int			you_can_thread_those(t_my_framebuffer *frame,
					     t_fig *fig, t_window *window,
					     char **argv)
{
  t_params		**params;
  int			i;
  int			amount;
  pthread_t		*thread;

  amount = 0;
  i = 0;
  amount = check_amount_thread(argv);
  thread = malloc(sizeof(pthread_t*) * amount);
  params = malloc(sizeof(t_params *) * (amount + 1));
  if (thread == NULL || params == NULL)
    return (84);
  init_params(frame, fig, params, amount);
  while (i < amount)
    {
      if (pthread_create(&thread[i], NULL, raytrace, (void *)params[i]) == -1)
	return (84);
      i += 1;
    }
  wait_for_them(params, window, frame, amount);
  return (0);
}
