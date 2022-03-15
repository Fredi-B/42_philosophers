
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ----------------------------- Includes ---------------------------------- */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
/* ----------------------------- Defines ----------------------------------- */

/* # define TRUE 1
# define FALSE 0
# define OK 0
# define ERROR -2 */

/* ---------------------- Defines for debugging ---------------------------- */

# define dsprintf(expr) printf("\n" #expr ":\n|%s|\n", expr)
# define diprintf(expr) printf("\n" #expr ":\n|%d|\n", expr)
# define dwrite(expr) write(2, "\n" #expr "\n", strlen(#expr) + 2)

/* ----------------------------- Structures -------------------------------- */

typedef struct	s_data
{
	int				cnt_p;
	pthread_mutex_t	*mutex1;
}				t_data;

/* typedef struct s_in_out
{
	char			*name;
	char			*here_doc;
	int				mode;
	struct s_in_out	*next;

}				t_in_out;
 */
/*  ------------------------ Function prototypes --------------------------- */
/*  ------------------------------- main.c --------------------------------- */
/*  ------------------------------- time.c --------------------------------- */


#endif
