/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingaye <ysingaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:56:40 by ysingaye          #+#    #+#             */
/*   Updated: 2018/04/30 15:41:21 by ysingaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void	ft_strendcmp(const char *s1, const char *s2, t_arena *arena)
{
	int	i;

	i = ft_strlen(s1) - ft_strlen(s2);
	if (i < 1)
		ft_error("Invalide file name", arena);
	if (ft_strcmp(s1 + i, s2))
		ft_error("Invalide file name", arena);
}

char	*get_winner(t_player *player, int winner)
{
	while (player)
	{
		if (player->nbr == winner)
			return (player->name);
		player = player->next;
	}
	return ("Nobody");
}

void	print_players(t_player *player)
{
	while (player)
	{
		ft_printf("* Player %d: \"%s\" (\"%s\")\n",
			player->nbr, player->name, player->comment);
		player = player->next;
	}
}

int		main(int argc, char **argv)
{
	t_arena		*arena;

	ft_bzero(&arena, sizeof(arena));
	arena = new_arena();
	check_arg_create_players(argc, argv, arena);
	fill_players(arena);
	if (arena->process_cpt > MAX_PLAYERS)
		ft_error("Too many champ", arena);
	else if (arena->process_cpt <= 0)
		ft_usage(argv[0], arena);
	print_players(arena->players);
	execute_vm(arena);
	ft_printf("And the winner is... %s!\n", get_winner(arena->players,
		arena->winner));
	free_arena(arena);
	return (0);
}
