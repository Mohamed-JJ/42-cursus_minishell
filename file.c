/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjarboua <mjarboua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:02:12 by mjarboua          #+#    #+#             */
/*   Updated: 2023/04/05 16:06:43 by mjarboua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int search(int* nums, int size, int target){
    int end = size - 1;

    if (size == 1 && nums[0] == target)
        return (0);
    for (int i = 0; i < size; i++)
    {
        if (nums[i] == target)
            return (i);
        // else if (nums[end] == target)
        //     return (end);
        end--;
    }
    return (-1);
}

int main()
{
	int nums[] = {-1, 0, 5};
	int size = sizeof(nums) / sizeof(nums[0]);
	int target = 0;
	printf("%d", search(nums, size, target));
	return (0);
}