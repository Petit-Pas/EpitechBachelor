/*
** fcts_and_strcts.h for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Dec 17 12:36:51 2016 benoit
** Last update Wed Dec 21 13:08:22 2016 benoit
*/

#ifndef FCTS_AND_STRCTS_H_
# define FCTS_AND_STRCTS_H_

#include "include.h"

typedef struct		s_player
{
  sfVector2f		pos;
  float			direction;
}			t_player;

typedef struct		s_window
{
  sfRenderWindow	*window;
  sfVideoMode		mode;
  sfSprite		*sprite;
  sfTexture		*texture;
}			t_window;

typedef struct          s_frame_buf
{
  sfUint8		*pixels;
  int			width;
  int			height;
}			t_frame_buffer;

typedef struct		s_map
{
  int			**map;
  int			row;
  int			column;
}			t_map;

t_frame_buffer	*create_pixel_buffer(int width, int height);
void		move_camera_right(t_window *window, t_frame_buffer *buffer,
				  t_map *map, t_player *player);
void		move_camera_left(t_window *window, t_frame_buffer *buffer,
				 t_map *map, t_player *player);
void		show_window(t_window *window, t_frame_buffer *buffer,
			    t_map *map, t_player *player);
void		move_player_backward(t_window *window, t_frame_buffer *buffer,
				     t_map *map, t_player *player);
void		move_player_forward(t_window *window, t_frame_buffer *buffer,
				    t_map *map, t_player *player);
float		raycast(sfVector2f pos, float direction, int **map,
			sfVector2i mapSize);
sfVector2f	move_forward(sfVector2f pos, float direction,
			     float distance);
void		print_image(t_frame_buffer *buffer, t_map *map,
			    t_player *player);
int		fill_player(t_map *map, t_player *player);
int		fill_tab(int ac, char **av, t_map *map);
int		fill_map(char *path, t_map *map);
int		try_open_file(char *filepath);
int		my_put_err(char *str);
void		my_put_pixel(t_frame_buffer *buffer, int x,
			     int y, sfColor color);
void		my_draw_line(t_frame_buffer *frame_buffer,
		     sfVector2i from, sfVector2i to, sfColor color);
int		my_check_map(t_frame_buffer *buffer, int argc,
			     char **av, t_map *map);

#endif /* !FCTS_AND_STRCTS_H_ */
