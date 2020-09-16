/*
** tetris.h for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris/thomas
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Mon Feb 20 16:55:06 2017 shintaro
** Last update Thu Mar 16 09:02:01 2017 Benoit
*/

#ifndef TETRIS_H_
# define TETRIS_H_

#include <sys/types.h>
#include <dirent.h>

typedef struct	s_size
{
  int		row;
  int		col;
}		t_size;

typedef struct	s_option
{
  int		level;
  char		*left_key;
  char		*right_key;
  char		*turn_key;
  char		*drop_key;
  char		*quit_key;
  char		*pause_key;
  t_size	map_size;
  int		without_next;
  int		debug;
  int		help;
  int		error;
}		t_option;

typedef struct	s_map
{
  char		**map;
  int		hidden;
  int		score;
  int		level;
  int		max_score;
  int		lines_left;
  int		init_time;
  t_size	size_max;
}		t_map;

typedef struct		s_piece_falling
{
  unsigned char		*coords;
  int			center_x;
  int			center_y;
  char			color;
  unsigned char		*coords_next;
  int			center_x_next;
  int			center_y_next;
  char			color_next;
  int			max_x;
  int			max_y;
  int			longest_x_next;
  int			longest_x;
}			t_piece_falling;

typedef	struct		s_tetrimino
{
  char			*path;
  char			*name;
  int			error;
  int			amount;
  int			amount_tetrimino;
  int			max_x_found;
  int			size_x;
  int			size_y;
  int			color;
  char			**shape;
}			t_tetrimino;

typedef struct		s_list
{
  t_tetrimino		data;
  struct s_list		*next;
}			t_list;

int	check_game_can_be_launched(t_list *tetriminos);
int	free_and_return(char *str, int to_r);
void	print_level(t_map *map);
int	find_new_falling_piece(t_list *tetriminos,
			       t_piece_falling *piece,
			       t_map *map, int mode);
int	game_loop(t_map *map, t_list *tetriminos,
		  t_option *option);
void	get_lines(t_map *map);
void	free_all(t_list *list, t_map *map, t_option *option);
int     create_first_tab_shape(t_list *to_copy,
			       t_piece_falling *to_fill, t_map *map, int i);
int	fill_tab_shape(t_list *new_one, t_piece_falling *to_fill, t_map *map);
int	put_center_coordinates_first(t_list *to_copy,
				     t_piece_falling *to_fill, t_map *map);
int	check_tetrimino_validity(t_list *list);
int	check_if_not_too_big(t_list *list, t_map *map, t_piece_falling *piece);
void    print_piece(t_piece_falling *piece, t_map *map, int i);
void	go_as_down_as_possible(t_piece_falling *piece, t_map *map);
void	validate_piece(t_piece_falling *piece, t_map *map);
void	manage_rotate(t_piece_falling *piece, t_map *map);
int     manage_basic_moves(t_piece_falling *piece, t_map *map, int x, int y);
void	print_game(t_map *map, int x, int y);
char	**create_map(t_size size);
void	popsort(t_list *list, int done, int max);
void	try_popsort(t_list *list);
int	create_tab_shape(t_list *elem,
			 t_piece_falling *to_fill, t_map *map, int i);
void	fill_amount(t_list *list);
int	my_putchar(char c, int exit);
int	put_shape_in_elem(t_list *element, int fd);
int	fill_data(char *str, t_list *elem, int i, int amount);
void	print_debug(t_list *list, t_option *option);
int	my_putstr(char *str, int exit, int to_return);
int	my_putnbr_base(int nb, char *base, int exit, int to_return);
int	my_get_nbr(char *str);
char	*get_next_line(int fd);
int	my_strlen(char *str);
char	*my_strcat(char *str, char *str2, int free, int free2);
char	*my_strcpy(char *str);
int	argument_parser(int ac, char **av, t_option *option);
int   	match(char *str, char *str2);
int	my_strcmp(char *str, char *str2);
int    	my_get_nbr(char *str);
int	is_numeric(char *str);
int	check_flags_quit(char *av, char *av2, t_option *option);
int	check_flags_pause(char *av, char *av2, t_option *option);
int	check_flags_without_next(char *av, char *av2, t_option *option);
int	check_flags_debug(char *av, char *av2, t_option *option);
int	check_flags_help(char *av, char *av2, t_option *option);
int	check_flags_level(char *av, char *av2, t_option *option);
int	check_flags_left(char *av, char *av2, t_option *option);
int	check_flags_right(char *av, char *av2, t_option *option);
int	check_flags_turn(char *av, char *av2, t_option *option);
int	check_flags_drop(char *av, char *av2, t_option *option);
int	check_flags(int ac, char **av, t_option *option);
int	init_term(char **env);
int	print_help(int to_r, int error, char *str);
t_list	*start_main_list(DIR *dir);
char	*my_strcpy(char *str);
void	print_key(t_option *option);
int	check_validity(char **av);
int	check_debug_help(t_option *option, t_list *tetrimino);
void	print_unprintable(char *str);
int	check_double(t_option *option);
int	match_s(char *s1, char *s2);
int	check_input(t_option *option, t_map *map, t_piece_falling *piece);
void	manage_falling(t_piece_falling *piece, t_map *map, int *i);
void	check_remove_lines(t_map *map);
int	check_basic_moves(t_piece_falling *piece, t_map *map, int x, int y);
char	*remove_last_spaces(char *str);
void	free_list_tetrimino(t_list *list);
int	check_before_the_beginning(char **av);
int	my_resize_term(t_map *map, t_piece_falling *piece, t_option *option);

#endif /* TETRIS_H_ */
