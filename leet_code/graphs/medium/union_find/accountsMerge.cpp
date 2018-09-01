/*
Given a list accounts, each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name,
and the rest of the elements are emails representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some email
that is common to both accounts. Note that even if two accounts have the same name, they may belong to different people 
as people could have the same name. A person can have any number of accounts initially, but all of their accounts 
definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each account is the name, 
and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

Example 1:
Input: 
accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], 
["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]

Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], 
["Mary", "mary@mail.com"]]
Explanation: 
The first and third John's are the same person as they have the common email "johnsmith@mail.com".
The second John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.

*/

//Union Find 
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        vector<int> parent(accounts.size());
        vector<int> unionHe(accounts.size());
        vector<vector<string>> res;
        unordered_map<string, int> mail2account;
        for (int i=0; i<accounts.size(); i++) {
            parent[i] = i;
        }
        for (int i=0; i<accounts.size(); i++) {
            for (int j=1; j<accounts[i].size(); j++) {
                if (!mail2account.count(accounts[i][j])) {
                    mail2account[accounts[i][j]] = i;
                } else {
                    __union(i, mail2account[accounts[i][j]], unionHe, parent);
                }
            }
        }
        unordered_map<int, set<string>> newAccounts;
        for (int i=0; i<accounts.size(); i++) {
            int p = __root(i, parent);
            newAccounts[p].insert(accounts[i].begin()+1, accounts[i].end());
        }
        for (const auto& it: newAccounts) {
            vector<string> account;
            account.push_back(accounts[it.first][0]);
            account.insert(account.end(), it.second.begin(), it.second.end());
            res.push_back(move(account));
        }
        return res;
        
    }
    
private:
    void __union(int i, int j, 
                 vector<int>& unionHe, 
                 vector<int>& parent) {
        int p = __root(i, parent);
        int q = __root(j, parent);
        if (unionHe[p] > unionHe[q]) {
            parent[q] = p;
        } else if (unionHe[q] > unionHe[p]) {
            parent[p] = q;
        } else {
            unionHe[q]++;
            parent[p] = q;
        } 
    }
    
    int __root(int i, vector<int>& parent) {
        while (parent[i] != i){
            parent[i] = parent[parent[i]];
            i = parent[i];
        }
        return i;
    }
    
    bool __find(int i, int j, vector<int>& parent) {
        int p = __root(i, parent);
        int q = __root(j, parent);
        return (p == q);
    }
};


//dfs
class Solution {
public:
    vector<vector<string>> accountsMerge(const vector<vector<string>>& accounts) {
        
        // Key = email, Value = list of indexes that has that email
        unordered_map<string, vector<int>> email2index;
        for(int i = 0; i < accounts.size(); ++i)
        {
            for(int j = 1; j < accounts[i].size(); ++j)
            {
                string email = accounts[i][j];
                email2index[email].emplace_back(i);
            }
        }
        
        vector<vector<string>> results;
        vector<int> visited(accounts.size(), false);
        
        for(int i = 0; i < accounts.size(); ++i)
        {
            if(visited[i])
            {
                continue;
            }
            
            visited[i] = true;
            
            set<string> emails;
            stack<int> toVisit({i});
            
            while(!toVisit.empty())
            {
                auto curr = toVisit.top();
                toVisit.pop();
                emails.insert(accounts[curr].begin() +1, accounts[curr].end());
                for(int k = 1; k < accounts[curr].size(); ++k)
                {
                    string email = accounts[curr][k];
                    for(auto &&index : email2index[email])
                    {
                        if(visited[index])
                        {
                            continue;
                        }
                        
                        visited[index] = true;
                        toVisit.push(index);
                    }
                }
            }
            
            results.emplace_back(vector<string> {accounts[i][0]});
            auto &b = results.back();
            b.insert(b.end(), emails.begin(), emails.end());
        }
        
        return results;
    }
};


