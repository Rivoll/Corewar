/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenguyen <kenguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 15:26:51 by kenguyen          #+#    #+#             */
/*   Updated: 2018/04/30 15:35:52 by ysingaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_init_color(t_player *players, t_arena *arena)
{
	int color;
	int i;
	int adr;

	start_color();
	refresh_arena(arena, 0, MEM_SIZE, 0);
	i = 1;
	if (arena->nbr_of_playr < 7)
	{
		color = 1;
		while (players)
		{
			init_pair((unsigned char)players->nbr, color++, COLOR_BLACK);
			adr = (MEM_SIZE / arena->nbr_of_playr) *
				(arena->nbr_of_playr - i);
			refresh_arena(arena, adr, players->file_size, players->nbr);
			players = players->next;
			i++;
		}
	}
}

void		waitting(void)
{
	unsigned int	i;
	unsigned int	max;

	i = 0;
	max = 500000;
	while (i < max)
		i++;
}

int			print_players_infos(t_player *player, int x, int y)
{
	if (has_colors() != FALSE)
		attron(COLOR_PAIR((unsigned char)player->nbr));
	mvprintw(y += 2, x, "%s: %-10d", player->name, player->nbr_live);
	if (has_colors() != FALSE)
		attroff(COLOR_PAIR((unsigned char)player->nbr));
	while ((player = player->next))
	{
		mvprintw(y += 1, x, "vs");
		if (has_colors() != FALSE)
			attron(COLOR_PAIR((unsigned char)player->nbr));
		mvprintw(y += 1, x, "%s: %-10d", player->name, player->nbr_live);
		if (has_colors() != FALSE)
			attroff(COLOR_PAIR((unsigned char)player->nbr));
	}
	return (y);
}

void		refresh_status(t_arena *arena, int ctd, int finish)
{
	int			x;
	int			y;

	x = 195;
	y = 0;
	mvprintw(y += 2, x, "Cycle : %d", arena->cycles);
	mvprintw(y += 2, x, "Processes : %-10d", arena->process_cpt);
	mvprintw(y += 2, x, "CYCLE_TO_DIE : %-4d", ctd);
	mvprintw(y += 2, x, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvprintw(y += 2, x, "NBR_LIVE : %-10d", arena->nbr_live);
	y = print_players_infos(arena->players, x, y);
	if (finish)
		mvprintw(y += 2, x, "And the winner is... %s!\n",
			get_winner(arena->players, arena->winner));
	refresh();
	waitting();
}

void		refresh_arena(t_arena *arena, int adr, int len, unsigned char color)
{
	int x;
	int y;

	adr = get_valide_adr(adr);
	x = get_valide_adr(adr + len - 1) * 3;
	y = x / 192;
	if (len)
	{
		refresh_arena(arena, adr, --len, color);
		if (color && has_colors() != FALSE)
			attron(COLOR_PAIR(color));
		mvprintw(y, x % 192, "%.2x ", arena->board[get_valide_adr(adr + len)]);
		refresh();
		if (color && has_colors() != FALSE)
			attroff(COLOR_PAIR(color));
	}
}
