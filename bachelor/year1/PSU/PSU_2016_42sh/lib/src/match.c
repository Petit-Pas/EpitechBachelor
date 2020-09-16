/*
** match.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:17:13 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:17:13 2017 Sahel Lucas--Saoudi
*/

int	match(char *s1, char *s2)
{
  if (*s2 == '*')
    return ((*s1 == '\0') ? (match(s1, s2 + 1)) :
	    (match(s1 + 1, s2) || match(s1, s2 + 1)));
  if (*s1 == *s2)
    return ((*s1 == '\0') ? (1) : (match(s1 + 1, s2 + 1)));
  return (0);
}
