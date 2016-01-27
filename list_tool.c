/*
** list_tool.c for minishell in /home/champi_t/rendu/minishell1
** 
** Made by theo champion
** Login   <champi_t@epitech.net>
** 
** Started on  Tue Jan 19 14:58:00 2016 theo champion
** Last update Sun Jan 24 22:56:33 2016 theo champion
*/

#include "header.h"

t_list		*fill_list(char **env)
{
  int		i;
  t_list	*lenv;
  char		*str;
  int		j;

  i = 0;
  j = 0;
  lenv = NULL;
  while (env[i])
    {
      while (env[i][j])
        j = j + 1;
      if ((str = malloc(sizeof(char) * (j + 2))) == NULL)
        exit(1);
      j = 0;
      while (env[i][j])
        str[j] = env[i][j++];
      str[j] = 0;
      lenv = add_elem_end(lenv, str);
      i = i + 1;
    }
  return (lenv);
}

t_list		*add_elem_end(t_list *lenv, char *str)
{
  t_list	*elem;
  t_list	*tmp;

  if ((elem = malloc(sizeof(t_list) + my_strlen(str))) == NULL)
    exit(1);
  elem->str = str;
  elem->next = NULL;
  if (lenv == NULL)
    return (elem);
  else
    {
      tmp = lenv;
      while (tmp->next != NULL)
        tmp = tmp->next;
      tmp->next = elem;
      return (lenv);
    }
}

t_list		*del_elem(t_list *lenv, t_list *elem)
{
  t_list	*tmp;

  tmp = lenv;
  if (elem == tmp)
    {
      tmp = lenv->next;
      free(lenv);
      return (tmp);
    }
  while (tmp->next != elem)
    tmp = tmp->next;
  tmp->next = tmp->next->next;
  return (lenv);
}

t_list		*find_elem(t_list *lenv, char *var)
{
  int		i;
  t_list	*tmp;

  tmp = lenv;
  while (tmp != NULL)
    {
      i = 0;
      while (var[i] == tmp->str[i] && var[i])
        i = i + 1;
      if (tmp->str[i] == '=')
        return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

char		**my_list_to_tab(t_list *lenv, char **env)
{
  int		i;
  t_list	*tmp;
  char		**new;

  tmp = lenv;
  i = 0;
  while (tmp != NULL)
    {
      tmp = tmp->next;
      i = i + 1;
    }
  if ((new = malloc(sizeof(char *) * (i + 2))) == NULL)
    exit(1);
  tmp = lenv;
  i = 0;
  while (tmp != NULL)
    {
      new[i] = tmp->str;
      i = i + 1;
      tmp = tmp->next;
    }
  new[i] = NULL;
  free_all(env);
  return (new);
}
