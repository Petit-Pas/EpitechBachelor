/*
** cerate_map.c for tetris in /home/angevil124/prog/PSU/PSU_2016_tetris/benoit
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Wed Feb 22 07:43:16 2017 Benoit
** Last update Tue Feb 28 10:25:57 2017 Benoit
*/

#include <stdlib.h>
#include "tetris.h"

void	put_border(char **map)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (map[0][i] != '\0')
    {
      map[0][i] = '#';
      i++;
    }
  i = 0;
  while (map[i] != NULL)
    i++;
  i--;
  while (map[i][j] != '\0')
    {
      map[i][j] = '#';
      j++;
    }
}

void	fill_map(char **map, t_size size)
{
  int	i;
  int	j;

  i = 0;
  while (map[i] != NULL)
    {
      j = 1;
      map[i][0] = '#';
      while (j <= size.col)
	{
	  map[i][j] = ' ';
	  j++;
	}
      map[i][j] = '#';
      map[i][j + 1] = '\0';
      i++;
    }
  put_border(map);
}

char	**create_map(t_size size)
{
  char	**map;
  int	i;

  i = 0;
  if (!(map = malloc(sizeof(char *) * (size.row + 3))))
    return (NULL);
  while (i != size.row + 2)
    {
      if (!(map[i] = malloc(sizeof(char) * (size.col + 3))))
	return (NULL);
      i++;
    }
  map[i] = NULL;
  fill_map(map, size);
  return (map);
}
