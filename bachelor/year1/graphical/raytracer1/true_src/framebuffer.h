/*
** fcts_and_strcts.h for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Dec 17 12:36:51 2016 benoit
** Last update Sun Mar 12 09:37:02 2017 Benoit
*/

#ifndef FRAMEBUFFER_H_
# define FRAMEBUFFER_H_

# include		<SFML/Graphics/RenderWindow.h>
# include		<SFML/Graphics/Sprite.h>
# include		<SFML/Graphics/Texture.h>
# include		<SFML/Audio.h>

typedef struct          s_window
{
  sfRenderWindow        *window;
  sfVideoMode           mode;
  sfSprite              *sprite;
  sfTexture             *texture;
}			t_window;

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
  int			type;
  sfColor		real_color;
  sfColor		seen_color;
  sfVector3f		pos;
  sfVector3f		rotations;
  float			radius;
  int			upward;
  float			k;
  struct s_elements	*next;
}			t_elements;

typedef struct          s_frame_buf
{
  sfUint8		*pixels;
  int			width;
  int			height;
}			t_my_framebuffer;

void			get_mode(t_window *window, int width,
				 int height, int bitsPerPixel);
sfVector3f		translate_then_rotate(sfVector3f to_modify,
				      sfVector3f translation,
				      sfVector3f rotate);
  int			my_putstr(char *str, int exit, int return_value);
int			end_game(t_window *window, t_my_framebuffer *buffer,
				 t_elements *list, t_camera *camera);
void			display_window(t_window *window, t_my_framebuffer *buffer);
int			count_argument(char *str);
void			go_to_next_semi(char *str, int *k);
t_my_framebuffer        *create_pixel_buffer(int width, int height);
int			check_env(char **env);
char			*get_next_line(int fd);
t_elements		*init_parser(char *str);
int			my_getnbr(char *str);
sfVector3f		rotate_xyz(sfVector3f to_rotate, sfVector3f angles);
sfVector3f		rotate_zyx(sfVector3f to_rotate, sfVector3f angles);
sfVector3f		get_normal_cone(sfVector3f intersection,
					float semiangle,
					int useless);
sfVector3f		get_normal_plane(sfVector3f useless,
					 float useless2,
					 int upward);
sfVector3f		get_normal_sphere(sfVector3f origin,
					  float useless,
					  int useless2);
sfVector3f		rotate_x(sfVector3f origin, float semiangle);
sfVector3f		rotate_y(sfVector3f origin, float semiangle);
sfVector3f		get_normal_cylinder(sfVector3f intersection_point,
					    float useless,
					    int useless2);
float			do_hard(float a, float b, float delta);
void			normalize_vector(sfVector3f *vector);
void			check_light(t_elements *objects,
				    t_my_framebuffer *buffer,
				    t_camera *camera);
sfVector3f		vector_between_points(sfVector3f pos1,
					      sfVector3f pos2);
float		        get_light_coef(sfVector3f light_vector,
				       sfVector3f point);
sfVector3f		calculate_light_vector(sfVector3f intersection_point,
					       t_camera *camera);
sfVector3f		calc_vector(sfVector3f vector);
sfVector3f		translate(sfVector3f vector, sfVector3f old_pos);
sfVector3f		reversed_translate(sfVector3f vector,
					   sfVector3f old_pos);
void			my_framebuffer_destroy(t_my_framebuffer *buffer);
void			check_which_pixel(t_elements *list,
					  t_my_framebuffer *buffer,
					  t_camera *camera);
int	                process_game_loop(sfRenderWindow *window,
					  sfSprite *sprite);
t_my_framebuffer	*my_framebuffer_create(int width, int height);
void			do_translation(t_camera *camera, t_elements *elem,
				       int mode);
t_elements		*create_list_element();
void			my_put_pixel(t_my_framebuffer *buffer, int x, int y,
				     sfColor color);
sfVector3f		calc_dir_vector(float dist_to_plane, sfVector2i screen_size,
					sfVector2i screen_pos);
float			intersect_sphere(sfVector3f eye_pos,
					 sfVector3f dir_vector,
					 float radius);
float			intersect_plane(sfVector3f eye_pos,
					sfVector3f dir_vector,
					float useless);
float			intersect_cylinder(sfVector3f eye_pos,
					   sfVector3f dir_vector,
					   float	angle);
float			intersect_cone(sfVector3f eye_pos,
				       sfVector3f dir_vector,
				       float semiangle);

#endif /* !FRAMEBUFFER_H_ */
