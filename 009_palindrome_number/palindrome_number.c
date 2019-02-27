#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int reverse(int x)
{
    int y = 0;
    while (x) {
		//判断翻转后是否溢出?
        y = y * 10 + x % 10;
        x /= 10;
    }
    return y;
}
//反转全部数字
static bool isPalindrome(int x)
{
    if (x == 0) {
        return true;
    }
    if (x < 0) {
        return false;
    }
    return x == reverse(x);
}

//反转一半数字
static bool isPalindrome2(int x)
{
	/* 特殊情况：
	 * 如上所述，当 x < 0 时，x 不是回文数。
	 * 同样地，如果数字的最后一位是 0，为了使该数字为回文，
	 * 则其第一位数字也应该是 0
	 * 只有 0 满足这一属性
	 */
	if(x < 0 || (x % 10 == 0 && x != 0)) {
		return false;
	}
    if(x == 0) {
        return true;
    }
			
    int new = 0;
    while (x>new) {
        new = new * 10 + x % 10;
        x /= 10;
    }

	/* 当数字长度为奇数时，我们可以通过 new/10 去除处于中位的数字。
	 * 例如,当输入为 12321 时，在 while 循环的末尾我们可以得到 x = 12，new = 123，
	 * 由于处于中位的数字不影响回文（它总是与自己相等），所以我们可以简单地将其去除。
	 */
	return x == new || x == new/10;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test number\n");
        exit(-1);
    }

    printf("%s\n", isPalindrome2(atoi(argv[1])) ? "true" : "false");
    return 0;
}
