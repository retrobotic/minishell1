/*
** get_next_line.c for get_next_line in /home/champi_t/rendu/get_next_line
** 
** Made by theo champion
** Login   <champi_t@epitech.net>
** 
** Started on  Fri Dec 25 13:21:39 2015 theo champion
** Last update Sun Jan 24 23:10:27 2016 theo champion
*/

#include "header.h"

int	my_strlen(char *str)
{
  int	len;

  if (str == NULL)
    return (1);
  len = 0;
  while (str[len])
    len = len + 1;
  return (len);
}

char	*offset_check(char *off, char *buffer)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (off != NULL && off[j] != '\n' && off[j])
    j = j + 1;
  if (off != NULL && off[j] == '\n')
    {
      if ((buffer = malloc(sizeof(char) * j)) == NULL)
        return (NULL);
      while (off[i] != '\n' && off[i] != '\0')
        buffer[i] = off[i++];
      buffer[i] = 0;
      i = 0;
      j = j + 1;
      while (off[j])
        off[i++] = off[j++];
      off[i] = 0;
    }
  return (buffer);
}

char		*get_next_line(const int fd)
{
  char		*buffer;
  char		tmp[READ_SIZE + 1];
  t_control	control;
  static char	offset[READ_SIZE];

  control.stop = 0;
  control.ptr_stop = &control.stop;
  buffer = NULL;
  if ((buffer = offset_check(offset, buffer)) != NULL)
    return (buffer);
  while (control.stop == 0)
    {
      if ((control.readed = read(fd, tmp, READ_SIZE)) != READ_SIZE)
        control.stop = 1;
      tmp[control.readed] = 0;
      if (read_to_linebuf(offset, &buffer, tmp, &control))
        return (NULL);
    }
  return (buffer);
}

int	read_to_linebuf(char *off, char **old, char *tmp, t_control *ctrl)
{
  char	*new;
  int	i;
  int	j;

  i = 0;
  j = 0;
  if ((new = malloc(sizeof(char) * (my_strlen(*old) + READ_SIZE + 1))) == NULL)
    return (1);
  while (off != NULL && off[j])
    new[j] = off[j++];
  while (*old != NULL && (*old)[i])
    new[j++] = (*old)[i++];
  i = 0;
  while (tmp[i] != '\n' && tmp[i])
    new[j++] = tmp[i++];
  new[j] = 0;
  linebuf_to_offset(tmp, off, ctrl, i);
  *old = new;
  if (!new[0])
    *old = NULL;
  return (0);
}

void	linebuf_to_offset(char *tmp, char *off, t_control *ctrl, int i)
{
  int	j;

  j = 0;
  off[j] = 0;
  if (tmp[i++])
    {
      *ctrl->ptr_stop = 1;
      while (tmp[i])
        off[j++] = tmp[i++];
      off[j] = 0;
    }
}
