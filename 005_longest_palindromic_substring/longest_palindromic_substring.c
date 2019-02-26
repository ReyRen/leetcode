#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

static int manacher(char *s, char output[])
{
    int i, j;
    char s2[3000] = { '\0' };

    s2[0] = '$';
    for (i = 0; s[i] != '\0'; i++) {
        s2[(i<<1)+1] = '#';
        s2[(i<<1)+2] = s[i];
    }
    s2[(i<<1)+1] = '#';
    int len = (i<<1)+2;
    s2[len] = '\0';
    
    int p[3000] = { 0 }; // 以s2中某一点为中心的回文半径
    int id = 0; // 回文的中心点
    int limit = 0; // 最长回文的右边界点
    int maxLen = 0; // 最大回文长度
    int maxId = 0; // 最长回文的中心点
    for (i = 1; i < len; i++) {
        if (i < limit) {
            p[i] = min(p[2*id-i], limit-i);
        } else {
            p[i] = 1;
        }
        
        while (s2[i+p[i]] == s2[i-p[i]]) {
            p[i]++;
        }
        
        if (i+p[i] > limit) {
            limit = i+p[i];
            id = i;
        }
        if (maxLen < p[i]-1) {
            maxLen = p[i]-1;
            maxId = i;
        }
    }
    
    for (j = 0, i = maxId - maxLen; i <= maxId+maxLen; i++) {
        if (s2[i] != '#') {
            output[j++] = s2[i];
        }
    }
    return maxLen;
}

static char *longestPalindrom(char *s)
{
    int i;
    if (s == NULL) {
        return NULL;
    }

    int len = strlen(s);
    if (len <= 1) {
        return s;
    }

    char *palindrome = malloc(2000);
    memset(palindrome, 0, sizeof(palindrome));

    int size = manacher(s, palindrome);
    palindrome[size] = '\0';
    return palindrome;
}

static int expandAroundCenter(char *s, int len, int l, int r) {
	while (l >=0 && r < len && s[l] == s[r]) {
		l--;
		r++;
	}
	return r - l - 1;  /* r - l + 1 - 2 */
}

//brute force. 以每个元素为中间元素, 同时从左右出发. 时间O(n^2)
static char *longestPalindrom2(char *s)
{
	int i, max, n1, n2, begin=0, end=0;
	int len = strlen(s);
	for(i=0;i<len;++i){
		n1 = expandAroundCenter(s, len, i, i);
		n2 = expandAroundCenter(s, len, i, i+1);
		max = n1 > n2 ? n1 : n2;
		if (max > end - begin) {
			begin = i - (max - 1)/2;
			end = i + max/2;
		}
	}
	i = end - begin + 1;
	char *ret = malloc(sizeof(char)*i);
	strncpy(ret, s+begin, i);
	ret[i] = '\0';
	return ret;
}

//dp.  todo...
static char *longestPalindrom3(char *s)
{
	int i, j, left = 0, right = 0;
	int len = strlen(s);
	int **dp = (int **)malloc(sizeof(int *) * len);
	for(i=0; i<len; ++i){
		dp[i] = malloc(sizeof(int) * len);
		memset(dp[i], 0, sizeof(int)*len);
	}
	for (i = 0; i < len; ++i) {
		for (j = 0; j < i; ++j) {
			dp[j][i] = (s[i] == s[j] && (i - j < 2 || dp[j + 1][i - 1]));
			if (dp[j][i] && len < i - j + 1) {
				len = i - j + 1;
				left = j;
				right = i;
			}
		}
		dp[i][i] = 1;
	}
	i = right - left + 1;
	char *ret = malloc(sizeof(char)*i);
	strncpy(ret, s+left, i);
	ret[i] = '\0';
	return ret;
}

int main(int argc, char **argv)
{
	//./test babad  cbbd  aaaaa abcdef
    if (argc != 2) {
        fprintf(stderr, "Usage: ./test string\n");
        exit(-1);
    }
    printf("%s\n", longestPalindrom3(argv[1]));
    return 0;
}
