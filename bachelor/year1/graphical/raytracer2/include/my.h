/*
** my.h for raytracer2 in /home/bastien/delivery/MUL/raytracer1
**
** Made by bastien bedu
** Login   <bastien@epitech.net>
**
** Started on  Sun Feb 12 18:46:22 2017 bastien bedu
** Last update Sun May 28 18:13:53 2017 Martin Van Elslande
*/

#ifndef MY_H_
# define MY_H_

# include       <SFML/System/Vector2.h>
# include       <SFML/System/Vector3.h>
# include	"my_struct.h"
# include	"graph.h"

t_fig		*get_light_fig(t_fig *);
t_fig		*get_beg_fig(t_fig *);
t_fig		*set_tmp(double, double *, t_fig **, t_fig *);
sfColor		calc_all(t_fig *, sfVector3f *, sfVector3f *, int);
sfVector3f	get_normal_sphere(sfVector3f);
sfVector3f	get_normal_cone(sfVector3f, float);
sfVector3f	get_normal_cylinder(sfVector3f);
sfVector3f	get_normal_plane(int);
sfVector3f	calc_dir_vector(float, sfVector2i, sfVector2i);
sfVector3f	true_calc_dir_vector(sfVector3f, sfVector2i);
sfVector3f	translate(sfVector3f, sfVector3f);
sfVector3f	inv_translate(sfVector3f, sfVector3f);
sfVector3f	calc_rotate(sfVector3f *, sfVector3f, t_fig *, sfVector3f);
sfVector3f	set_pos(t_fig *, double, sfVector3f *, sfVector3f *);
sfVector3f	rotate_xyz(sfVector3f, sfVector3f);
sfVector3f	rotate_zyx(sfVector3f, sfVector3f);
sfVector3f	inv_rotate_zyx(sfVector3f, sfVector3f);
sfVector3f	inv_rotate_xyz(sfVector3f, sfVector3f);
sfVector3f	get_reflected_vector(sfVector3f, sfVector3f);
sfVector3f	get_refracted_vector(sfVector3f, sfVector3f, t_fig *);
sfColor		true_color(t_fig *, double, sfVector3f *, int);
double		get_k(t_fig *, sfVector3f *, sfVector3f *);
double		limit_object(t_fig *, double, double *, sfVector3f *);
float		intersect_sphere(sfVector3f, sfVector3f, t_fig *);
float		intersect_cone(sfVector3f, sfVector3f, t_fig *);
float		intersect_cylinder(sfVector3f, sfVector3f, t_fig *);
float		intersect_plane(sfVector3f, sfVector3f, t_fig *);
float		get_light_coef(sfVector3f, sfVector3f);
float		true_get_light_coef(sfVector3f, sfVector3f);
int		is_shadow(sfVector3f *, sfVector3f *, t_fig *);
int		is_int(char *);
int		nb_max(int, int);
int		has_pattern(sfVector3f *, t_fig *);
void		*raytrace(void *params);
void		colorize(sfColor *, float, sfColor *);
void		new_color(sfColor *, sfColor, t_fig *);
void		my_put_pixel_point(t_my_framebuffer *, int, int, sfColor);
void		set_color(sfColor *, int, int, int);
void		set_vector(sfVector3f *, float, float, float);
struct s_params	*cpy_params(struct s_my_framebuffer *frame,
			    struct s_fig *fig);
int		you_can_thread_those(struct s_my_framebuffer *frame,
				     struct s_fig *fig,
				     struct s_window *window,
				     char **argv);

#endif	/* !MY_H_ */
