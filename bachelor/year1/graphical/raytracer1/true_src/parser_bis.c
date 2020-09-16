/*
** parser_bis.c for raytracer1 in /home/angevil124/prog/graphical/bsraytracer1/src
** 
** Made by Benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Sun Feb 26 09:02:18 2017 Benoit
** Last update Tue Mar  7 14:16:54 2017 Benoit
*/

int     count_argument(char *str)
{
  int   i;
  int   semi;

  i = 0;
  semi = 0;
  if (str[0] == ':')
    return (- 1);
  while (str[i] != '\0')
    {
      if (str[i] == ':')
        {
          semi++;
          if (str[i + 1] == ':' || str[i + 1] == '\0')
            return (- 1);
        }
      i++;
    }
  return (semi);
}

void    go_to_next_semi(char *str, int *k)
{
  while (str[*k] != ':')
    {
      *k += 1;
    }
  *k += 1;
}
