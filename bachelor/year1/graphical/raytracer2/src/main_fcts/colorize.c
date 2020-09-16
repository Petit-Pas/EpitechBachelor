/*
** colorize.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Sun May 28 14:12:03 2017 Lucas Dumy
** Last update Sun May 28 15:22:30 2017 Lucas Dumy
*/

#include	"my.h"

void		new_color(sfColor *color, sfColor new, t_fig *fig)
{
  set_color(color, color->r * (1.0f - fig->reflection - fig->refraction),
	    color->g * (1.0f - fig->reflection - fig->refraction),
	    color->b * (1.0f - fig->reflection - fig->refraction));
  set_color(color, color->r + new.r, color->g + new.g, color->b + new.b);
}

void		colorize(sfColor *new, float ref, sfColor *color)
{
  set_color(new, new->r * ref, new->g * ref, new->b * ref);
  set_color(color, color->r + new->r, color->g + new->g, color->b + new->b);
}
