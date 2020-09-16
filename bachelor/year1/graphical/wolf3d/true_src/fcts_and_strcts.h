/*
** fcts_and_strcts.h for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Dec 17 12:36:51 2016 benoit
** Last update Sat Jan 14 10:17:00 2017 benoit
*/

#ifndef FCTS_AND_STRCTS_H_
# define FCTS_AND_STRCTS_H_

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Audio.h>

typedef struct		s_player
{
  sfVector2f		pos;
  float			direction;
  sfVector2f		stock;
  float			stock_angle;
}			t_player;

typedef struct		s_window
{
  sfRenderWindow	*window;
  sfVideoMode		mode;
  sfSprite		*sprite;
  sfTexture		*texture;
  sfMusic		*music;
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
  int			**solution;
  int			**path_found;
  int			row;
  int			column;
}			t_map;

sfColor		return_white();
int		show_solution(t_window *window, t_frame_buffer *buffer,
			      t_map *map, t_player *player);
void		get_size(t_map *map, int *size, t_frame_buffer *buffer);
void		draw_square(sfVector2i, int size, sfColor color,
			    t_frame_buffer *buffer);
int		**map_cpy(t_map *map, int x, int y);
void		put_path(t_map *map);
int		**prepare_solution(t_map *map);
int		check_env(char **env);
void		reset_teleportation(t_player *player);
int		is_on_end(t_map *map, t_player *player);
int		check_end(t_map *map, t_player *player);
void		display_window(t_window *window, t_frame_buffer *buffer);
void		show_map(t_window *window, t_frame_buffer *buffer,
			 t_map *map, t_player *player);
void		print_image(t_frame_buffer *buffer, t_map *map, t_player *player);
void		teleportation(t_frame_buffer *buffer,
			      t_map *map, t_player *player);
void            put_sky_and_ground(t_frame_buffer *buffer, sfVector2i to,
				   sfVector2i from, sfColor color);
int		check_in_map(t_map *map, float new_pos_y, float new_pos_x);
void		move_player_wall(t_map *map, t_player *player, int dir);
int		free_all(t_window *window, t_frame_buffer *buffer,
			 t_player *player, t_map *map);
t_frame_buffer	*create_pixel_buffer(int width, int height);
void		move_camera_right(t_frame_buffer *buffer,
				  t_map *map, t_player *player);
void		move_camera_left(t_frame_buffer *buffer,
				 t_map *map, t_player *player);
void		show_window(t_window *window, t_frame_buffer *buffer,
			    t_map *map, t_player *player);
void		move_player_backward(t_frame_buffer *buffer,
				     t_map *map, t_player *player);
void		move_player_forward(t_frame_buffer *buffer,
				    t_map *map, t_player *player);
float		raycast(sfVector2f pos, float direction, t_map *map,
			sfVector2i mapSize);
sfVector2f	move_forward(sfVector2f pos, float direction,
			     float distance, t_map *map);
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
void		my_putstr(char *str);

#endif /* !FCTS_AND_STRCTS_H_ */
