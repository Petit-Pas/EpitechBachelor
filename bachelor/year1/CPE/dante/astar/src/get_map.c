/*
** get_map.c for dante in /home/angevil124/prog/CPE/dante/depth_first
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Apr 27 07:31:26 2017 Benoit Hoffman
** Last update Tue May  9 08:31:45 2017 Benoit Hoffman
*/

#include	<fcntl.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"astar.h"

static void	copy_in_skeletton(int *str, char *str2)
{
  int		x;

  x = 0;
  while (str2[x] != '\0')
    {
      if (str2[x] == '*')
	str[x] = 2000000000;
      else if (str2[x] == 'X')
	str[x] = -1;
      x += 1;
    }
}

int		create_int_map(t_map *map)
{
  int		y;

  y = 0;
  map->skeletton = malloc(sizeof(int *) * (map->y + 1));
  if (map->skeletton == NULL)
    return (84);
  while (map->map[y] != NULL)
    {
      map->skeletton[y] = malloc(sizeof(int) * (map->x));
      if (map->skeletton[y] == NULL)
	return (84);
      copy_in_skeletton(map->skeletton[y], map->map[y]);
      y += 1;
    }
  map->skeletton[y] = NULL;
  return (0);
}

static int	get_size(char *path)
{
  struct stat	buff;

  if (stat(path, &buff) == 1)
    return (-1);
  return (buff.st_size);
}

int		get_middle_map(t_map *map, int fd)
{
  int		i;

  i = 1;
  while (i < map->y)
    {
      map->map[i] = malloc(sizeof(char) * (map->x + 1));
      if (map->map[i] == NULL)
	return (my_putstr("Malloc error\n", 2, 84));
      map->map[i][read(fd, map->map[i], (size_t)map->x)] = '\0';
      i += 1;
    }
  map->map[i] = NULL;
  return (0);
}

int		get_map(char *path, t_map *map, int fd)
{
  int		size_file;
  char		*buffer;

  size_file = get_size(path);
  if (size_file < 0)
    return (my_putstr("Couldn't open the file.\n", 2, 84));
  fd = open(path, O_RDONLY);
  if (fd < 0)
    return (my_putstr("Couldn't open the file.\n", 2, 84));
  buffer = get_next_line(fd);
  map->x = my_strlen(buffer);
  if (map->x == 0)
    return (my_putstr("Invalid map\n", 2, 84));
  map->y = (size_file + 1) / map->x;
  map->map = malloc(sizeof(char *) * (map->y + 1));
  if (map->map == NULL)
    return (my_putstr("Malloc error\n", 2, 84));
  map->map[0] = buffer;
  return (get_middle_map(map, fd));
}
