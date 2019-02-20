#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* convert1(char* s, int numRows)
{
    if (numRows <= 1) return s;

    int len = strlen(s);
    char *new_str = malloc(len + 1);    
    char *p = new_str;
    int row = 0;
    for (row = 0; row < numRows; row++) {
        int interval1 = numRows + (numRows - 2) - row * 2;
        int interval2 = 2 * row;
        int flag = 0;
        int i = row;
        while (i < len) {
            *p++ = s[i];
            int delta = 0;
            do {
                delta = flag == 0 ? interval1 : interval2;
                flag = !flag;
            } while (delta == 0);
            i += delta;
        }
    }

    new_str[len] = '\0';
    return new_str;
}

char* convert2(char* s, int numRows)
{
	if(!s || numRows == 1) return s;
	int len = strlen(s), k = 0, interval = (numRows<<1)-2;
	char *res = malloc(sizeof(char)*len+1);

	for(int j = 0; j < len ; j += interval)//handling first line
		res[k++] = s[j];
	for(int i = 1; i < numRows-1; i++){ //handling interval lines
		int inter = (i<<1); //2*i
#if 0 /* both if-else solution are work fine */
		for(int j = i; j < len; j += inter){
			res[k++] = s[j];
			inter = interval - inter;           
		}
#else        
		for(int j = i; j < len; j += interval) {
			res[k++] = s[j];
			int tmp = j + interval - inter;
			if (tmp < len) res[k++] = s[tmp];
		}
#endif

	}
	for(int j = numRows-1; j < len ; j += interval)//handling last line
		res[k++] = s[j];

	res[len] = '\0';
	return res;
}

char* convert3(char* s, int numRows)
{
	if(!s || numRows == 1) return s;
	int len = strlen(s), interval = (numRows<<1)-2;
	char *res = malloc(sizeof(char)*len+1);
	char *p = res;

	for(int i = 0; i < numRows; i++){
		int inter = (i<<1); //2*i
		for(int j = i; j < len; j += interval) {
			*p++ = s[j];
			int tmp = j + interval - inter;
			if (i!=0 && i!=numRows-1 && tmp < len) *p++ = s[tmp];
		}

	}
	res[len] = '\0';
	return res;
}

int main(int argc, char **argv)
{
	/*  ./test "PAYPALISHIRING" 3
	 *  ./test "LEETCODEISHIRING" 4
	 *  ./test "0123456789ABCDEF" 4
	 */
    if (argc < 3) {
        fprintf(stderr, "./test string num\n");
        exit(-1);
    }

    printf("%s\n", convert2(argv[1], atoi(argv[2])));
    return 0;
}
