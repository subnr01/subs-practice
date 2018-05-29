/*
Given a non-empty string s and an integer k, rearrange the string such that the same characters 
are at least distance k from each other.

All input strings are given in lowercase letters. If it is not possible to rearrange the string, 
return an empty string "".

Example 1:
s = "aabbcc", k = 3

Result: "abcabc"

The same letters are at least distance 3 from each other.
Example 2:
s = "aaabc", k = 3 

Answer: ""

It is not possible to rearrange the string.
Example 3:
s = "aaadbbcc", k = 2

Answer: "abacabcd"

Another possible answer is: "abcabcda"

The same letters are at least distance 2 from each other.

*/

//heap

class Solution {
public:
    string rearrangeString(string str, int k) {
        if(k == 0) return str;
        int length = (int)str.size(); 
        
        string res;
        unordered_map<char, int> dict;
        priority_queue<pair<int, char>> pq;
        
        for(char ch : str) dict[ch]++;
        for(auto it = dict.begin(); it != dict.end(); it++){
            pq.push(make_pair(it->second, it->first));
        }
        
        while(!pq.empty()){
            vector<pair<int, char>> cache; //store used char during one while loop
            int count = min(k, length); //count: how many steps in a while loop
            for(int i = 0; i < count; i++){
                if(pq.empty()) return "";
                auto tmp = pq.top();
                pq.pop();
                res.push_back(tmp.second);
                if(--tmp.first > 0) cache.push_back(tmp);
                length--;
            }
            for(auto p : cache) pq.push(p);
        }
        return res;
    }
    
    
};


//fastest hash table
class Solution {
public:
    string rearrangeString(string s, int k) {
        int n=s.size(); 
        if(n==0) return ""; 
        
        int char_map[26]={0}; 
        
        for(auto c:s) char_map[c-'a']++; 
        multimap<int, char, greater<int>> count_map; 
        for(int i=0; i<26; i++) count_map.emplace(char_map[i], i+'a'); 
        
        int max_cnt=count_map.begin()->first, pos=0, mct=0; 
        vector<string> arr_str(max_cnt); 
        
        for(auto iter=count_map.begin(); iter!=count_map.end(); iter++){
            if(iter->first==max_cnt) mct++;
            
            for(auto i=0; i<iter->first; i++, pos=(pos+1)%max(iter->first, max_cnt-1)){
                arr_str[pos].push_back(iter->second); 
            } 
        }
        
        if((max_cnt-1)*k+mct > n) return ""; 
        
        string res; 
        
        for(auto s:arr_str) res+=s; 
        
        return res; 
        
        
        
    }
};

//faster heap soln
class Solution {
public:

    using nextLoc = pair<char,int>;
    using vc = vector<char>;
    
    string rearrangeString(string s, int k) {
        
        vector<int> count(26,0);
        
        auto comp = [&](const char &c1, const char &c2)->bool{
            if(count[c1 - 'a'] < count[c2 - 'a'] || (count[c1 - 'a'] == count[c2 - 'a'] && c1 > c2)){
                return true;
            }
        
            return false;
        };
        
        priority_queue<char,vc,decltype(comp)> pq(comp);
        deque<nextLoc> wait;
        string result;
    
        for(auto &c : s){
            count[c - 'a']++;
        }
        
        for(int i = 0; i < count.size(); ++i){
            if(count[i]){
                pq.push(i + 'a');
            }
        }
        
        while(!pq.empty() || !wait.empty()){
            
            if(!wait.empty()){
                
                if(wait.front().second <= result.size()){
                    pq.push(wait.front().first);
                    wait.pop_front();
                }
            }
        
            if(pq.empty()){
                return "";
            }
            
            auto top = pq.top();
            pq.pop();
            result.push_back(top);
            count[top - 'a']--;
            
            if(count[top - 'a'] > 0){
                wait.push_back({top,result.size() + k - 1});
            }
        }
    
        return result;
    }
        
};
