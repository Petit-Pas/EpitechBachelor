/*
** fcts_and_strcts.h for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Dec 17 12:36:51 2016 benoit
** Last update Mon Mar 13 08:18:09 2017 Benoit
*/

#ifndef FRAMEBUFFER_H_
# define FRAMEBUFFER_H_

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Audio.h>

typedef struct		s_camera
{
  sfVector3f		init_pos;
  sfVector3f		modified_pos;
  sfVector3f		dir_vector;
  sfVector3f		light;
  int			x_watched;
  int			y_watched;
}			t_camera;

typedef struct		s_elements
{
  char			type;
  sfColor		real_color;
  sfColor		seen_color;
  sfVector3f		pos;
  float			radius;
  float			k;
  struct s_elements	*next;
}			t_elements;

typedef struct          s_frame_buf
{
  sfUint8		*pixels;
  int			width;
  int			height;
}			t_my_framebuffer;

float			do_hard(float a, float b, float delta);
sfVector3f		rotate_y(sfVector3f old, float angle);
sfVector3f		rotate_x(sfVector3f old, float angle);
sfVector3f		get_normal_cylinder(sfVector3f point);
sfVector3f		calc_vector(sfVector3f vector);
sfVector3f		translate(sfVector3f vector, sfVector3f old_pos);
void			my_framebuffer_destroy(t_my_framebuffer *buffer);
void			check_which_pixel(t_elements *list,
					  t_my_framebuffer *buffer,
					  t_camera *camera);
int	                process_game_loop(sfRenderWindow *window,
					  sfSprite *sprite);
t_my_framebuffer	*my_framebuffer_create(int width, int height);
void			do_translation(t_camera *camera,
				       t_elements *elem, int mode);
t_elements		*create_list_element();
void			my_put_pixel(t_my_framebuffer *buffer,
				     int x, int y, sfColor color);
sfVector3f		calc_dir_vector(float dist_to_plane,
					sfVector2i screen_size,
					sfVector2i screen_pos);
float			intersect_sphere(sfVector3f eye_pos,
					 sfVector3f dir_vector, float radius);
float			intersect_plane(sfVector3f eye_pos,
					sfVector3f dir_vector);

#endif /* !FRAMEBUFFER_H_ */
