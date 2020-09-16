/*
** main.c for tetris in /home/shintaro/Work/Epitech/delivery/PSU_2016_tetris/finished
**
** Made by shintaro
** Login   <thomas.grandjean@epitech.eu>
**
** Started on  Wed Feb 22 10:39:26 2017 shintarogr
** Last update Thu Mar 16 10:22:25 2017 shintarogr
*/

#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "tetris.h"

void	init_game(t_option *option, t_map *map)
{
  initscr();
  noecho();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  start_color();
  init_pair(48, COLOR_BLACK, COLOR_BLACK);
  init_pair(48 + 1, COLOR_RED, COLOR_BLACK);
  init_pair(48 + 2, COLOR_GREEN, COLOR_BLACK);
  init_pair(48 + 3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(48 + 4, COLOR_BLUE, COLOR_BLACK);
  init_pair(48 + 5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(48 + 6, COLOR_CYAN, COLOR_BLACK);
  init_pair(48 + 7, COLOR_WHITE, COLOR_BLACK);
  srand(time(NULL));
  map->size_max = option->map_size;
  map->map = create_map(map->size_max);
  map->level = option->level;
  if (map->level > 20)
    map->level = 20;
  map->score = 0;
  map->init_time = time(NULL);
  map->hidden = option->without_next;
  map->max_score = 0;
}

int		find_new_falling_piece(t_list *tetriminos,
				       t_piece_falling *piece,
				       t_map *map, int mode)
{
  int		i;
  t_list	*temp;

  temp = tetriminos;
  i = rand() % tetriminos->data.amount_tetrimino;
  while (i > 0)
    {
      temp = temp->next;
      i--;
    }
  if (temp->data.error == 1)
    return (find_new_falling_piece(tetriminos, piece, map, mode));
  else
    {
      if (mode == 1)
	return (fill_tab_shape(temp, piece, map));
      else
	return (create_first_tab_shape(temp, piece, map, 0));
    }
}

int		main(int ac, char **av, char **env)
{
  t_option	*opt;
  DIR		*directory;
  t_list	*tetriminos;
  t_map		*map;
  int		return_value;

  if (check_before_the_beginning(av) == 1)
    return (0);
  if ((opt = malloc(sizeof(*opt))) == NULL || !(map = malloc(sizeof(*map))))
    return (my_putstr("Malloc error\n", 2, 84));
  if (!(directory = opendir("./tetriminos/")))
    return (print_help(84, 1, av[0]));
  if (init_term(env) == 84 || check_validity(av) == 84 ||
      argument_parser(ac, av, opt) == 84)
    return (print_help(84, 0, av[0]));
  tetriminos = start_main_list(directory);
  fill_amount(tetriminos);
  try_popsort(tetriminos);
  if (check_debug_help(opt, tetriminos) == 1)
    return (0);
  init_game(opt, map);
  return_value = game_loop(map, tetriminos, opt);
  endwin();
  free_all(tetriminos, map, opt);
  return (return_value);
}
