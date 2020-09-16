/*
** fcts_and_strcts.h for wireframe in /home/angevil124/prog/graphical/wireframe
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sun Dec  4 10:19:52 2016 benoit
** Last update Fri Dec  9 18:02:31 2016 benoit
*/


#ifndef FCTS_AND_STRCTS_H_
# define FCTS_AND_STRCTS_H_

#include "include.h"
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

int		fill_map(char *path, t_map *map);
int		try_open_file(char *filepath);
sfVector2i	my_parallel_projection(sfVector3f pos3d, float angle);
int		my_put_err(char *str);
void		my_put_pixel(t_frame_buffer *buffer, int x,
			     int y, sfColor color);
void		my_draw_line(t_frame_buffer *frame_buffer,
		     sfVector2i from, sfVector2i to, sfColor color);
int		my_draw_map(t_frame_buffer *buffer, int argc, char **av);

#endif /* !FCTS_AND_STRCTS_H_ */
