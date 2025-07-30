/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:10:14 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 10:11:05 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/animation.h"

void launch_animation(void)
{
	t_animation anim;

	init_animation(&anim);
	run_animation_loop(&anim);
	display_final_title(TITLE);
}

void init_animation(t_animation *anim)
{
	int title_len;

	title_len = strlen(TITLE);
	srand(time(NULL));
	get_terminal_size(&anim->rows, &anim->cols);
	init_screen_matrix(anim->screen, anim->rows, anim->cols);
	anim->frame = 0;
	anim->max_frames = 200;
	anim->fast_forward_frame = 160;
	anim->title_done_frame = (int)(title_len * 3.2);
	anim->post_title_wait = 0;
	anim->last_sound_index = -1;
}

