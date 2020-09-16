/*
** set_reflection.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Sun May 28 10:33:23 2017 Lucas Dumy
** Last update Sun May 28 12:00:39 2017 Lucas Dumy
*/

#include	"parsing.h"

void		set_reflection(t_fig *node, float reflect,
			       float refract, float dens)
{
  if (reflect > 0.0f && reflect <= 1.0f)
    node->reflection = reflect;
  if (refract > 0.0f && refract <= 1.0f)
    node->refraction = refract;
  if (dens > 0 && dens <= 30)
    node->density = dens;
  if (reflect + refract > 1.0f)
    {
      node->reflection = 0.0f;
      node->refraction = 0.0f;
    }
}
