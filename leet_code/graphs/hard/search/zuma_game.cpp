/*
Think about Zuma Game. You have a row of balls on the table, colored red(R), yellow(Y), blue(B), green(G),
and white(W). You also have several balls in your hand.

Each time, you may choose a ball in your hand, and insert it into the row (including the leftmost place 
and rightmost place). Then, if there is a group of 3 or more balls in the same color touching, remove these balls. Keep doing this until no more balls can be removed.

Find the minimal balls you have to insert to remove all the balls on the table. If you cannot 
remove all the balls, output -1.

Examples:

Input: "WRRBBW", "RB"
Output: -1
Explanation: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW

Input: "WWRRBBWW", "WRBRW"
Output: 2
Explanation: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty

Input:"G", "GGGGG"
Output: 2
Explanation: G -> G[G] -> GG[G] -> empty 

Input: "RBYYBBRRB", "YRBGB"
Output: 3
Explanation: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] -> BB[B] -> empty 

*/

//there is another soln in the discussion, if you do not understand this.

class Solution {
public:
    int findMinStep(string board, string hand) {
        vector<int> c(128);
		for (char x : hand) {
			c[x]++;
		}
		return  aux(board, c);
	}
private:
	int aux(string s, vector<int>& c) {
		if (s.empty()) return 0;
		//worst case, every character needs 2 characters; plus one to make it impossible, ;-)
		int res = 2 * s.length() + 1;
		for (int i = 0; i < s.length();) {
			int j = i++;
			while (i < s.length() && s[i] == s[j]) i++;
			int inc = 3 - i + j;
			if (c[s[j]] >= inc) {
				int used = inc <= 0 ? 0 : inc;
				c[s[j]] -= used;
				int temp = aux(s.substr(0, j) + s.substr(i), c);
				if (temp >= 0) res = min(res, used + temp);
				c[s[j]] += used;
			}
		}
		return res == 2 * s.length() + 1 ? -1 : res;
    }
};
