/*
** main.c for my_sokoban in /home/angevil124/prog/PSU/PSU_2016_my_sokoban
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Dec 13 10:32:39 2016 benoit
** Last update Thu Dec 15 14:56:35 2016 benoit
*/

#include "functions.h"

char		**get_map(char *path, t_map *map)
{
  FILE		*stream;
  char		*line;
  size_t	len;
  int		count;
  char		**tab;

  len = 0;
  line = NULL;
  count = 0;
  stream = fopen(path, "r");
  while ((getline(&line, &len, stream)) != - 1)
    count++;
  tab = malloc(sizeof(char*) * count);
  map->row = count;
  count = 0;
  fclose(stream);
  stream = fopen(path, "r");
  while ((getline(&line, &len, stream)) != - 1)
    {
      tab[count] = my_strcpy(line);
      count++;
    }
  free(line);
  return (tab);
}

int	main(int ac, char **av)
{
  t_map		*map;
  t_player	*player;

  if (ac != 2)
    return (84);
  if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0')
    return (print_help());
  if (check_error(av) == 84)
    return (84);
  map = malloc(sizeof(*map));
  player = malloc(sizeof(*player));
  map->map = get_map(av[1], map);
  map->map_init = get_map(av[1], map);
  if (check_map(map, 0, 0, 0) == 84)
    return (my_put_err("invalid map\n"));
  return (create_window(map, player, 0));
}
