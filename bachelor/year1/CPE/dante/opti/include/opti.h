/*
** depth.h for dante in /home/shintaro/Work/Epitech/delivery/dante
**
** Made by Thomas GRANDJEAN
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Sat May 13 13:13:18 2017 Thomas GRANDJEAN
** Last update Sat May 13 13:13:18 2017 Thomas GRANDJEAN
*/

#ifndef		OPTI_H_
# define	OPTI_H_

typedef	struct	s_map
{
  char		**map;
  int		**skeletton;
  int		x;
  int		y;
}		t_map;

int		print_solution(t_map *map);
int		resolve(t_map *map);
int		resolve_depth(t_map *map, int id);
int		my_putstr(char *str, int exit, int return_value);
int		get_map(char *str, t_map *map, int fd);
int		create_int_map(t_map *map);
int		my_strlen(char *str);
char		*my_strcat(char *str1, char *str2, int to_free1, int to_free2);
char		*get_next_line(int fd);

#endif		/* !OPTI_H_ */
