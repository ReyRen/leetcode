/*
 * 3. Longest Substring Without Repeating Characters
 * 
 * Given a string, find the length of the longest substring without repeating characters.
 *
 * Example 1:
 *
 * Input: "abcabcbb"
 * Output: 3 
 * Explanation: The answer is "abc", with the length of 3. 
 * Example 2:
 *
 * Input: "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 * Example 3:
 *
 * Input: "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3. 
 *              Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 *
 * Difficulty: Medium
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(x, y) ((x) > (y)) ? (x) : (y);

int lengthOfLongestSubstring1(char* s) {
	int i=0, cur=0, n=0, max_len=0;
	int map[128];
	memset(map, -1, sizeof(int)*128);
	for(; s[i]!='\0'; ++i, ++n) {
		if (map[s[i]] >= cur){
			max_len = max(max_len, i - cur);
			cur = map[s[i]] + 1;
		}
		map[s[i]] = i;

	}
	return max(max_len, n-cur);
}

//brute force
int lengthOfLongestSubstring2(char* s)
{
	int i,j,last_idx=0, cnt=1, max_cnt=0, tmp;
	int len = strlen(s);
	if(len <= 1) return 0;

	for(i=1; i<len; ++i){
		cnt++;
		j = last_idx;
		tmp = 0;
		while(j<i){
			tmp++;
			if(s[j++] == s[i]){
				if(--cnt > max_cnt)
					max_cnt = cnt;
				last_idx = j;
				cnt = cnt - tmp + 1;
				break;
			}
		}
	}
	return max(max_cnt, cnt);
}

int main(int argc, char **argv)
{
	// ./test bbtablud
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test string\n");
        exit(-1);
    }

    printf("%d\n", lengthOfLongestSubstring1(argv[1]));
    return 0;
}
