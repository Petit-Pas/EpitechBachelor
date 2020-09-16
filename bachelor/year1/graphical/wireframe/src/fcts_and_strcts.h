/*
** fcts_and_strcts.h for wireframe in /home/angevil124/prog/graphical/wireframe
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sun Dec  4 10:19:52 2016 benoit
** Last update Thu Dec  8 11:13:44 2016 benoit
*/


#ifndef FCTS_AND_STRCTS_H_
# define FCTS_AND_STRCTS_H_

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>

typedef struct          s_frame_buf
{
  sfUint8		*pixels;
  int			width;
  int			height;
}			t_frame_buffer;

int	my_put_err(char *str);
void	my_put_pixel(t_frame_buffer *buffer, int x, int y, sfColor color);
void    my_draw_line(t_frame_buffer *frame_buffer,
		     sfVector2i from, sfVector2i to, sfColor color);

#endif /* !FCTS_AND_STRCTS_H_ */
