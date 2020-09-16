/*
** main.c for dante in /home/angevil124/prog/CPE/dante/depth_first
** 
** Made by Benoit Hoffman
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Thu Apr 27 07:27:44 2017 Benoit Hoffman
** Last update Tue May  9 08:33:45 2017 Benoit Hoffman
*/

#include	"astar.h"

int	main(int ac, char **av)
{
  t_map map;

  if (ac != 2)
    return (my_putstr("no input file\n", 2, 84));
  if (get_map(av[1], &map, 0) == 84)
    return (84);
  if (create_int_map(&map) == 84)
    return (my_putstr("malloc error\n", 2, 84));
  map.y = map.y - 1;
  map.x = map.x - 2;
  if (map.map[0][0] != '*' || map.map[map.y][map.x] != '*')
    return (my_putstr("no start or end\n", 2, 84));
  if (resolve(&map) == 84)
    return (my_putstr("malloc error\n", 2, 84));
  if (print_solution(&map) == 84)
    return (my_putstr("no path found\n", 2, 84));
  return (0);
}
