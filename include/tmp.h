#ifndef TMP_H
# define TMP_H

int		tmp_create(int *fd);
int		tmp_write(int fd, char *str);
void	tmp_close(int fd);

#endif