/*
** generator.h for dante in /home/angevil124/prog/CPE/dante
**
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Tue Apr 11 12:29:01 2017 Benoit Hoffman
** Last update Wed May  3 12:36:56 2017 Benoit Hoffman
*/

#ifndef		GENERATOR_H_
# define	GENERATOR_H_

typedef	struct		s_coords
{
  int			x;
  int			y;
}			t_coords;

typedef	struct		s_stack
{
  t_coords		coords;
  struct s_stack	*next;
}			t_stack;

void			check_walls(t_coords vertical, t_coords coords,
                                    t_coords horizontal, t_coords walls[3]);
void		       	do_unperfect(char **map);
void			free_stack(t_stack **list);
int			add_stacks(t_coords walls[3], t_stack **list);
int			my_get_nbr(char *str);
int			my_strlen(char *str);
int			my_putstr(char *str, int exit, int to_return);
int			my_strcmp(char *str1, char *str2);
int			break_down_the_walls(char **map, t_coords coords);
void			my_put_lab(char **map, int x, int y);
void			randomize_me(t_coords walls[3]);
void			find_walls(char **map, t_coords coords,
				       t_coords *vertical,
				       t_coords *horizontal);

#endif		/* !GENERATOR_H_ */
