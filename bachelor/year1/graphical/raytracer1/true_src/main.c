/*
** main.c for raytracrer1 in /home/angevil124/prog/graphical/bsraytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sun Feb 26 09:06:44 2017 Benoit
** Last update Sat Mar 18 09:15:50 2017 Benoit
*/

#include <math.h>
#include <stdlib.h>
#include <SFML/Graphics.h>

#include "framebuffer.h"

#define	FRAMEBUFFER_WIDTH 1920
#define FRAMEBUFFER_HEIGHT 1080

float   (*intersection[4])(sfVector3f eye_pos,
			   sfVector3f dir_vector,
			   float radius);

t_camera	*init_camera()
{
  t_camera	*camera;

  if (!(camera = malloc(sizeof(*camera))))
    return (NULL);
  camera->init_pos.x = - 600;
  camera->init_pos.y = 0;
  camera->init_pos.z = 10;
  camera->x_watched = 0;
  camera->y_watched = 0;
  camera->light.x = - 700;
  camera->light.y = 200;
  camera->light.z = 0;
  return (camera);
}

void	get_k_from_elem(t_my_framebuffer *buffer, t_elements *list,
			t_camera *camera, sfVector2i screen_size)
{
  t_elements	*temp;
  sfVector2i	screen_pos;

  camera->y_watched = 0;
  while (camera->y_watched != 1080)
    {
      temp = list;
      screen_pos.x = camera->x_watched;
      screen_pos.y = camera->y_watched;
      while (temp != NULL)
	{
	  camera->modified_pos = translate(temp->pos, camera->init_pos);
	  camera->modified_pos = rotate_xyz(camera->modified_pos, temp->rotations);
	  camera->dir_vector = calc_dir_vector(camera->modified_pos.x * - 1,
					       screen_size, screen_pos);
	  camera->dir_vector = rotate_xyz(camera->dir_vector, temp->rotations);
	  temp->k = intersection[temp->type](camera->modified_pos,
					     camera->dir_vector, temp->radius);
	  temp = temp->next;
	}
      check_light(list, buffer, camera);
      camera->y_watched++;
    }
}

void	raytrace_scene(t_my_framebuffer *buffer, t_elements *list,
		       t_camera *camera, t_window *window)
{
  sfVector2i	screen_size;

  screen_size.x = 1920;
  screen_size.y = 1080;
  while (camera->x_watched != 1920)
    {
      get_k_from_elem(buffer, list, camera, screen_size);
      display_window(window, buffer);
      camera->x_watched++;
    }
}

int                     main(int ac, char **av, char **env)
{
  t_window              *window;
  t_my_framebuffer      *buffer;
  t_elements		*list;
  t_camera		*camera;

  camera = init_camera();
  window = malloc(sizeof(*window));
  if (camera == NULL || window == NULL || check_env(env) == 84 || ac != 2)
    return (my_putstr("error in malloc or in ENV\n", 2, 84));
  window->texture = sfTexture_create(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
  if (!(list = init_parser(av[1])))
    return (my_putstr("error while creating the list of objects\n", 2, 84));
  get_mode(window, 1920, 1080, 32);
  window->window = sfRenderWindow_create(window->mode,
					 "raytracer", sfResize | sfClose, NULL);
  if (!(buffer = create_pixel_buffer(1920, 1080)))
    return (my_putstr("couldn't create pixel buffer\n", 2, 84));
  window->texture = sfTexture_create(1920, 1080);
  window->sprite = sfSprite_create();
  if (!(window->texture))
    return (84);
  sfSprite_setTexture(window->sprite, window->texture, sfTrue);
  raytrace_scene(buffer, list, camera, window);
  process_game_loop(window->window, window->sprite);
  return (end_game(window, buffer, list, camera));
}

int		process_game_loop(sfRenderWindow *window, sfSprite *sprite)
{
  sfEvent	event;

  while (sfRenderWindow_isOpen(window))
    {
      if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
        sfRenderWindow_close(window);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
    }
  return (0);
}
