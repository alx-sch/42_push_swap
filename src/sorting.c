/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:20:37 by aschenk           #+#    #+#             */
/*   Updated: 2024/02/22 21:13:48 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// THIS FILE..

#include "libft/libft.h"
#include "push_swap.h"

// FILE
bool	is_sorted_a(const t_stacks *stacks);
void	sort_three(t_stacks *stacks);
void	sort_more_than_three(t_stacks *stacks);

// target.c
void	find_target_a(t_stacks *stacks);

// cost_a.c
void	calc_cost_a(t_stacks *stacks);

// stacks_utils.c
int		find_max_val(const t_stacks *stacks, const char x);

// moves_a.c
void	sa(t_stacks *stacks);
void	ra(t_stacks *stacks);
void	rra(t_stacks *stacks);

// moves_b.c
void	pb(t_stacks *stacks);



size_t	find_cheapest(const t_stacks *stacks, const char x);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

// Checks if 'stack A' is sorted from smallest to largest.
// A stack with only one element is also considered 'sorted'.
bool	is_sorted_a(const t_stacks *stacks)
{
	size_t	i;

	i = 0;
	while (i < stacks->size_a - 1)
	{
		if (stacks->stack_a[i] > stacks->stack_a[i + 1])
			return (false);
		i++;
	}
	return (true);
}

// Sorts 'stack A' with a size of three in ascending order.
// First, it rotates the largest element to the bottom if it's not already in
// that position. Then, it swaps the top two elements, if top > middle.
void	sort_three(t_stacks *stacks)
{
	int	max_value;

	max_value = find_max_val(stacks, 'a');
	if (stacks->stack_a[0] == max_value)
		ra(stacks);
	else if (stacks->stack_a[1] == max_value)
		rra(stacks);
	if (stacks->stack_a[0] > stacks->stack_a[1])
		sa(stacks);
}

void	sort_more_than_three(t_stacks *stacks)
{
	size_t	element_to_move;

	if (stacks->size_a > 3)
		pb(stacks);
	if (stacks->size_a > 3)
		pb(stacks);
	while (stacks->size_a > 3)
	{
		find_target_a(stacks);
		calc_cost_a(stacks);
		element_to_move = find_cheapest(stacks, 'a');
	}
	ft_printf("Element to move: %d\n", element_to_move);
}



// 	}
// 	sort_three(stacks);

// }


// {
// 	bool	exit_success;

// 	exit_success = false;
// 	if (is_sorted(array, size))
// 		exit_success = true;
// 	if ()


// }


// void	small_sort(t_stacks *stacks)
// {
// 	bool	exit_success;

// 	exit_success = false;
// 	if (is_sorted(stacks))
// 		exit_success = true;
// 	else if (stacks->size_a == 2)
// 	{
// 		sa(stacks);
// 		exit_success = true;
// 	}
// 	else if (stacks->size_a == 3)
// 	{
// 		if (stacks->stack_a[2] == find_max_in_stack_a(stacks))
// 		{
// 			sa(stacks);
// 			exit_success = true;
// 		}



// 	}
// 	if (exit_success)
// 	{
// 		free(array);
// 		exit_free_stacks(EXIT_SUCCESS, "", stacks);
// 	}
// }