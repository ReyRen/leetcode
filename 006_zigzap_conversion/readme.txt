6. ZigZag Conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I

Difficulty: Medium

以字符串: 数字0~22,  给定行数为5,走之字形如下:
 0 | - | - | - | 8 | - | - | - | 16| - | -  |
---+---+---+---+---+---+---+---+---+---+----+--
 1 | - | - | 7 | 9 | - | - |15 | 17| - | +  |
---+---+---+---+---+---+---+---+---+---+----+--
 2 | - | 6 | - | 10| - |14 | - | 18| - | 22 |   
---+---+---+---+---+---+---+---+---+---+----+--
 3 | 5 | - | - | 11|13 | - | - | 19| 21| -  |
---+---+---+---+---+---+---+---+---+---+----+--
 4 | - | - | - | 12| - | - | - | 20| - | -  |

1) 0,1,2,3,4,5,6,7.这是一次排列, [8~16]是前面的重复. [0~7]的长度永远是 2n-2 
   (想法是你试想把所有0-7这些列压缩成两列，两边手挤一下，第二列永远的"第一行"和
    "最后一行"少1个字)
   第一行和最后一行下标间隔都是interval = n*2-2 = 8 (这里n是行数5)
   利用这个规律，可以按行填字，第一行和最后一行，就是按照2n-2的顺序一点点加的。
   注意竖线之间是等距的, [0~1]与[8~12]与[16~20]等距2n-2=8

2) 中间行的间隔是周期性的,第i行的间隔是: 
  interval–2*i,  2*i,  interval–2*i, 2*i, interval–2*i, 2*i, ... 
  第1行: 8-2*1, 即7与1之间的间隔是6.
  第2行: 2*i, 即6与2的间隔是4.
  第3行: 8-2*i, 即5与3的间隔2.

  竖线列[0~1] [8~12]间的元素, 每行只有1个. 1-9之间只有7, 2-10之间只有6.

  斜线上每个元素的位置为j + (2*nRows-2) - (2*i), 其中j为前一个竖线元素的列数, i为当前行数.
  比如上图当n=5时, 那个7,它的位置为 1 + (2*5-2) - (2*1) = 7  (第一个1是[0~1]这条竖线的列号)

char* convert(char* s, int numRows) {
	if(!s || numRows == 1) return s;
	int len = strlen(s), k = 0, interval = (numRows<<1)-2;
	char *res = malloc(sizeof(char)*len+1);

	for(int j = 0; j < len ; j += interval)//处理第一行
		res[k++] = s[j];
	for(int i = 1; i < numRows-1; i++){ //处理中间行
		int inter = (i<<1);
		for(int j = i; j < len; j += inter){
			res[k++] = s[j];
			inter = interval - inter;           
		}
	}
	for(int j = numRows-1; j < len ; j += interval)//处理最后一行
		res[k++] = s[j];

	res[len] = '\0';
	return res;
}
