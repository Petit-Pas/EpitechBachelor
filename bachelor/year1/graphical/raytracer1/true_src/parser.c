/*
** parser.c for raytracer1 in /home/angevil124/prog/graphical/bsraytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sat Feb 25 11:58:11 2017 Benoit
** Last update Thu Mar 16 12:06:53 2017 Benoit
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "framebuffer.h"

int	check_validity_line(t_elements *to_check)
{
  if (to_check->type < 0 || to_check->type > 3)
    return (0);
  return (1);
}

void	add_list(t_elements *to_add, t_elements **list)
{
  to_add->next = *list;
  to_add->upward = to_add->radius;
  if (to_add->upward != 0)
    to_add->upward = 1;
  *list = to_add;
}

void	next_read_line_input(t_elements *result, int k, char *str)
{
  result->real_color.r = my_getnbr(&str[k]);
  go_to_next_semi(str, &k);
  result->real_color.g = my_getnbr(&str[k]);
  go_to_next_semi(str, &k);
  result->real_color.b = my_getnbr(&str[k]);
  go_to_next_semi(str, &k);
  result->real_color.a = my_getnbr(&str[k]);
  go_to_next_semi(str, &k);
  result->rotations.x = my_getnbr(&str[k]);
  go_to_next_semi(str, &k);
  result->rotations.y = my_getnbr(&str[k]);
  go_to_next_semi(str, &k);
  result->rotations.z = my_getnbr(&str[k]);
  go_to_next_semi(str, &k);
  result->radius = my_getnbr(&str[k]);
}

t_elements	*read_line_input(char *str)
{
  t_elements	*result;
  int		k;

  k = 0;
  if (!(result = malloc(sizeof(*result))))
    return (NULL);
  if (count_argument(str) != 11)
    return (NULL);
  result->type = my_getnbr(&str[k]);
  go_to_next_semi(str, &k);
  result->pos.x = my_getnbr(&str[k]);
  go_to_next_semi(str, &k);
  result->pos.y = my_getnbr(&str[k]);
  go_to_next_semi(str, &k);
  result->pos.z = my_getnbr(&str[k]);
  go_to_next_semi(str, &k);
  next_read_line_input(result, k, str);
  return (result);
}

t_elements	*init_parser(char *path)
{
  t_elements	*list;
  t_elements	*new_list;
  int	fd;
  char	*str;

  list = NULL;
  if ((fd = open(path, O_RDONLY)) <= 0)
    return (NULL);
  str = get_next_line(fd);
  while (str != NULL)
    {
      new_list = read_line_input(str);
      if (new_list != NULL)
	if (check_validity_line(new_list) == 1)
	  add_list(new_list, &list);
      str = get_next_line(fd);
    }
  return (list);
}
