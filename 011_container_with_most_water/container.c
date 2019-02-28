#include <stdio.h>
#include <stdlib.h>

static int maxArea(int* height, int heightSize)
{
    int min = 0, max = heightSize - 1;
    int area_max = 0;
    while (min < max) {
        int area = (max - min) * (height[min] < height[max] ? height[min] : height[max]);
        area_max = area > area_max ? area : area_max;
        if (height[min] < height[max]) {
            while (++min < max && height[min] <= height[min - 1]) {
                continue;//优化, 不计算更小值
            }
        } else {
            while (min < --max && height[max] <= height[max + 1]) {
                continue;//优化, 不计算更小值
            }
        }
    }
    return area_max;
}


//注意maxArea1和maxArea2本质是一样的. 
//double pointer
static int maxArea1(int* height, int heightSize)
{
	int i=0, j=heightSize-1, max=0, t;
	while(i<j){
		if(height[i]>height[j]){
			t = height[j] * (j-i);
			j--;
		} else {
			t = height[i] * (j-i);
			i++;
		}
		if(t > max) max = t;
	}
	return max;
}

//double pointer
static int maxArea2(int* height, int heightSize)
{
	int l=0, r=heightSize-1, max=0, t;
	while(l<r){
		t = (r-l) * ((height[l]>height[r]) ? height [r] : height[l]);
		max = t > max ? t : max;
		if(height[l]>height[r])
			r--;
		else
			l++;
	}
	return max;
}

//brute force
static int maxArea3(int* height, int heightSize)
{
	int i, j, max = 0, t;
	for(i=0; i<heightSize-1; ++i){
		for(j=i+1; j<heightSize; ++j){
			if(height[i] > height[j])
				t = height[j] * (j-i);
			else
				t = height[i] * (j-i);
			if(t > max) max = t;
		}
	}
	return max;
}

int main(int argc, char **argv)
{
	/*input: 1 8 6 2 5 4 8 3 7
	 *output: 49
	 */
    int i, count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }
    printf("%d\n", maxArea2(nums, count));
    return 0;
}
