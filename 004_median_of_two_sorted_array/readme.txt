4. Median of Two Sorted Arrays

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity
should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.

Example 1:
nums1 = [1, 3]
nums2 = [2]
The median is 2.0

Example 2:
nums1 = [1, 2]
nums2 = [3, 4]
The median is (2 + 3)/2 = 2.5

Difficult: hard

========================
分析: 查找中位数 (其实这道题是经典的寻找第K大数)

如果输入[1,3] [7,8], 那么结果是: (3+7)/2 = 5.
如果输入[4,5] [1,2,3,4,5,6,7], 结果是: 4.

运行时间要求O(log (m+n)), 所以不能用merge成一个数组再查找的方式. 
可以考虑二分查找, 分块查找这些时间复杂度是logn的查找算法.

2个排序数组, 找中位数, 要求时间复杂度 O(log (m+n)). 相当于求第k大的数.
1> 直接merge, 然后求第k大, O(m+n). 空间复杂度O(m+n)不合题意.
2> 和直接merge类似, 两个指针分别指向各个数组, 然后根据当前值比较2个数组的指针. 
     比如: 用一个计数器, 记录当前已经找到第m大的元素. 同时我们使用两个指针pa, pb, 
	 分别指向A和B数组的第一个元素, 使用类似于merge sort的原理, 如果数组A当前元素小, 那么
 	 pa++, m++, 如果B当前元素小, 那么pb++, m++.最终当m等于k的时候, 就得到了答案. 时间
 	 O(k), 空间O(1). 但是, 当k接近m+n时候, 时间还是O(m+n). 本质还是方法一的merge操作. 
3> 用第k大元素的作为index为 k/2. 然后比较A,B2个数组的元素, 删掉小的一半.

对于第3种思路:
AB的元素个数都大于k/2, 将A的第k/2个元素和B的第k/2个元素比较, 有如下情况:
A[k/2-1] == B[k/2-1] 找到了第k大元素, 直接返回A[k/2-1] 或 B[k/2-1].
A[k/2-1]  > B[k/2-1], 删去较小的B的一半(k/2)元素
A[k/2-1]  < B[k/2-1], 删去较小的A的一半(k/2)元素
如果A[k/2-1]  < B[k/2-1], 意味着A[0]到A[k/2-1]肯定在 A U B (A并B集)的top k元素的范围内.
换句话说, A[k/2-1]不可能大于A U B的第k大元素. 因此, 我们可以放心的删除A数组的这k/2个元素.
同理, 当A[k/2-1]  > B[k/2-1], 可以删除B数组的k/2个元素
故, 做dfs深搜, 终止条件:
A或B为空, 返回B[k-1]或A[k-1]
k==1, 返回min(A[0],B[0])
A[k/2-1] == B[k/2-1], 返回A[k/2-1] 或 B[k/2-1]
