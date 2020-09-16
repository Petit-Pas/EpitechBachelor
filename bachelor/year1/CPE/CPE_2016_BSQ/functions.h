/*
** functions.h for wireframe in /home/angevil124/prog/CPE/CPE_2016_BSQ
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Mon Dec  5 10:15:18 2016 benoit
** Last update Tue Dec  6 15:31:09 2016 benoit
*/

#ifndef FUNCTIONS_H_
# define FUNCTIONS_H_

#include "structs.h"

void	free_tab(char **tab, int nb);
void	free_map(t_map *map);
void	print_map(t_map *map, char c);
void	replace(t_map *map);
void	my_memset(char *str, char c, int nb);
int	find_biggest(t_map *map, int x, int y);
char	*get_first_char(char *str);
void    fill(char *path, int amount_lines, t_map *map);
int	my_put_err(char *str);
int	try_open_file(char *str);
int	fs_get_number_from_first_line(char *path);
int	check_error(int ac, char **av);

#endif /* !FUNCTIONS_H_ */
