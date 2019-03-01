#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void num2char(char **num, int bit, int n)
{
    int i;
    char low, mid, high;
    char *p = *num;

    switch (n) {
    case 2:
        low = 'C';
        mid = 'D';
        high = 'M';
    break;
    case 1:
        low = 'X';
        mid = 'L';
        high = 'C';
    break;
    case 0:
        low = 'I';
        mid = 'V';
        high = 'X';
    break;
    }

    if (bit > 0) {
        switch (bit) {
        case 1:
        case 2:
        case 3:
            for (i = 0; i < bit; i++) {
                *p++ = low;
            }
            break;
        case 4:
            *p++ = low;
            *p++ = mid;
            break;
        case 5:
            *p++ = mid;
            break;
        case 6:
        case 7:
        case 8:
            *p++ = mid;
            for (i = 5; i < bit; i++) {
                *p++ = low;
            }
            break;
        case 9:
            *p++ = low;
            *p++ = high;
            break;
        }
    }

    *num = p;
}

static char roman_numeral[64];

static char *intToRoman(int num)
{
    char *p = &roman_numeral[0];
    int thousand_bit = num / 1000;
    int hundred_bit = (num % 1000) / 100;
    int ten_bit = (num % 100) / 10;
    int one_bit = num % 10;
    int i;

    memset(roman_numeral, 0, sizeof(roman_numeral));

    if (thousand_bit > 0) {
        if (thousand_bit < 4) {
            for (i = 0; i < thousand_bit; i++) {
                *p++ = 'M';
            }
        }
    }

    num2char(&p, hundred_bit, 2);
    num2char(&p, ten_bit, 1);
    num2char(&p, one_bit, 0);

    return roman_numeral;
}

//分为四类，100到300一类，400一类，500到800一类，900最后一类
static char *intToRoman2(int num)
{
}

//建立一个数表，每次通过查表找出当前最大的数，减去再继续查表
static char *intToRoman3(int num)
{
}

//直接按位查表，时间复杂度O(1)
static char *intToRoman4(int num)
{
#define ROMAN_SIZE 20
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
    printf("%s\n", intToRoman2(atoi(argv[1])));
    return 0;
}
