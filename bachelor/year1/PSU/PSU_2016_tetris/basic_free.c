/*
** basic_free.c for lib in /home/angevil124/lib
**
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
**
** Started on  Sun Jan 22 15:57:52 2017 benoit
** Last update Mon Mar 13 12:40:22 2017 Benoit
*/

#include <stdlib.h>
#include "tetris.h"

int	free_and_return(char *str, int to_r)
{
  free(str);
  return (to_r);
}

int	free_tab(char **tab, int return_value)
{
  int   i;

  i = 0;
  if (tab != NULL)
    {
      while (tab[i] != NULL)
        {
          free(tab[i]);
          i++;
        }
      free(tab);
    }
  return (return_value);
}

void		free_list_tetrimino(t_list *list)
{
  t_list	*tmp;
  t_list	*to_free;

  tmp = list;
  while (tmp)
    {
      to_free = tmp;
      tmp = tmp->next;
      free_tab(to_free->data.shape, 1);
      free(to_free->data.path);
      free(to_free->data.name);
      free(to_free);
    }
}

void	free_map(t_map *map)
{
  free_tab(map->map, 1);
  free(map);
}

void	free_all(t_list *list, t_map *map, t_option *option)
{
  free_list_tetrimino(list);
  free_map(map);
  free(option);
}
