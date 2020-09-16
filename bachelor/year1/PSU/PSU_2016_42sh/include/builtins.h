/*
** builtins.h for PSU_2016_42sh in /home/sahel/rendu/PSU/PSU_2016_42sh
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed May 10 15:29:48 2017 Sahel Lucas--Saoudi
** Last update Mon May 15 13:00:00 2017 Benoit Hoffman
*/

#ifndef BUILTINS_H_
# define BUILTINS_H_

int	call_repeat(char **, t_shell *);
int	call_where(char **, t_shell *);
int	call_which(char **, t_shell *);
int	call_echo(char **, t_shell *);
int	call_cd(char **, t_shell *);
int	call_env(char **, t_shell *);
int	call_setenv(char **, t_shell *);
int	call_unsetenv(char **, t_shell *);
int	call_exit(char **, t_shell *);

#endif /* !BUILTINS_H_ */
