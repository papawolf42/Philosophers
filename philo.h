/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:46:53 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/14 20:53:50 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# define STR_DIED		" \e[91mdied\e[0m\n"
# define STR_FORK		" \e[93mhas taken a fork\e[0m\n"
# define STR_EAT		" \e[92mis eating\e[0m\n"
# define STR_SLEEP		" \e[96mis sleeping\e[0m\n"
# define STR_THINK		" \e[95mis thinking\e[0m \n"

# define ANSI_RED		"\e[91m"
# define ANSI_GREEN		"\e[92m"
# define ANSI_YELLOW	"\e[93m"
# define ANSI_BLUE		"\e[94m"
# define ANSI_MAGENTA	"\e[95m"
# define ANSI_CYAN		"\e[96m"

# define DECIMAL		"0123456789"
# define STDOUT			1

# define FULL			1
# define HUNGRY			0

/*
struct
*/
typedef struct s_info			t_info;
typedef struct s_philo			t_philo;
typedef struct s_common			t_common;

typedef enum e_bool				t_bool;
typedef enum e_status			t_status;
typedef enum e_error			t_error;
typedef enum e_state			t_state;

/*
enum
*/
enum			e_bool
{
	true = 1,
	false = 0
};

enum			e_state
{
	forking = 27,
	eating = 20,
	sleeping = 22,
	thinking = 23,
	died = 15
};

enum			e_error
{
	no_error = 0,
	err_malloc_fail = 1
};

struct			s_info
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_time_each_philo_must_eat;
};

struct			s_common
{
	long			time_start;
	long			time_delay;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_enter;
	pthread_mutex_t	m_check_die;
	pthread_mutex_t	m_full;
	int				count_full;
	int				count_entered;
	int				num_starve;
	t_bool			flag_all_eaten;
	t_bool			flag_all_entered;
	t_bool			flag_someone_died;
};

struct			s_philo
{
	int				index;
	int				num;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	int				rfork;
	int				lfork;
	long			time_last_eat;
	long			times_eat;
	t_info			*info;
	t_common		*common;
};

/*
main.c
*/
void	ft_parse_info(int argc, char *argv[], t_info *info);
t_error	ft_set_up_dining(t_info *info);

int		ft_atoi(const char *nptr);

/*
set_up_dining.c
*/
t_error	ft_set_up_dining(t_info *info);
t_error	ft_alloc_vars(t_philo **philo, pthread_mutex_t **fork, int num);
void	ft_init_common(t_info *info, t_common *common);
void	ft_init_vars(t_info *info, t_philo *philo, pthread_mutex_t *fork,
			t_common *common);
void	ft_enter_dining_room(t_info *info, t_philo *philo, t_common *common);
void	ft_loop(t_info *info, t_philo *philo, t_common *common);

/*
dining.c
*/

void	*ft_dining(void *var);
void	ft_sitting(t_philo *philo);
int		ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);

/*
print.c
*/
void	ft_print_state(t_philo *philo, t_state state);
void	ft_putstr_state(char *str, t_state state, long now, int philo_num);
void	ft_putstr(char *s, int strlen);

/*
time.c
*/
long	ft_time(void);
void	ft_sleep(t_philo *philo, long time);
void	ft_wait(t_philo *philo);

/*
putnbr.c
*/
void	ft_putnbr(long n);
int		ft_count_digit(long nbr);
void	ft_recursive_putnbr_fd(long n, int digit, long *base, int i);
void	ft_putnbr_ms(long n);
void	ft_recursive_putnbr_fd_ms(long n, int digit, long *base, int *save);

#endif
