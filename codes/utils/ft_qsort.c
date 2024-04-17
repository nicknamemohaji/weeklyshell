/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:59:28 by dogwak            #+#    #+#             */
/*   Updated: 2024/04/05 15:15:17 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
	quick sort

	 sort array of pointer in quick-sort algorithm.

	 < parameter >
	 arr	: pointer to array which is array of pointer.
	 	each element of array point to the resource.
	 left	: left most index of arr to sort, 0 based, included.
	 right	: right most index of arr to sort, 0 based, included.
	 cmp	: comparator, take two pointer of resource to compare.

		t_bool compare(void *pa, void *pb)

	 	if a is greater than b	-> return *pa > *pb, descending order.
		if a is less than b		-> return *pa < *pb, ascending order.
*/
void	ft_qsort(void **arr, int left, int right,
			t_bool (*cmp)(const void*, const void*))
{
	const void	*pivot = arr[(left + right) >> 1];
	int			i;
	int			j;
	void		*ptemp;

	i = left;
	j = right;
	while (i <= j)
	{
		while (cmp(arr[i], pivot))
			i++;
		while (cmp(pivot, arr[j]))
			j--;
		if (i <= j)
		{
			ptemp = arr[i];
			arr[i++] = arr[j];
			arr[j--] = ptemp;
		}
	}
	if (left < j)
		ft_qsort(arr, left, j, cmp);
	if (i < right)
		ft_qsort(arr, i, right, cmp);
}
