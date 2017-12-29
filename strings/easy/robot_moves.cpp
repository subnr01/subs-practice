
/*
The move sequence is represented by a string. And each move is represent by a character. The valid robot moves are 
R (Right), L (Left), U (Up) and D (down). The output should be true or false representing whether the robot makes a circle.

Example 1:
Input: "UD"
Output: true

Example 2:
Input: "LL"
Output: false

*/

class Solution {
public:
    bool judgeCircle(string moves) {
    int hm = 0;
    int vm = 0;
    char ch;
    for ( int i = 0; i < moves.size(); i++){
        switch(moves[i]) {
            case 'L': hm++; break;
            case 'R': hm--; break;
            case 'U': vm++; break;
            case 'D': vm--; break;
        }
    }
    return hm == 0 && vm == 0;
}
};

