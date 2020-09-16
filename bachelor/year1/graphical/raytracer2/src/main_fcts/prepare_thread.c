/*
** prepare_thread.c for raytracer2 in /home/angevil124/prog/graphical/raytracer2
**
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Sat May 27 09:26:38 2017 Benoit Hoffman
** Last update Sun May 28 14:09:06 2017 bastien bedu
*/

#include                <stdlib.h>
#include                <SFML/Graphics.h>
#include                <pthread.h>
#include                "my_struct.h"
#include                "graph.h"
#include                "my.h"

void			init_params(t_my_framebuffer *frame,
				    t_fig *fig, t_params **params, int amount)
{
  int			i;

  i = 0;
  while (i < amount)
    {
      params[i] = malloc(sizeof(t_params));
      params[i]->fig = fig;
      params[i]->frame = frame;
      params[i]->step = 0;
      params[i]->from = get_vect(i, 0);
      params[i]->skip = amount;
      i += 1;
    }
  params[i] = NULL;
}

int			check_amount_thread(char **argv)
{
  int			i;
  int			amount;

  amount = 50;
  i = 0;
  while (argv[i] != NULL)
    {
      if ((my_strcmp(argv[i], "-t") == 0 ||
	   my_strcmp(argv[i], "--thread") == 0)
	  && argv[i + 1] != NULL)
	amount = my_getnbr(argv[i + 1]);
      i += 1;
    }
  if (amount > 100)
    return (100);
  if (amount < 1)
    return (50);
  return (amount);
}
