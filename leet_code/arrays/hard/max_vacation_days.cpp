/*

Maximum vacation days

refer leet code

*/


//Alexander (75 %)
class Solution {
public:
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        int n = days.size(), k = days[0].size(); // n city , k weeks
        vector<vector<int>> dp(n, vector<int>(k, 0)); // dp[i][j] - max days play if you spent week j in city i;
        for (int j = k - 1; j >= 0; j--) {
            for (int i = 0; i < n; i++) {
                dp[i][j] = days[i][j];
                for (int i1 = 0; i1 < n && j < k - 1; i1++) {
                    if (flights[i][i1] || i == i1)
                        dp[i][j] = max(dp[i][j], days[i][j] + dp[i1][j + 1]);
                }
            }
        }
        int maxplay = dp[0][0];
        for (int i = 1; i < n; i++) {
            if (flights[0][i]) {
                maxplay = max(maxplay, dp[i][0]);
            }
        }
        return maxplay;
    }
};

//99 %
class Solution {
public:
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        int nCities = flights.size(), nWeeks = days[0].size();
        
        vector<vector<int>> graphs(nCities,vector<int>{});
        for(int from=0; from<nCities; ++from) {
            for(int to=0; to<nCities; ++to) {
                if(flights[from][to] || from==to)
                    graphs[from].push_back(to);
            }
        }
        
        //max days (pair.first) so far for city (pair.seccond)
        priority_queue<pair<int,int>> maxDays;
        maxDays.push({0,0});
        
        for(int week=0; week<nWeeks; ++week) {
            priority_queue<pair<int,int>> maxDaysNew;
            vector<bool> visited(nCities, false);
            while(maxDaysNew.size()<nCities && !maxDays.empty()) {
                int cityFrom = maxDays.top().second, dayFrom = maxDays.top().first;
                maxDays.pop();
                
                for(int cityTo : graphs[cityFrom]) {
                    if(!visited[cityTo]) {
                        maxDaysNew.push({dayFrom+days[cityTo][week], cityTo});
                        visited[cityTo] = true;
                    }
                }
            }
            
            swap(maxDays, maxDaysNew);
        }
        
        
        return maxDays.top().first;
        
        
    }
};

//faster DP soln
class Solution {
public:
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        if (days.empty()) return 0;
        int m = days.size(), n = days[0].size();
        vector<int> dp(m, -1);
        dp[0] = 0;
        for (int k = 0; k < n; ++k) {
            vector<int> next(m, -1);
            for (int i = 0; i < m; ++i) {
                if (dp[i] == -1) continue;
                for (int j = 0; j < m; ++ j) {
                    if (i == j || flights[i][j]) {
                        next[j] = max(next[j], dp[i]+days[j][k]);
                    }
                }
            }
            swap(dp, next);
        }
        return *max_element(dp.begin(), dp.end());
    }
};
