/*
** my_strcat.c for lib in /home/sahel/rendu/PSU/PSU_2016_minishell2/lib/src
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:18:39 2017 Sahel Lucas--Saoudi
** Last update Sat Apr  8 17:18:39 2017 Sahel Lucas--Saoudi
*/

char	*strcat_(char *dest, char *src)
{
  int	dest_len;
  int	i;

  i = 0;
  dest_len = 0;
  while (dest[dest_len] != '\0')
    dest_len++;
  while (src[i] != '\0')
    {
      dest[dest_len + i] = src[i];
      i++;
    }
  dest[dest_len + i] = '\0';
  return (dest);
}
