/*

Given a string, determine if a permutation of the string could form a palindrome.
For example,
"code" -> False, "aab" -> True, "carerac" -> True.
Understand the problem:
The problem can be easily solved by count the frequency of each character using a hash map. The only thing need to take
special care is consider the length of the string to be even or odd. 
  -- If the length is even. Each character should appear exactly times of 2, e.g. 2, 4, 6, etc..
  -- If the length is odd. One and only one character could appear odd times. 
*/

bool canPermutePalindrome(string s) {
    bitset<256> b;
    for (char c : s)
        b.flip(c);
    return b.count() < 2;
}
