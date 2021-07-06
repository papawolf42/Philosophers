/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:46:53 by gunkim            #+#    #+#             */
/*   Updated: 2021/07/06 19:18:17 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# define STR_FORK		"%ldms %d %shas taken a fork\e[0m\n"
# define STR_EAT		"%ldms %d %sis eating\e[0m\n"
# define STR_SLEEP		"%ldms %d %sis sleeping\e[0m\n"
# define STR_THINK		"%ldms %d %sis thinking\e[0m\n"

# define ANSI_RED		"\e[91m"
# define ANSI_GREEN		"\e[92m"
# define ANSI_YELLOW	"\e[93m"
# define ANSI_BLUE		"\e[94m"
# define ANSI_MAGENTA	"\e[95m"
# define ANSI_CYAN		"\e[96m"

/*
struct
*/
typedef struct s_info		t_info;
typedef struct s_philo		t_philo;
typedef struct s_common		t_common;

typedef struct s_timeval	t_timeval;

typedef enum e_bool			t_bool;
typedef enum e_status		t_status;
typedef enum e_error		t_error;
typedef enum e_state		t_state;

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
	forking,
	eating,
	thinking,
	sleeping,
	died
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
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_enter;
	int				num_entered;
	t_bool			flag_all_entered;
	t_bool			flag_someone_died;
};

struct			s_philo
{
	int				index;
	int				num;
	pthread_t		thread;
	pthread_mutex_t	*print;
	pthread_mutex_t	*fork;
	int				rfork;
	int				lfork;
	long			time_last_eat;
	t_state			state;
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
void	ft_init_common(t_common *common);
void	ft_init_vars(t_info *info, t_philo *philo, pthread_mutex_t *fork,
			t_common *common);
void	ft_enter_dining_room(t_info *info, t_philo *philo, t_common *common);

/*
dining.c
*/

void	*ft_dining(void *var);
void	ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);
void	ft_yousleep(long time);

/*
print.c
*/
void	ft_print_state(t_philo *philo);

/*
time.c
*/
long	ft_time(void);

#endif
