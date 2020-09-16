/*
** usage.c for RTV2 in /home/Lucas/delivery/MUL/raytracer2/Lucas
**
** Made by Lucas Dumy
** Login   <lucas.dumy@epitech.eu>
**
** Started on  Wed May 24 20:47:01 2017 Lucas Dumy
** Last update Sun May 28 11:58:30 2017 Lucas Dumy
*/

#include	"parsing.h"

void            usage(char *bin)
{
  my_putstr(1, "USAGE:\n\t");
  my_putstr(1, bin);
  my_putstr(1, " file.csv [-t nb] [-h]\n\nDESCRIPTION:\n\tfile.csv"
	    "\ta .csv file whose lines correspond to the following pattern:\n"
	    "\ttype,pos_x,pos_y,pos_z,rot_x,rot_y,rot_z,col_r,col_g,col_b,"
	    "var_1,var_2,shine,min_height,max_height"
	    ",reflection,refraction,density\n"
	    "\tnb\t\tthe amount of threads you want to use "
	    "(default: 50, max: 100)\n\n\t"
	    "use man -l raytracer2.1.gz for more information.\n");
}
