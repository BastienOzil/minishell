/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:00:33 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 15:00:34 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define MAX_ROWS 100
# define MAX_COLS 300
# define TITLE " GHOST IN THE MINISHELL "

typedef struct s_animation
{
	char	screen[MAX_ROWS][MAX_COLS];
	int		rows;
	int		cols;
	int		frame;
	int		max_frames;
	int		fast_forward_frame;
	int		title_done_frame;
	int		post_title_wait;
	int		last_sound_index;
}			t_animation;

/* animation.c */
void		launch_animation(void);
void		init_animation(t_animation *anim);
void		run_animation_loop(t_animation *anim);

/* screen_utils.c */
void		clear_screen(void);
void		move_cursor(int row, int col);
int			int_to_str(int n, char *str);
void		get_terminal_size(int *rows, int *cols);

/* matrix_effects.c */
int			ft_random_digit(void);
void		init_screen_matrix(char screen[MAX_ROWS][MAX_COLS], int rows,
				int cols);
void		update_matrix_char(char *c);
void		draw_matrix_char(char c, int should_fade, int frame,
				int max_frames);

/* title_display.c */
int			display_title_char(const char *title, int frame, int i, int j,
				int *last_sound_index);
int			is_in_title_area(int i, int j, int rows, int cols, int title_len);
void		check_title_sound(int ti, int *last_sound_index);
int			should_display_title_char(int frame, int ti);
void		display_final_title(const char *title);

/* prompt_utils.c */
void		slow_type_prompt(const char *str);

#endif
