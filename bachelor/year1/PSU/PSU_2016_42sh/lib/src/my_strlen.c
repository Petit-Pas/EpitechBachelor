/*
** my_strlen.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:19:35 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:19:35 2017 Sahel Lucas--Saoudi
*/

int	strlen_(char *str)
{
  int	i;

  i = 0;
  while (str && str[i])
    i++;
  return (i);
}
