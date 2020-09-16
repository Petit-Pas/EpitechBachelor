/*
** alias.h for PSU_2016_42sh in /home/sahel/rendu/PSU/PSU_2016_42sh
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed May 10 15:49:27 2017 Sahel Lucas--Saoudi
** Last update Thu May 11 11:37:58 2017 Sahel Lucas--Saoudi
*/

#ifndef ALIAS_H_
# define ALIAS_H_

# ifndef ALIAS_FILE
#  define ALIAS_FILE ".42shrc"
# endif /* !ALIAS_FILE */

int	source(char **, t_shell *);
char	**alias(char **, t_shell *);
int	call_alias(char **, t_shell *);

#endif /* !ALIAS_H_ */
