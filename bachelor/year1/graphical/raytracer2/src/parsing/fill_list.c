/*
** fill_list.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Wed May 24 22:44:31 2017 Lucas Dumy
** Last update Fri May 26 15:28:29 2017 Lucas Dumy
*/

#include	<stdlib.h>
#include	"parsing.h"

static int	*create_object_array()
{
  int		*array;

  array = malloc(sizeof(int) * 8);
  if (array == NULL)
    return (NULL);
  array[0] = 0;
  array[1] = 1;
  array[2] = 2;
  array[3] = 3;
  array[4] = 4;
  array[5] = 5;
  array[6] = 6;
  array[7] = -2;
  return (array);
}

static void	create_object(void (**object)(t_fig *, char **, int))
{
  object[0] = &get_eye;
  object[1] = &get_sphere;
  object[2] = &get_cylinder;
  object[3] = &get_cone;
  object[4] = &get_plane;
  object[5] = &get_light;
}

t_fig		*fill_node(t_fig *node, char *buffer, int line)
{
  void		(*object[6])(t_fig *, char **, int);
  char		**tab;
  int		*object_array;
  int		i;

  i = 0;
  tab = my_str_to_wordtab(buffer, ',');
  object_array = create_object_array();
  if (tab == NULL || object_array == NULL)
    {
      my_putstr(2, "Malloc fail\n");
      return (NULL);
    }
  create_object(object);
  while (object_array[i] != -2 && object_array[i] != my_getnbr(tab[0]))
    i++;
  free(object_array);
  if (i == 6)
    {
      my_sentence(2, "Line ", line + 1, ": wrong object type.\n");
      return (NULL);
    }
  node->type = i;
  object[i](node, tab, line);
  return (node);
}
