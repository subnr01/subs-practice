
/*
On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, and an empty square represented by 0.

A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

Given a puzzle board, return the least number of moves required so that the state of the board is solved. 
If it is impossible for the state of the board to be solved, return -1.
Examples:

Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.
Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.
Input: board = [[4,1,2],[5,0,3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4,1,2],[5,0,3]]
After move 1: [[4,1,2],[0,5,3]]
After move 2: [[0,1,2],[4,5,3]]
After move 3: [[1,0,2],[4,5,3]]
After move 4: [[1,2,0],[4,5,3]]
After move 5: [[1,2,3],[4,5,0]]
Input: board = [[3,2,4],[1,5,0]]
Output: 14

*/

//4 ms
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& b) {
        string target="123450",
        begin=to_string(b[0][0])+to_string(b[0][1])+to_string(b[0][2])
             +to_string(b[1][0])+to_string(b[1][1])+to_string(b[1][2]);
        vector<vector<int>> nextMoves{{1,3},{0,2,4},{1,5},{0,4},{1,3,5},{2,4}};
        unordered_set<string> visited{begin};
        queue<string> q; q.push(begin);
        for (int depth=0; !q.empty(); ++depth){
            int size=(int)q.size();
            for (int i=0; i<size; ++i){
                auto curr=q.front(); q.pop();
                if (curr==target) return depth;
                int zero=(int)curr.find("0");
                for (auto next: nextMoves[zero]){
                    auto candidate=curr;
                    swap(candidate[zero],candidate[next]);
                    if (visited.find(candidate)==visited.end()){
                        visited.insert(candidate);
                        q.push(candidate);
                    }
                }
            }
        }
        return -1;
    }
};


//Another soln
class Solution {
public:
    int slidingPuzzle(vector<vector<int> >& board) {
        int start = encode_board(board);
        int target = encode_board(Solution::_target_board);
        int depth = 0;
        std::set<int> visited;
        std::queue<int> que;
        que.push(start);
        que.push(0);
        while (! que.empty()) {
            int curr = que.front();
            // std::cout << curr << std::endl;
            visited.insert(curr);
            que.pop();
            if (curr == target) {
                return depth;
            } else if (curr == 0) {
                ++depth;
                if (! que.empty()) {
                    que.push(0);
                }
                continue;
            }

            auto tmp = decode_board(curr);
            int row = 0;
            int col = 0;
            bool found = false;
            for (row = 0; row < 2; ++row) {
                for (col = 0; col < 3; ++col) {
                    if (tmp[row][col] == 0) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }

            for (const auto& direction: Solution::_directions) {
                if (row + direction.first >=0 && row + direction.first < 2 &&
                        col + direction.second >=0 && col + direction.second < 3) {
                    std::swap(tmp[row][col], tmp[row + direction.first][col + direction.second]);
                    int next = encode_board(tmp);
                    if (visited.count(next) == 0) {
                        que.push(next);
                        // std::cout << "children: " << next << std::endl;
                    }
                    std::swap(tmp[row][col], tmp[row + direction.first][col + direction.second]);
                }
            }
        }
        return -1;
    }
protected:
    static const std::vector<std::vector<int> > _target_board;
    static const std::vector<std::pair<int, int> > _directions;

    static int encode_board(const std::vector<std::vector<int> >& board) {
        int ret = 0;
        for (const auto& row: board) {
            for (auto val: row) {
                // std::cout << val << std::endl;
                ret = 10 * ret + val;
            }
        }
        return ret;
    }

    static std::vector<std::vector<int> > decode_board(int code) {
        std::vector<std::vector<int> > ret(2, std::vector<int>(3, 0));
        for (int row=1; row>=0; --row) {
            for (int col=2; col>=0; --col) {
                ret[row][col] = code % 10;
                code /= 10;
            }
        }
        return ret;
    }
};


const std::vector<std::vector<int> > Solution::_target_board = {{1, 2, 3}, {4, 5, 0}};
const std::vector<std::pair<int, int> > Solution::_directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
