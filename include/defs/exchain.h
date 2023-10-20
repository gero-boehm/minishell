#ifndef EXCHAIN_H
# define EXCHAIN_H

typedef struct s_ex_chain
{
	int				exit_code;
	pid_t			pid;
	unsigned long	i;
	int				fd;
	t_raw_command	*raw;
	t_command		cmd;
	int				ports[2];
}	t_exchain;

#endif