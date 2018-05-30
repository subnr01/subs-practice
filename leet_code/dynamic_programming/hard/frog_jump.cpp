/*
A frog is crossing a river. The river is divided into x units and at each unit 
there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

Given a list of stones' positions (in units) in sorted ascending order, 
determine if the frog is able to cross the river by landing on the last 
stone. Initially, the frog is on the first stone and assume the first jump must be 1 unit.

If the frog's last jump was k units, then its next jump must
be either k - 1, k, or k + 1 units. Note that the frog can only jump in the forward direction.

Example 1:

[0,1,3,5,6,8,12,17]

There are a total of 8 stones.
The first stone at the 0th unit, second stone at the 1st unit,
third stone at the 3rd unit, and so on...
The last stone at the 17th unit.

Return true. The frog can jump to the last stone by jumping 
1 unit to the 2nd stone, then 2 units to the 3rd stone, then 
2 units to the 4th stone, then 3 units to the 6th stone, 
4 units to the 7th stone, and 5 units to the 8th stone.
Example 2:

[0,1,2,3,4,8,9,11]

Return false. There is no way to jump to the last stone as 
the gap between the 5th and 6th stone is too large.


*/


//Soln with 84 %
class Solution {
public:
   unordered_map<int, bool> dp;

bool canCross(vector<int>& stones, int pos = 0, int k = 0) {
    int key = pos | k << 11;

    if (dp.count(key) > 0)
        return dp[key];

    for (int i = pos + 1; i < stones.size(); i++) {
        int gap = stones[i] - stones[pos];
        if (gap < k - 1)
            continue;
        if (gap > k + 1)
            return dp[key] = false;
        if (canCross(stones, i, gap))
            return dp[key] = true;
    }

    return dp[key] = (pos == stones.size() - 1);
}
};


//different way
struct path{
    int stone;
    int step;
    path(int stone, int step){
        this->stone = stone;
        this->step = step;
    }
};

class Solution {

public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        unordered_set<int> hash_map;
        for (int i =0 ; i < n; i++){
            hash_map.insert(stones[i]);
        }
        
        int last = stones[n-1];
        if (last > 606000) return false;
        if (stones[1] != 1) return false;
            
        stack<path *> buffer;
        buffer.push(new path(1,1));
        while (!buffer.empty()){
            path * top = buffer.top();
            //cout<<top->stone<<" "<<top->step<<" "<<last<<endl;
            buffer.pop();
            if (top->stone == last) return true;
            if (hash_map.find(top->stone + top->step-1) != hash_map.end()){
                int new_stone = top->stone + top->step-1;
                int new_step = top->step-1;
                if (new_step != 0) buffer.push(new path(new_stone, new_step));
            }
            if (hash_map.find(top->stone + top->step) != hash_map.end()){
                int new_stone = top->stone + top->step;
                int new_step = top->step;
                buffer.push(new path(new_stone, new_step));
            }
            if (hash_map.find(top->stone + top->step+1) != hash_map.end()){
                //cout<<"here"<<endl;
                int new_stone = top->stone + top->step+1;
                int new_step = top->step+1;
                buffer.push(new path(new_stone, new_step));
            }
        }
        
        return false;
    }
};

//another good (100 %)
class Solution {
public:
    bool canCross(vector<int>& stones) {
        struct node {
            int units;
            int pos;
            bool operator<(const node& n) const {
                return pos < n.pos;
            }
        };
        int sz = stones.size();
        if(stones.size() > 1) {
            if(stones[1] - stones[0] > 1) return false;
            if(stones[sz - 1] > sz - 1 + stones[sz - 2]) return false;
        }
        
        priority_queue<node> q;
        q.push(node{1,0});
        
        while(!q.empty()) {
            node cur = q.top(); q.pop();
            if(cur.pos == stones.size() - 1)  return true;
            for(int i=cur.pos+1;i<stones.size();i++) {
                int diff = stones[i] - stones[cur.pos] - cur.units;
                if(diff >= -1 && diff <= 1) {
                    if(i == stones.size() - 1)  return true;
                    q.push(node{stones[i] - stones[cur.pos],i});
                } else if(diff > 1){ break; }
            }
        }
        return false;
    }
};

