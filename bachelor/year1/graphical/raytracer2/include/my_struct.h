/*
** my.h for raytracer2 in /home/bastilol/delivery/maths/104intersection
**
** Made by bastien BEDU
** Login   <bastilol@epitech.net>
**
** Started on  Thu Dec 22 15:42:46 2016 bastien BEDU
** Last update Sat May 27 07:37:12 2017 Benoit Hoffman
*/

#ifndef	MY_STRUCT_H_
# define MY_STRUCT_H_

# include	<SFML/System/Vector2.h>
# include	<SFML/System/Vector3.h>
# include	<SFML/Graphics/Color.h>
# include	"graph.h"
# include	"parsing.h"

typedef struct		s_window
{
  sfTexture		*texture;
  sfRenderWindow	*window;
  sfSprite		*sprite;
}			t_window;

typedef struct		s_params
{
  t_fig			*fig;
  t_my_framebuffer	*frame;
  int			step;
  sfVector2i		from;
  int			skip;
}			t_params;

#endif	/* !MY_STRUCT_H_ */
