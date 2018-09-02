/*

*/


class Solution {
    int table[7][7];
public:
    bool solve(string s,int l ,int i,int j){        
        if(!i && l==1)return true;
        if(!table[s[i]-'A'][s[i+1]-'A'])return false;
        int x = table[s[i]-'A'][s[i+1]-'A'];
        while(j>=0 && !((x>>j)&1))j--;
        if(j==-1)return false;
        char temp = s[i];
        s[i]='A'+j;
        if(i==l-2 && solve(s,l-1,0,6))return true;
        else if(i<l-2 && solve(s,l,i+1,6))return true;
        s[i]=temp;
        return solve(s,l,i,--j);
    }
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for(string al:allowed)
            table[al[0]-'A'][al[1]-'A'] |= 1<<(al[2]-'A');
        return solve(bottom,bottom.length(),0,6);
    }
};

//Another soln
class Solution {
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        if(bottom == "") return true;
        map<string, string> lr2t;
        for(auto a: allowed) lr2t[a.substr(0, 2)] += a.substr(2);
        return dfs(bottom, lr2t);
    }
    
private:
    bool dfs(string bottom, const map<string, string> &lr2t){
        if(bottom.size() <= 1) return true;
        vector<string> next = {""};
        for(int i = 0; i < bottom.size()-1; i++){
            vector<string> cur;
            string str = string(1, bottom[i]) + string(1, bottom[i+1]);
            auto itor = lr2t.find(str);
            if(itor == lr2t.end()) return false;
            for(auto c: itor->second){
                for(auto str: next){
                    cur.push_back(str + c);
                }
            }
            next = cur;
        }
        for(auto str: next){
            if(dfs(str, lr2t) == true) return true;
        }
        return false;
    }
};
