/*
** parsing.h for raytracer2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Tue May 23 17:30:37 2017 Lucas Dumy
** Last update Sun May 28 17:16:13 2017 Lucas Dumy
*/

#ifndef		PARSING_H_
# define	PARSING_H_

# include	<SFML/System/Vector2.h>
# include	<SFML/System/Vector3.h>
# include	<SFML/Graphics/Color.h>

/*
** type 0 == eye
** type 1 == sphere
** type 2 == cylinder
** type 3 == cone
** type 4 == plane
** type 5 == light
*/

typedef struct	s_fig
{
  struct s_fig	*prev;
  struct s_fig	*next;
  int		id;
  int		type;
  sfVector3f	*pos;
  sfVector3f	*vect_dir;
  sfColor	color;
  int		pattern;
  double	radius;
  double	shine;
  int		min_height;
  int		max_height;
  float		reflection;
  float		refraction;
  float		density;
}		t_fig;

void		free_list(t_fig *);
void		get_cone(t_fig *, char **, int);
void		get_cylinder(t_fig *, char **, int);
void		get_eye(t_fig *, char **, int);
void		get_light(t_fig *, char **, int);
void		get_plane(t_fig *, char **, int);
void		get_sphere(t_fig *, char **, int);
void		get_tore(t_fig *, char **, int);
void		my_putnbr(int, int);
void		my_putstr(int, char *);
void		my_sentence(int, char *, int, char *);
void		set_reflection(t_fig *, float, float, float);
void		usage(char *);

int		adjust_value(char *, int, int);
int		check_args(int, char **);
int		my_getnbr(char *);
int		my_is_num(char *);
int		my_strcmp(char *, char *);
int		my_strlen(char *);

float		my_atof(char *);
float		my_getshine(char *);

char		*get_next_line(int);
char		*my_strdup(char *);

char		**my_str_to_wordtab(char *, int);

t_fig		*create_list(int);
t_fig		*fill_node(t_fig *, char *, int);
t_fig		*free_link(t_fig *, int);
t_fig		*node_malloc();
t_fig		*parsing(int, char **);

#endif		/* !PARSING_H_ */
