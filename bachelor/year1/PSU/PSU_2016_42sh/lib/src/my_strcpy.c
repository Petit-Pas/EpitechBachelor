/*
** my_strcpy.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:19:02 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:19:03 2017 Sahel Lucas--Saoudi
*/

char	*strcpy_(char *dest, char *src)
{
  int	i;

  i = 0;
  while (src[i])
    {
      dest[i] = src[i];
      i++;
    }
  return (dest);
}
