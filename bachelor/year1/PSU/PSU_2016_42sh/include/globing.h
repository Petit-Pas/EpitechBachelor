/*
** globing.h for PSU_2016_42sh in /home/sahel/rendu/PSU/PSU_2016_42sh
**
** Made by Sahel Lucas--Saoudi
** Login   <sahel.lucas-saoudi@epitech.eu>
**
** Started on  Wed May 10 11:44:32 2017 Sahel Lucas--Saoudi
** Last update Sat May 20 10:49:25 2017 Sahel Lucas--Saoudi
*/

#ifndef			GLOBING_H_
# define		GLOBING_H_

# include		"main.h"

typedef struct		s_globing
{
  char			*new_command;
  char			*var;
  char			*varname;
  char			ret_value[10];
}			t_globing;

int			init_globing(char *, t_globing *, int *, int *);
void			modif_command_globing(t_globing *, int *, char *,
					      int *);
char			*globing(char *, t_shell *);
char			*file_globing(char *);

#endif			/* !GLOBING_H_ */
