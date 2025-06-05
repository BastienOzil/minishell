#include "../includes/animation.h"

void	launch_animation(void)
{
	t_animation	anim;

	init_animation(&anim);
	run_animation_loop(&anim);
	display_final_title(TITLE);
}

void	init_animation(t_animation *anim)
{
	int	title_len;

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

void	run_animation_loop(t_animation *anim)
{
	int	i;
	int	j;
	int	title_displayed;

	while (anim->frame < anim->max_frames)
	{
		clear_screen();
		if (anim->frame > anim->title_done_frame)
			anim->post_title_wait++;
		if (anim->post_title_wait > 10)
			break ;
		i = 0;
		while (i < anim->rows)
		{
			move_cursor(i + 1, 1);
			j = 0;
			while (j < anim->cols)
			{
				title_displayed = display_title_char(TITLE, anim->frame, i, j, &anim->last_sound_index);
				if (!title_displayed)
				{
					draw_matrix_char(anim->screen[i][j], 1, anim->frame, anim->max_frames);
					update_matrix_char(&anim->screen[i][j]);
				}
				j++;
			}
			i++;
		}
		usleep((anim->frame > anim->fast_forward_frame) ? 10000 : 30000);
		anim->frame++;
	}
}
