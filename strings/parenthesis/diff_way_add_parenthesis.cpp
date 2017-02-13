/*
Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.


Example 1
Input: "2-1-1".

((2-1)-1) = 0
(2-(1-1)) = 2
Output: [0, 2]


Example 2
Input: "2*3-4*5"

(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
Output: [-34, -14, -10, -10, 10]

*/

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        map<string, vector<int>> cache;
        return diffWaysToCompute(input, 0, input.size()-1, cache);
    }
private:
    vector<int> diffWaysToCompute(string& input, int start, int end, map<string, vector<int>>& cache) {
        string key=to_string(start)+to_string(end);
        if(cache.count(key)) return cache[key];
        vector<int> result;
        int num=0;
	    for(int i=start; i<=end; ++i) {
	        if(input[i]!='+' && input[i]!='-' && input[i]!='*')
	            num=num*10+(input[i]-'0');
		    else{ 
    		    vector<int> left=diffWaysToCompute(input, start, i-1, cache);
    		    vector<int> right=diffWaysToCompute(input, i+1, end, cache);
    		    for(auto l:left){
    		        for(auto r: right){
    		            if(input[i]=='+')
    		                result.push_back(l+r);
    		            else if(input[i]=='-')
    		                result.push_back(l-r);
    		            else if(input[i]=='*')
    		                result.push_back(l*r);
    		        }
    		    }
		    }    
        }
        if(result.size()==0) result.push_back(num); //only single number
        return cache[key]=result;
    }
};
