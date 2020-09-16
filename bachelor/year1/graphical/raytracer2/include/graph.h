/*
** graph.h for raytracer2 in /home/bastien/delivery/MUL
** 
** Made by bastien bedu
** Login   <bastien@epitech.net>
** 
** Started on  Fri Jan 27 13:54:27 2017 bastien bedu
** Last update Sun May 28 09:05:39 2017 Benoit Hoffman
*/

#ifndef	GRAPH_H_
# define GRAPH_H_

# include		<SFML/Config.h>
# include		<SFML/Graphics/Types.h>
# include		<SFML/Graphics/Color.h>
# include               <SFML/System/Vector2.h>
# include               <SFML/System/Vector3.h>

# define SCREEN_WIDTH	1920
# define SCREEN_HEIGHT	1080
# define POV		-55

typedef	struct		s_my_framebuffer
{
  sfUint8		*pixels;
  int			width;
  int			height;
}			t_my_framebuffer;

typedef struct s_fig	t_fig;
typedef struct s_params t_params;
typedef struct s_window	t_window;

void                    set_ray(sfVector2i *screen_pos,
				t_my_framebuffer *frame, t_fig *fig);
sfVector3f		get_vectoriel_factor(sfVector3f *v1, sfVector3f *v2);
float			get_normal_of_vector(sfVector3f *v);
float			get_reflected_angle(sfVector3f *v1, sfVector3f *v2);
float			get_scalar_factor(sfVector3f *, sfVector3f *);
sfColor                 get_color(sfVector2i coords,
                                  sfVector2i modif,
                                  t_my_framebuffer *old_buffer);
void			set_coords(sfVector2i *vector, int x, int y);
void			do_blurring(t_window *window,
				    t_my_framebuffer *buffer,
				    t_my_framebuffer *old_buffer,
				    int blurr);
void			print_buffer(sfRenderWindow *window,
				     t_my_framebuffer *buffer,
				     sfTexture *texture,
				     sfSprite *sprite);
void                    anti_aliasing(t_window *window,
                                      t_my_framebuffer *buffer,
                                      t_my_framebuffer *old_buffer,
				      int blurr);
t_my_framebuffer	*my_framebuffer_create(int, int);
sfRenderWindow          *create_window(char *, int, int);
void			my_framebuffer_destroy(t_my_framebuffer *);
void			my_put_pixel(t_my_framebuffer *, int, int, sfColor);
void			init_params(t_my_framebuffer *frame,
				    t_fig *fig, t_params **params, int amount);
int                     check_amount_thread(char **argv);
sfVector2i              get_vect(int x, int y);

#endif			/* !GRAPH_H_ */
