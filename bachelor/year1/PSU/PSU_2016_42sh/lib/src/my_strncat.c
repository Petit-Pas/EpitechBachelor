/*
** my_strncat.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:19:47 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:19:48 2017 Sahel Lucas--Saoudi
*/

char	*strncat_(char *dest, char *src, int nb)
{
  int	dest_len;
  int	i;

  i = 0;
  dest_len = 0;
  while (dest[dest_len] != '\0')
    dest_len++;
  while (i < nb && src[i] != '\0')
    {
      dest[dest_len + i] = src[i];
      i++;
    }
  dest[dest_len + i] = '\0';
  return (dest);
}
