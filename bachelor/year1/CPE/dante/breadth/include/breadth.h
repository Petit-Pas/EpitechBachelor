/*
** solver.h for dante in /home/angevil124/prog/CPE/dante/depth_first
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Apr 27 08:39:00 2017 Benoit Hoffman
** Last update Tue May  9 08:33:31 2017 Benoit Hoffman
*/

#ifndef		SOLVER_H_
# define	SOLVER_H_

typedef struct  s_list
{
  int		x;
  int		y;
  struct s_list *next;
}		t_list;

typedef	struct	s_map
{
  char		**map;
  int		**skeletton;
  int		x;
  int		y;
}		t_map;

int		put_new_list(t_list **new, t_list *old, t_map *map, int id);
int		print_solution(t_map *map);
int		add_list(t_list **list, int x, int y);
int		check_up(t_map *map, t_list *list, int id);
int		check_down(t_map *map, t_list *list, int id);
int		check_left(t_map *map, t_list *list, int id);
int		check_right(t_map *map, t_list *list, int id);
int		add_up(t_map *map, t_list **list, int id);
int		add_down(t_map *map, t_list **list, int id);
int		add_left(t_map *map, t_list **list, int id);
int		add_right(t_map *map, t_list **list, int id);
int		add_up_breadth(t_map *map, t_list *list, int id, t_list **new);
int		add_down_breadth(t_map *map, t_list *list, int id, t_list **new);
int		add_left_breadth(t_map *map, t_list *list, int id, t_list **new);
int		add_right_breadth(t_map *map, t_list *list, int id, t_list **new);
int		resolve(t_map *map);
int		my_putstr(char *str, int exit, int return_value);
int		get_map(char *str, t_map *map, int fd);
int		create_int_map(t_map *map);
int		my_strlen(char *str);
char		*my_strcat(char *str1, char *str2, int to_free1, int to_free2);
char		*get_next_line(int fd);

#endif		/* !SOLVER_H_ */
