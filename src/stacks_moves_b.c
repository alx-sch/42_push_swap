/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks_moves_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:44:09 by aschenk           #+#    #+#             */
/*   Updated: 2024/02/25 13:46:53 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// THIS FILE

#include "libft/libft.h"
#include "push_swap.h"

// FILE
void	bring_cheapest_to_top(t_stacks *stacks);

// moves_a.c
void	ra(t_stacks *stacks);
void	rra(t_stacks *stacks);

// moves_b.c
void	rb(t_stacks *stacks);
void	rrb(t_stacks *stacks);

// moves_ab.c
void	rr(t_stacks *stacks);
void	rrr(t_stacks *stacks);

// target.c
void	find_target_a(t_stacks *stacks);
void	find_target_b(t_stacks *stacks);

// cost_a.c
void	calc_cost_b(t_stacks *stacks);

// cost_utils.c
size_t	find_cheapest(const t_stacks *stacks, const char x);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

// static void	to_top_r(t_stacks *stacks)
// {}
static void	to_top_r_b(t_stacks *stacks, const size_t element_to_move)
{
	int		a_value;
	int		b_value;
	size_t	median_a;
	size_t	median_b;

	a_value = stacks->stack_a[stacks->target_b[element_to_move]];
	b_value = stacks->stack_b[element_to_move];
	median_a = stacks->size_a / 2;
	median_b = stacks->size_b / 2;
	if (stacks->size_a % 2 == 1)
		median_a += 1;
	if (stacks->size_b % 2 == 1)
		median_b += 1;
	if (element_to_move < median_b)
		while (stacks->stack_b[0] != b_value)
			rb(stacks);
	else
		while (stacks->stack_b[0] != b_value)
			rrb(stacks);
	if (stacks->target_b[element_to_move] < median_a)
		while (stacks->stack_a[0] != a_value)
			ra(stacks);
	else
		while (stacks->stack_a[0] != a_value)
			rra(stacks);
}

// move up
static void	to_top_rr_b(t_stacks *stacks, const size_t element_to_move)
{
	int	a_value;
	int	b_value;

	a_value = stacks->stack_a[element_to_move];
	b_value = stacks->stack_b[stacks->target_a[element_to_move]];
	while (stacks->stack_a[0] != a_value && stacks->stack_b[0] != b_value)
		rr(stacks);
	while (stacks->stack_a[0] != a_value)
		ra(stacks);
	while (stacks->stack_b[0] != b_value)
		rb(stacks);
}

// move down
static void	to_top_rrr_b(t_stacks *stacks, const size_t element_to_move)
{
	int	a_value;
	int	b_value;

	a_value = stacks->stack_a[element_to_move];
	b_value = stacks->stack_b[stacks->target_a[element_to_move]];
	while (stacks->stack_a[0] != a_value && stacks->stack_b[0] != b_value)
		rrr(stacks);
	while (stacks->stack_a[0] != a_value)
		rra(stacks);
	while (stacks->stack_b[0] != b_value)
		rrb(stacks);
}


// brings the cheapest element in a to push to b along with it's target in
// stack b to the top of respective stacks.
void	bring_cheapest_to_top_b(t_stacks *stacks)
{
	size_t	element_to_move;

	find_target_b(stacks);
	calc_cost_b(stacks);
	element_to_move = find_cheapest(stacks, 'b');
	//ft_printf("\nMoving B[%d] (%d) ", element_to_move, stacks->stack_b[element_to_move]);
	//ft_printf("and A[%d] (%d) ", stacks->target_b[element_to_move], stacks->stack_a[stacks->target_b[element_to_move]]);
	if (stacks->rr_b[element_to_move])
	{
		//ft_printf("to top with RR moves.\n");
		to_top_rr_b(stacks, element_to_move);
	}
	else if (stacks->rrr_b[element_to_move])
	{
		//ft_printf("to top with RRR moves.\n");
		to_top_rrr_b(stacks, element_to_move);
	}
	else
	{
		//ft_printf("to top with 'single moves' only.\n");
		to_top_r_b(stacks, element_to_move);
	}
}


