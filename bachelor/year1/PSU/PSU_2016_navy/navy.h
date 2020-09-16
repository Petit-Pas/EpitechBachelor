/*
** navy.h for navy in /home/shintaro/Epitech/delivery/PSU_2016_navy
** 
** Made by Shintaro
** Login   <thomas.grandjean@epitech.eu>
** 
** Started on  Mon Jan 30 13:46:24 2017 Shintaro
** Last update Mon Feb 13 10:19:28 2017 Benoit
*/

#ifndef NAVY_H_
# define NAVY_H_

typedef struct	s_msg
{
  int		pid_host;
  int		pid_player;
  int		msg;
}		t_msg;

typedef struct  s_map
{
  char          **map_perso;
  char          **map_ennemy;
}               t_map;

t_msg	*g_msg;

int	free_all(char **morse, t_map *map);
void	change_boats(char **boat);
int	hit_manager(char *last);
int	attack_manager();
int	send_hit(int pid, int hit);
int	my_putchar(char c, int exit);
int	game_is_over(t_map *map);
void	change_coordinates(char *str, int start);
void	purify_boats(char **boat);
char	*free_and_return(char *to_free, char *to_return);
void	put_shot_enemy(char x, char y, t_map *map, int hit);
char	*translate_morse(char **morse, int i, int j);
int	check_hit(char x, char y, t_map *map);
void	put_shot_perso(char x, char y, t_map *map);
void	print_maps(t_map *map);
int	send_morse(int x, int y, int pid, char **morse);
int	fill_morse(char **morse);
int     check_boats(char **boat);
int     init_map(char **map);
int     is_in_map(char *boat);
int	free_tab(char **tab, int to_return);
int     my_putstr(char *str, int exit, int to_return);
int     my_strlen(char *str);
int     fill_map(t_map *map, char *path);
char    *my_strcpy(char *str);
char    *get_next_line(int fd);
int     my_strcmp(char *str, char *str2);
int     my_putnbr_base(int nb, char *base, int exit, int to_return);
int	my_get_nbr(char *str);
int	connexion_manager(int sig, int player, t_map *map);
int	print_help();
void	print_pid(int pid);

#endif /* !NAVY_H_ */
