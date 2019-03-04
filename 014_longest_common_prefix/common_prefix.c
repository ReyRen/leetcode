#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static char* longestCommonPrefix1(char** strs, int strsSize)
{
    int i, count = 0;
    char *result = malloc(1000);
    while (strsSize > 0) {
        char c = strs[0][count];
        for (i = 1; i < strsSize; i++) {
            if (c != strs[i][count]) break;
        }
        if (i == strsSize && c != '\0') {
            result[count++] = c;
        } else {
            break;
        }
    }
    result[count++] = '\0';
    return result;
}

static char* longestCommonPrefix2(char** strs, int strsSize)
{
	int i, j;
	if(strsSize == 0) return "";

	int len = strlen(strs[0]) - 1;
	for(i=1; i<strsSize; ++i){
		for(j=0; j <= len; ++j)
			if(strs[i][j] != strs[0][j])
				len = j - 1;
	}
	strs[0][len+1] = '\0';
	return strs[0];
}

int main(int argc, char **argv)
{
    printf("%s\n", longestCommonPrefix2(argv + 1, argc - 1));
    return 0;
}
