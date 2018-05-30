/*
You have a number of envelopes with widths and heights given as a pair of integers (w, h).
One envelope can fit into another if and only if both the width and height of one envelope 
is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)
Example:
Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of
envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).

*/


//Look at discussion
//99%
class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        sort(envelopes.begin(),envelopes.end(),[](const pair<int,int>& a, const pair<int,int>& b){return a.first < b.first || (a.first == b.first && a.second > b.second);});
        vector<int> height;
        for(auto pr: envelopes){
            height.push_back(pr.second);
        }
        vector<int> patience;
        for(int h: height){
            auto it = lower_bound(patience.begin(),patience.end(),h);
            if(it!=patience.end())*it = h;
            else patience.push_back(h);
        }
        return patience.size();
    }
};



