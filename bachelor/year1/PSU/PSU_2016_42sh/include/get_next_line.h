/*
** get_next_line.h for get_next_line in /home/sahel/rendu/PSU/PSU_2016_minishell2
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Sat Apr  8 17:22:41 2017 Sahel Lucas--Saoudi
** Last update Thu Apr 27 14:24:07 2017 Sahel Lucas--Saoudi
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# ifndef READSIZE
#  define READSIZE 1
# endif /* !READSIZE */

typedef struct	buffer
{
  int		fd;
  char		*buffer;
  struct buffer	*next;
  struct buffer *previous;
}		t_buffer;

char	*getnextline_(int);
char	*concat_free(char *, char *);

#endif /* !GET_NEXT_LINE_H_ */
