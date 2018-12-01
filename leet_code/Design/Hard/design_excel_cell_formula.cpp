/*



Example 1:
Excel(3,"C"); 
// construct a 3*3 2D array with all zero.
//   A B C
// 1 0 0 0
// 2 0 0 0
// 3 0 0 0

Set(1, "A", 2);
// set C(1,"A") to be 2.
//   A B C
// 1 2 0 0
// 2 0 0 0
// 3 0 0 0

Sum(3, "C", ["A1", "A1:B2"]);
// set C(3,"C") to be the sum of value at C(1,"A") and the values sum of the rectangle range whose top-left cell is C(1,"A") and bottom-right cell is C(2,"B"). Return 4. 
//   A B C
// 1 2 0 0
// 2 0 0 0
// 3 0 0 4

Set(2, "B", 2);
// set C(2,"B") to be 2. Note C(3, "C") should also be changed.
//   A B C
// 1 2 0 0
// 2 0 2 0
// 3 0 0 6




*/

class Excel {
public:
    Excel(int H, char W) {
        m=H;
        n=int(W-'A')+1;
        matrix.resize(m,vector<int>(n,0));
    }
    
    void set(int r, char c, int v) {
        
        int i=r-1, j=int(c-'A');
        int p=i*n+j;
        removepre(p);
        int delta=v-matrix[i][j];
        increase(p,delta);
    }
    
    int get(int r, char c) {
        
        return matrix[r-1][int(c-'A')];
    }
    
    int sum(int r, char c, vector<string> strs) {
        int i=r-1, j=int(c-'A');
        int p=i*n+j;
        
        removepre(p);
        
        int result=0;
        
        for(auto str:strs)
        {
            int k=str.find(':');
            if(k==-1)
            {
                int x=stoi(str.substr(1))-1;
                int y=str[0]-'A';
                hashnext[x*n+y].insert(p);
                hashpre[p].insert(x*n+y);
                result+=matrix[x][y];
                continue;
            }
            int x1=stoi(str.substr(1, k-1))-1, y1=str[0]-'A';
            int x2=stoi(str.substr(k+2))-1, y2=str[k+1]-'A';
            
            for(int x=x1;x<=x2;x++)
                for(int y=y1;y<=y2;y++)
                {
                    hashnext[x*n+y].insert(p);
                    hashpre[p].insert(x*n+y);
                    result+=matrix[x][y];
                }
        }
        int delta=result-matrix[i][j];
        increase(p,delta);
        
        return result;
    }
private:
    vector<vector<int>> matrix;
    int m,n;
    unordered_map<int,multiset<int>> hashpre, hashnext;
    void removepre(int p)
    {
        for(auto val:hashpre[p])
        {
            hashnext[val].erase(p);
            if(hashnext[val].empty()) hashnext.erase(val);
        }
    }
    void increase(int p, int val)  // increase val for p and all successors of p
    {
        int i=p/n, j=p%n;
        matrix[i][j]+=val;
        for(auto q:hashnext[p])
            increase(q,val);
    }
};


//Look at other solutions also if possible
