#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

/* ----------------------------- Includes ---------------------------------- */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
/* ----------------------------- Defines ----------------------------------- */

# define TRUE 0
# define FALSE 1
# define OK 0
# define ERROR 1

/* ---------------------- Defines for debugging ---------------------------- */

# define dsprintf(expr) printf("\n" #expr ":\n|%s|\n", expr)
# define diprintf(expr) printf("\n" #expr ":\n|%d|\n", expr)
# define dlprintf(expr) printf("\n" #expr ":\n|%lli|\n", expr)
# define dwrite(expr) write(2, "\n" #expr "\n", strlen(#expr) + 2)

/* ----------------------------- Structures -------------------------------- */

typedef struct s_data
{
	int			total_number_of_p;
	long		time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_meals;
	int			philosopher;
	long long	start_time;
	sem_t		*cutlery_sem;
	sem_t		*print_sem;
	
}				t_data;

/*  ------------------------ Function prototypes --------------------------- */
/*  ---------------------------- main_bonus.c ------------------------------ */
/*  -------------------------- parsing_bonus.c ----------------------------- */
int	parsing(t_data *data, int argc, char **argv);
/*  ------------------------ libft_utils_bonus.c --------------------------- */
int	ft_atoi(const char *str);
int	ft_is_pos_int(char *str);
/*  ----------------------- routine_utils_bonus.c -------------------------- */
void	routine(t_data *data);

#endif