/*
** check_env.c for wolf3d in /home/angevil124/prog/graphical/wolf3d
** 
** Made by benoit
** Login   <benoit.hoffman@epitech.eu>
** 
** Started on  Fri Jan  6 16:36:47 2017 benoit
** Last update Mon Mar 13 08:25:41 2017 Benoit
*/

#include "framebuffer.h"

int     check_reverse(char *s1, char *s2)
{
  int   max_2;
  int   max_1;

  max_2 = 0;
  max_1 = 0;
  while (s1[max_1])
    max_1++;
  while (s2[max_2] != '\0')
    max_2++;
  max_1--;
  max_2--;
  while (s2[max_2] != '*')
    {
      if (s2[max_2] != s1[max_1])
          return (0);
      max_1--;
      max_2--;
    }
  return (1);
}

int     match(char *s1, char *s2)
{
  int   i;

  i = 0;
  if (s1 == NULL || s2 == NULL)
    return (0);
  while (s2[i] != '\0' && s1[i] != '\0' && s2[i] != '*')
    {
      if (s1[i] != s2[i])
        return (0);
      i++;
    }
  if (s1[i] == '\0' && s2[i] == '\0')
    return (1);
  else if (s2[i] == '*')
    return (check_reverse(s1, s2));
  return (0);
}

int	check_env(char **env)
{
	// not necessary anymore, bypassing it
	return 0;
  int	i;
  int	runtime;
  int	path;
  int	cpath;
  int	display;

  i = - 1;
  runtime = 0;
  path = 0;
  cpath = 0;
  display = 0;
  while (env[++i] != NULL)
    {
      if (match(env[i], "XDG_RUNTIME_DIR*"))
	runtime++;
      else if (match(env[i], "LIBRARY_PATH**"))
	path++;
      else if (match(env[i], "CPATH*"))
	cpath++;
      else if (match(env[i], "DISPLAY*"))
	display++;
    }
  if (runtime == 0 || path == 0 || cpath == 0 || display == 0)
    return (84);
  return (0);
}
