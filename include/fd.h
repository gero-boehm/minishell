#ifndef FD_H
# define FD_H

# include <sys/types.h>

int		fd_open(char *path, int flags, mode_t mode, int *fd);
int		fd_dup(int fd_old, int *fd_new);
int		fd_pipe(int ports[2]);
void	fd_close(int fd);
void	fd_close_all(void);

#endif