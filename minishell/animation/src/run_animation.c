/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:11:17 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 10:11:36 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/animation.h"

static void	process_animation_frame(t_animation *anim)
{
	clear_screen();
	if (anim->frame > anim->title_done_frame)
		anim->post_title_wait++;
}

static void	draw_row_chars(t_animation *anim, int i)
{
	int	j;
	int	title_displayed;

	j = 0;
	while (j < anim->cols)
	{
		title_displayed = display_title_char(TITLE, anim->frame, i, j,
				&anim->last_sound_index);
		if (!title_displayed)
		{
			draw_matrix_char(anim->screen[i][j], 1, anim->frame,
				anim->max_frames);
			update_matrix_char(&anim->screen[i][j]);
		}
		j++;
	}
}

static void	render_screen(t_animation *anim)
{
	int	i;

	i = 0;
	while (i < anim->rows)
	{
		move_cursor(i + 1, 1);
		draw_row_chars(anim, i);
		i++;
	}
}

static void	handle_frame_timing(t_animation *anim)
{
	if (anim->frame > anim->fast_forward_frame)
		usleep(10000);
	else
		usleep(20000);
	anim->frame++;
}

void	run_animation_loop(t_animation *anim)
{
	while (anim->frame < anim->max_frames)
	{
		process_animation_frame(anim);
		if (anim->post_title_wait > 10)
			break ;
		render_screen(anim);
		handle_frame_timing(anim);
	}
}
