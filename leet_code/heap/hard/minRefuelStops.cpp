


/*

Example 1:

Input: target = 1, startFuel = 1, stations = []
Output: 0
Explanation: We can reach the target without refueling.
Example 2:

Input: target = 100, startFuel = 1, stations = [[10,100]]
Output: -1
Explanation: We can't reach the target (or even the first gas station).
Example 3:

Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
Output: 2
Explanation: 
We start with 10 liters of fuel.
We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters to 60 liters of gas.
Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
and refuel from 10 liters to 50 liters of gas.  We then drive to and reach the target.
We made 2 refueling stops along the way, so we return 2.

*/


class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) 
    {
        priority_queue<int, vector<int>, less<int>> pq; 
        pq.push(startFuel);
        int gas = 0; 
        int cnt = 0;
        int idx = 0;
        int n = stations.size();
        
        while(!pq.empty()) 
        {
            gas += pq.top(); 
            pq.pop();
            if(gas >= target) {
                return cnt;
            }
            cnt++;
            while(idx < n && gas >= stations[idx][0]) 
            {
                pq.push(stations[idx][1]);  
                idx++;
            }
        }
        return -1;
    }
};
