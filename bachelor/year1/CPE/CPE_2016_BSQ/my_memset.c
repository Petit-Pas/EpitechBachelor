/*
** my_memset.c for bsq in /home/angevil124/prog/CPE/CPE_2016_BSQ
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Tue Dec  6 13:18:31 2016 benoit
** Last update Tue Dec  6 13:22:15 2016 benoit
*/

void	my_memset(char *str, char c, int size)
{
  int	i;

  i = 0;
  while (i != size)
    {
      str[i] = c;
      i++;
    }
}
