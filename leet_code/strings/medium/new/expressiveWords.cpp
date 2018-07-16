/*

Sometimes people repeat letters to represent extra feeling, such as "hello" -> "heeellooo", "hi" -> "hiiii".
For some given string S, a query word is stretchy if it can be made to be equal to S by extending some groups.  
Formally, we are allowed to repeatedly choose a group (as defined above) of characters c, and add 
some number of the same character c to it so that the length of the group is 3 or more.  Note
that we cannot extend a group of size one like "h" to a group of size two like "hh" - all
extensions must leave the group extended - ie., at least 3 characters long.

Given a list of query words, return the number of words that are stretchy. 



Example:
Input: 
S = "heeellooo"
words = ["hello", "hi", "helo"]
Output: 1
Explanation: 
We can extend "e" and "o" in the word "hello" to get "heeellooo".
We can't extend "helo" to get "heeellooo" because the group "ll" is not extended.
*/
