# string-algorithm-tries
Notation. For a string s, |s| denotes its length.

You have to implement a data structure which, at any point of time, maintains a collection S of distinct bit strings, where each bit string is of length exactly 32 bits. 

Your data structure is initially empty. Further, it should support the following four operations:

insert(b : bit string of length 32):
	Check if b is in set S. 
If yes, return 0.
	If no, add b to set S and return 1.

remove(b: bit string of length 32):
	Check if b is in set S. 
If no, return 0.
	If yes, delete b from set S and return 1.

search1(p : (pattern) bit string of length at most 32):

Consider the set T(p, S) of all pairs (i, s) such that:

(i) 1<=i<=(32-|p|+1),
(ii) bit string s is currently in set S, and
(ii) the substring of s from location i to (i+|p|-1) matches pattern p.	

	The return value of the function is the cardinality |T(p,S)| of this set.


Note. The pattern p in the next search function, search2, can have one or more `?’ (wildcard) characters. If a character in the pattern is `?’ (the wildcard character), then it matches any alphabet in {0,1}. For example, let p=”?0??10” and s=”001111010”, then the longest prefix of s that matches a prefix of p is “00111”.





search2(p : a (pattern) string of length at most 32 over the alphabet {0, 1, ?}):

	For a string s currently in set S, let L(s,p) denote the maximum length prefix of s that 
matches a prefix of p. 

(Clearly, 0 <= L(s,p) <= |p|. For the example above, s=”001111010”,  p=”?0??10”, and
L(s,p)=5.)

Suppose set S currently has n (distinct) bit strings s_1, s_2, …, s_n. Then function 
search2 outputs a single integer equal to the value of the following sum:

		L(s_1,p) + L(s_2, p) + … + L(s_n, p)

Requirements.

Running time. The maximum number of operations in the RAM model allowed for each of the above functions are:
	
Function
Maximum number of operations (in RAM model)
insert
4000
remove
4000
search1
4000
search2
(4000)*(1+L), where L is the integer output by search2.

Note that the above table gives the maximum number of RAM operations, there are no hidden multiplicative constants (due to order notation) in these bounds on the running times.

