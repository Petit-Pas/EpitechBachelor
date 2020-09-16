/*
** functions.h for my_sokoban in /home/angevil124/prog/PSU/PSU_2016_my_sokoban
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Dec 10 12:33:39 2016 benoit
** Last update Wed Dec 14 13:07:26 2016 benoit
*/

#ifndef FUNCTIONS_H_
# define FUNCTIONS_H_

#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct		s_player
{
  int			x;
  int			y;
  int			was_on_a_box;
}			t_player;

typedef struct		s_map
{
  int			col;
  int			row;
  int			amount_of_boxes;
  char			**map;
  char			**map_init;
}			t_map;

int	free_map(t_map *map, t_player *player, int result);
int	check_error(char **av);
int	my_put_err(char *str);
int	check_map(t_map *map, int x, int y, int boxes);
void	print_resize(t_map *map);
void	print_tab(t_map *map);
void	refresh_window(t_map *map);
int	check_loose(t_map *map);
int	print_help();
void	reset_map(t_map *map);
int	check_win(t_map *map);
void	get_key(t_map *map, int c, t_player *player);
int	my_strlen(char *str);
char	*my_strcpy(char *str);
int	create_window(t_map *map, t_player *player, int c);

#endif /* !FUNCTIONS_H_ */
