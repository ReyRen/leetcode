#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROMAN_SIZE 20

/* 分为四类，100到300一类，400一类，500到800一类，900最后一类
 * 100 - C 200 - CC 300 - CCC
 * 400 - CD
 * 500 - D 600 - DC 700 - DCC 800 - DCCC
 * 900 - CM
 */
static char *intToRoman2(int num)
{
	char roman[] = {'M',  'D', 'C', 'L', 'X', 'V', 'I'};
	int  value[] = {1000, 500, 100, 50,  10,  5,   1};
	int i, j, x, len = 0;
	char *p;
	char *ret = (char *)malloc(sizeof(char) * ROMAN_SIZE);
	p = ret;
	for(i=0; i<7; i+=2){ //step is 2 on every loop
		x = num / value[i];
		if (x < 4) {
			for(j=1; j<=x; ++j)memcpy(ret++, roman+i, 1);
		} else if (x == 4) {
			memcpy(ret++, roman+i, 1);
			memcpy(ret++, roman+i-1, 1);
		} else if (x > 4 && x < 9) {
			memcpy(ret++, roman+i-1, 1);
			for (j = 6; j <= x; ++j) memcpy(ret++, roman+i, 1);
		} else if (x == 9) {
			memcpy(ret++, roman+i, 1);
			memcpy(ret++, roman+i-2, 1);
		}
		num %= value[i];
	}
	*ret = '\0';
	return p;
}

//建立一个数表，每次通过查表找出当前最大的数，减去再继续查表
static char *intToRoman3(int num)
{
	int i;
	int  val[13] = {1000, 900, 500, 400,  100,  90,  50,  40,   10,   9,   5,   4,    1};
	char *str[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	int strSize[13] = {1,  2,    1,   2,    1,   2,   1,    2,    1,   2,    1,   2,    1};
	char *ret = (char *)malloc(sizeof(char) * ROMAN_SIZE);
	char *p = ret;
	for (i = 0; i < 13; ++i) {
		while (num >= val[i]) {
			num -= val[i];
			memcpy(ret, str[i], strSize[i]);
			ret += strSize[i];
		}
	}
	*ret = '\0';
	return p;
}

//直接按位查表，时间复杂度O(1)
static char *intToRoman4(int num)
{
	int n;
	char *ret = (char *)malloc(sizeof(char) * ROMAN_SIZE);
	char* v1[] = {"", "M", "MM", "MMM"};
	char* v2[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
	char* v3[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
	char* v4[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
	n = snprintf(ret, ROMAN_SIZE, "%s%s%s%s", v1[num/1000], v2[(num%1000)/100], v3[(num%100)/10], v4[num%10]);
	ret[n] = '\0';
	return ret;
}

int main(int argc, char **argv) {
	//./test 58 LVIII   9 IX    1994 MCMXCIV
    printf("%s\n", intToRoman3(atoi(argv[1])));
    return 0;
}
