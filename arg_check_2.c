/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:49:02 by aschenk           #+#    #+#             */
/*   Updated: 2024/02/12 11:06:01 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	This file implements a function for validating command-line arguments,
//	ensuring they represent valid integer values without duplicates.
//	It returns an integer array of arguments if the validation is successful.
//
//	Valid input for the push_swap program:
//	-	Integers with optional sign ('+'/'-') followed by digits,
//		within the range of 'int' data type.
//	-	Integers must not be duplicates.
//	-	Strings: If values are separated by one or more space characters.
//	-	Mix of strings and integers.
//	-	Leading zeroes before numbers are allowed.
//
//	Examples of valid input:
//	-	./push_swap 42 -2 +0
//	-	./push_swap 1 "42 -2" 2 "5 6"
//	-	./push_swap 00042 -05
//
//	Invalid input:
//	-	Floats or non-integer numeric values (e.g. "4.2" or "2147483650")
//	-	Characters, symbols, or more than one sign (e.g. "e!", "++42").
//	-	Duplicates (e.g. ./push_swap 00042 +42)
//	-	Incorrectly formatted numbers (e.g., "1a" or "42-").

#include "libft/libft.h"
#include "push_swap.h" // bool, error code

//	FILE
int		*check_args(int argc, char **argv);

//	libft
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *nptr);
int		ft_printf(const char *format, ...);

//	utils.c
void	free_arr(char **array);
int		count_tokens_in_str(char *string);

//	arg_check_1.c
bool	is_valid_int_str(const char *str);

//	+++++++++++++++
//	++ FUNCTIONS ++
//	+++++++++++++++

//	Concatenates all command-line arguments provided as input
//	into a single string separated by spaces.
static char	*concatenate_args(int argc, char **argv)
{
	char	*concat_str;
	char	*arg_with_space_added;
	char	*temp;
	int		i;

	concat_str = "";
	i = 1;
	while (i < argc)
	{
		arg_with_space_added = ft_strjoin(argv[i], " ");
		if (!arg_with_space_added && i != 1)
		{
			free(concat_str);
			return (NULL);
		}
		temp = concat_str;
		concat_str = ft_strjoin(concat_str, arg_with_space_added);
		free(arg_with_space_added);
		if (i != 1)
			free(temp);
		if (!concat_str)
			return (NULL);
		i++;
	}
	return (concat_str);
}

//	Parses a string representing integer values into an array of integers.
static int	*parse_str_to_int_arr(const char *str, size_t num_tokens)
{
	char	**tokens;
	size_t	i;
	int		*int_array;

	tokens = ft_split(str, ' ');
	i = 0;
	if (!tokens)
		return (NULL);
	int_array = (int *)ft_calloc(num_tokens, sizeof(int));
	if (!int_array)
	{
		free_arr(tokens);
		return (NULL);
	}
	while (i < num_tokens)
	{
		int_array[i] = ft_atoi(tokens[i]);
		i++;
	}
	free_arr(tokens);
	return (int_array);
}

//	Checks if there are any duplicates in an array of integers.
static bool	has_duplicates(int *array, size_t length)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!array || length <= 0)
		return (true);
	while (i < length - 1)
	{
		j = i + 1;
		while (j < length)
		{
			if (array[i] == array[j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

//	Checks if command-line arguments are valid integer representations.
//	Prints error message if check fails.
//	Returns:
//	-	A string containing concatenated arguments if valid.
//	-	NULL otherwise.
static char	*check_args_pre(int argc, char **argv)
{
	char	*arg_str;

	if (argc < 2)
	{
		ft_printf("Error\n");
		exit(1);
	}
	arg_str = concatenate_args(argc, argv);
	if (!arg_str)
	{
		ft_printf("Error\n");
		exit(2);
	}
	if (!is_valid_int_str(arg_str))
	{
		ft_printf("Error\n");
		free(arg_str);
		exit(3);
	}
	return (arg_str);
}

//	Validates command-line arguments, ensuring they represent
//	valid integer values without duplicates.
//	Prints an error message if the validation fails.
//
//	Returns:
//	-	An integer array containing the validated arguments if
//		the validation is successful.
//	-	NULL if the validation fails.
int	*check_args(int argc, char **argv)
{
	char	*arg_str;
	size_t	num_tokens;
	int		*int_arr;

	arg_str = check_args_pre(argc, argv);
	if (!arg_str)
		exit(EXIT_FAILURE);
	num_tokens = count_tokens_in_str(arg_str);
	int_arr = parse_str_to_int_arr(arg_str, num_tokens);
	free(arg_str);
	if (!int_arr || has_duplicates(int_arr, num_tokens))
	{
		ft_printf("Error\n");
		free(int_arr);
		exit(EXIT_FAILURE);
	}
	return (int_arr);
}
