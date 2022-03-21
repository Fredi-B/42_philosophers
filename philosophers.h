
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

/* ---------------------- Defines for debugging ---------------------------- */

# define dsprintf(expr) printf("\n" #expr ":\n|%s|\n", expr)
# define diprintf(expr) printf("\n" #expr ":\n|%d|\n", expr)
# define dwrite(expr) write(2, "\n" #expr "\n", strlen(#expr) + 2)

/* ----------------------------- Structures -------------------------------- */

typedef struct	s_data
{
	int				total_number_of_p;
	int				cnt_number_of_p;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	unsigned long	total_time;
	pthread_mutex_t	**cutlery;
	int				philosopher;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned long	time_last_eaten;
}				t_data;

/*  ------------------------ Function prototypes --------------------------- */
/*  ------------------------------- main.c --------------------------------- */
/*  ---------------------------- libft_utils.c ----------------------------- */
int	ft_atoi(const char *str);
int	ft_is_pos_int(char *str);
/*  ------------------------------ parsing.c ------------------------------- */
int	parsing(t_data *data, int argc, char **argv);
/*  ---------------------------- init_mutexes.c ---------------------------- */
int		init_mutexes(t_data *data);
/*  ------------------------------- time.c --------------------------------- */
void	free_data(t_data *data);

#endif
