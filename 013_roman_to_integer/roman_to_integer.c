#include <stdio.h>
#include <stdlib.h>

inline int map(const char c) {
	switch (c) {
		case 'I': return 1;
		case 'V': return 5;
		case 'X': return 10;
		case 'L': return 50;
		case 'C': return 100;
		case 'D': return 500;
		case 'M': return 1000;
		default: break;
	}
	return 0;
}

int romanToInt(char *s)
{
	int i, prev, cur;
	int ret = map(s[0]);
	for(i=1; s[i] != '\0'; ++i){
		prev = map(s[i-1]);
		cur = map(s[i]);
        //if left<right such as : IV(4), XL(40), IX(9) ...
		if(cur > prev){
			ret = ret - prev + (cur - prev);
		}else{
			ret += cur;
		}
	}
	return ret;
}

int main(int argc, char **argv)
{
	// ./teset MCMXCIV 1994    LVIII 58   III 3   IV 4
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test roman\n");
        exit(-1);
    }
    printf("%d\n", romanToInt(argv[1]));
    return 0;
}
