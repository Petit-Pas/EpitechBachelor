/*
** history.h for PSU_2016_42sh in /home/sahel/rendu/PSU/PSU_2016_42sh
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Fri May 12 14:52:55 2017 Sahel Lucas--Saoudi
** Last update Fri May 12 14:52:55 2017 Sahel Lucas--Saoudi
*/

#ifndef HISTORY_H_
# define HISTORY_H_

# ifndef HISTORY_FILE
#  define HISTORY_FILE ".42shhistory"
# endif /* !HISTORY_FILE */

char	*history(char *, t_shell *, int);
int	call_history(char **, t_shell *);
int	add_to_history(char *, t_shell *);

#endif /* !HISTORY_H_ */
