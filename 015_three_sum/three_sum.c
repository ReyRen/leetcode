#include <stdio.h>
#include <stdlib.h>

static int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

static void two_sum(int *nums, int low, int high, int target, int **results, int *count)
{
    while (low < high) {
        int diff = target - nums[low];
        if (diff > nums[high]) {
            while (++low < high && nums[low] == nums[low - 1]) {}
        } else if (diff < nums[high]) {
            while (--high > low && nums[high] == nums[high + 1]) {}
        } else {
            results[*count] = malloc(3 * sizeof(int));
            results[*count][0] = -target;
            results[*count][1] = nums[low];
            results[*count][2] = nums[high];
            (*count)++;
            while (++low < high && nums[low] == nums[low - 1]) {}
            while (--high > low && nums[high] == nums[high + 1]) {}
        }
    }
}

/**
 ** Return an array of arrays of size *returnSize.
 ** Note: The returned array must be malloced, assume caller calls free().
 **/
static int** threeSum(int* nums, int numsSize, int* returnSize)
{
    if (numsSize < 3) {
        return NULL;
    }

    qsort(nums, numsSize, sizeof(*nums), compare);

    *returnSize = 0;
    int i, j, capacity = 50000;
    int **results = malloc(capacity * sizeof(int *));
    for (i = 0; i < numsSize; i++) {
        if (i == 0 || i > 0 && nums[i] != nums[i - 1]) {
            two_sum(nums, i + 1, numsSize - 1, -nums[i], results, returnSize);
        }
    }
	//need call free(results) when returnSize is 0.
    return results;
}

//double pointer
static int** threeSum2(int* nums, int numsSize, int* returnSize)
{
	*returnSize = 0;
    if (numsSize < 3) {
        return NULL;
    }

    qsort(nums, numsSize, sizeof(*nums), compare);
    int i, j, k, capacity = 50000;
    int **ret = malloc(capacity * sizeof(int *));
	for(i=0; i<numsSize; ++i){
		j = i + 1;
		k = numsSize - 1;
		while(j<k){
			if(nums[i] + nums[j] + nums[k] == 0){
				ret[*returnSize] = malloc(sizeof(int) * 3);
				ret[*returnSize][0] = nums[i];
				ret[*returnSize][1] = nums[j];
				ret[*returnSize][2] = nums[k];
				(*returnSize)++;
				++j; --k;
				//skip duplicates of n & m
				while(j<k && nums[j-1] == nums[j]) ++j;
				while(j<k && nums[k] == nums[k+1]) --k;
			} else if (nums[i] + nums[j] + nums[k] < 0){
				++j;
			} else {
				--k;
			}

			//skip duplicates of i
			while(i<numsSize-1 && nums[i] == nums[i+1]) ++i;
		}
	}
	if(*returnSize == 0) {
		free(ret);
		return NULL;
	}
	return ret;
}

int main(void)
{
    int i, count;
    //int nums[] = { -1, 0, 1, 2, -1, -4 };
    //int nums[] = { 0, 0, 0 };
    //int nums[] = { -1, 0, 1, 0 };
    int nums[] = {-2,0,0,2,2};
    int **triplets = threeSum2(nums, sizeof(nums) / sizeof(*nums), &count);
    for (i = 0; i < count; i++) {
        printf("%d %d %d\n", triplets[i][0], triplets[i][1], triplets[i][2]);
    }

    return 0;
}
