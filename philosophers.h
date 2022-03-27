
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ----------------------------- Includes ---------------------------------- */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
/* ----------------------------- Defines ----------------------------------- */

# define TRUE 0
# define FALSE 1
# define OK 0
# define ERROR 1
# define L_FORK 0
# define R_FORK 4
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIED 5


/* ---------------------- Defines for debugging ---------------------------- */

# define dsprintf(expr) printf("\n" #expr ":\n|%s|\n", expr)
# define diprintf(expr) printf("\n" #expr ":\n|%d|\n", expr)
# define dwrite(expr) write(2, "\n" #expr "\n", strlen(#expr) + 2)

/* ----------------------------- Structures -------------------------------- */

typedef struct	s_data
{
	int				total_number_of_p;
	int				*cnt_number_of_p;
	long			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				*enough_meals;
	unsigned long	*start_time;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	**cutlery;
	int				philosopher;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned long	*time_last_eaten;
	int				times_eaten;
	int				*died;
}				t_data;

/*  ------------------------ Function prototypes --------------------------- */
/*  ------------------------------- main.c --------------------------------- */
/*  ---------------------------- libft_utils.c ----------------------------- */
int		ft_atoi(const char *str);
int		ft_is_pos_int(char *str);
/*  ------------------------------ parsing.c ------------------------------- */
int		parsing(t_data *data, int argc, char **argv);
/*  ---------------------------- init_mutexes.c ---------------------------- */
int		init_mutexes(t_data *data);
/*  ---------------------------- init_threads.c ---------------------------- */
int		init_threads(t_data *data);
/*  ---------------------------=-- routine.c ------------------------------- */
void	*routine(void *arg);
void	protected_print(t_data *philosopher, int state);
/*  -------------------------------- eat.c --------------------------------- */
void	eat(t_data *philosopher);
/*  -------------------------- sleep_and_think.c --------------------------- */
void	sleep_and_think(t_data *philosopher);
/*  ------------------------------ doctor.c -------------------------------- */
void	*doctor(void *arg);
/*  ------------------------------- time.c --------------------------------- */
/*  ----------------------------- free_data.c ------------------------------ */
void	free_data(t_data *data);
void	err_exit(t_data *data, int exit_status, char *msg, int len);

#endif
