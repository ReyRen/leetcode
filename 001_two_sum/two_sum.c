/*
 * Two Sum
 * Given an array of integers, return indices of the two numbers such that they
 * add up to a specific target.
 * You may assume that each input would have exactly one solution, and you may
 * not use the same element twice.
 *
 * Example:
 *
 * Given nums = [2, 7, 11, 15], target = 9,
 *
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 *
 * Difficulty: Easy
 */
test
test
#include <stdio.h>
#include <stdlib.h>

struct object {
    int val;
    int index;
    int idx;
};

static int compare(const void *a, const void *b)
{
    return ((struct object *) a)->val - ((struct object *) b)->val;
}

static int * twosum1(int *nums, int numsSize, int target)
{
    int i, j;
    struct object *objs = malloc(numsSize * sizeof(*objs));
    for (i = 0; i < numsSize; i++) {
        objs[i].val = nums[i];
        objs[i].index = i;
    }
    qsort(objs, numsSize, sizeof(*objs), compare);
    
    int *results = malloc(2 * sizeof(int));
    i = 0;
    j = numsSize - 1;
    while (i < j) {
        int diff = target - objs[i].val;
        if (diff > objs[j].val) {
            while (++i < j && objs[i].val == objs[i - 1].val) {}
        } else if (diff < objs[j].val) {
            while (--j > i && objs[j].val == objs[j + 1].val) {}
        } else {
            results[0] = objs[i].index;
            results[1] = objs[j].index;
            return results;
        }
    }
    return NULL;
}

//brute force
static int * twosum2(int *nums, int numsSize, int target)
{
	int i, j, *ret;
	if (!nums || numsSize < 2) return NULL;

	for(i=0; i<numsSize; ++i){
		for(j=numsSize-1; j>i; --j){
			//printf("i: %d (%d) j: %d (%d)\n", i, nums[i], j, nums[j]);
			if(target == (nums[i] + nums[j])){
				ret = malloc(2*sizeof(int));
				ret[0] = i; ret[1] = j;
				return ret;
			}
		}
	}
	return NULL;
}

int main(void)
{
    int nums[] = {-1, -2, -3, -4, -5};
    int target = -8;
    //int nums[] = {0,4,3,0};
    //int target = 0;
    //int nums[] = { 3, 2, 3 };
    //int target = 6;
    int count = sizeof(nums) / sizeof(*nums);
    int *indexes = twosum1(nums, count, target);
    if (indexes != NULL) {
        printf("%d %d\n", indexes[0], indexes[1]);
    } else {
        printf("Not found\n");
    }

    return 0;
}
