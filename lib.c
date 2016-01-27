/*
** lib.c for minishell1 in /home/champi_t/rendu/minishell1
** 
** Made by theo champion
** Login   <champi_t@epitech.net>
** 
** Started on  Mon Jan 18 16:46:07 2016 theo champion
** Last update Sun Jan 24 23:02:55 2016 theo champion
*/

#include "header.h"

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putstr(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    my_putchar(str[i++]);
}

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  while (s1[i])
    {
      if (s1[i] < s2[i])
        return (-1);
      if (s1[i] > s2[i])
        return (1);
      i = i + 1;
    }
  if (s1[i] < s2[i])
    return (-1);
  if (s1[i] > s2[i])
    return (1);
  return (0);
}

char	**my_str_to_wordtab(char *str, int argc)
{
  int	i;
  int	j;
  int	h;
  char	**tab;
  int	stop;

  i = 0;
  j = 0;
  h = 0;
  stop = 0;
  if (str == NULL)
    return (NULL);
  if ((tab = malloc(sizeof(char *) * (argc + 10))) == NULL)
    exit(1);
  while (str[i] && stop == 0)
    {
      while (str[i] != ' ' && str[i] && str[i] != '\n')
        i = i + 1;
      tab[h++] = put_in_tab(str, j, i);
      if (!str[i++])
        stop = 1;
      j = i;
    }
  tab[h] = NULL;
  return (tab);
}

char	*put_in_tab(char *str, int j, int i)
{
  int	h;
  char	*elem;

  h = 0;
  if ((elem = malloc(sizeof(char) * (i - j + 12))) == NULL)
    exit(1);
  while (j != i)
    elem[h++] = str[j++];
  elem[h] = 0;
  return (elem);
}
