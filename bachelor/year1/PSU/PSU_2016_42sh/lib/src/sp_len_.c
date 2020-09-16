/*
** sp_len_.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:20:45 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:20:53 2017 Sahel Lucas--Saoudi
*/

int	sp_len_(char *str, char c)
{
  int	str_i;

  str_i = 0;
  while (str && str[str_i] && str[str_i] != c)
    str_i++;
  return (str_i);
}
