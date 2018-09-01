/*
You are asked to cut off trees in a forest for a golf event. The forest is represented as a non-negative 2D map, in this map:

0 represents the obstacle can't be reached.
1 represents the ground can be walked through.
The place with number bigger than 1 represents a tree can be walked through, and this positive number represents the tree's height.
You are asked to cut off all the trees in this forest in the order of tree's height - always cut off the tree 
with lowest height first. And after cutting, the original place has the tree will become a grass (value 1).

You will start from the point (0, 0) and you should output the minimum steps you need to walk to cut off all the trees.
If you can't cut off all the trees, output -1 in that situation.

You are guaranteed that no two trees have the same height and there is at least one tree needs to be cut off.

Example 1:
Input: 
[
 [1,2,3],
 [0,0,4],
 [7,6,5]
]
Output: 6
Example 2:
Input: 
[
 [1,2,3],
 [0,0,0],
 [7,6,5]
]
Output: -1
Example 3:
Input: 
[
 [2,3,4],
 [0,0,5],
 [8,7,6]
]
Output: 6
Explanation: You started from the point (0,0) and you can cut off the tree in (0,0) directly without walking.

*/





class Solution {
    class compareClass {
    public: 
    bool operator()(const pair<long, pair<int,int>> &a , const pair<long, pair<int,int>> &b){
        return a.first > b.first;
       }
    };
    
public:
    int cutOffTree(vector<vector<int>>& forest) {
        
        int m= forest.size();
        if(!m) return -1;
        int n = forest[0].size();
        //priority_queue<pair<int, pair<int,int> >, vector<pair<int, pair<int,int> > > > pq;
        priority_queue<pair<long, pair<int,int>>, vector<pair<long, pair<int,int>>>, compareClass> pq;
        
       for(int i=0;i<m;i++) {
            for(int j=0;j<n;j++) {
                if(forest[i][j] > 1)
                    pq.push({forest[i][j],{i, j}});
            }
        }
        
        //doing DFS to see if every tree is available from (0,0)
        int tree_available = 0;
        vector<vector<bool>> visited(forest.size(),vector<bool>(forest[0].size(),false));
        DFS(0,0,visited,forest,tree_available);
        if(tree_available != pq.size())   return -1; //some trees are not available from (0,0)
        
        
        queue<pair<int,int>> q;
        q.push({0,0});
        int sx =0, sy =0;
        int step =0;
        while(pq.size()){
            
            if(findpath(sx,sy,pq.top().second.first, pq.top().second.second, forest))
                step += abs(sx-pq.top().second.first)+abs(sy-pq.top().second.second);
            else 
                step += BFS(sx,sy,pq.top().second.first, pq.top().second.second, forest);
            
            sx = pq.top().second.first;
            sy = pq.top().second.second;
            pq.pop();
         }
        return step;
    }
    
    int BFS(int si, int sj, int ti, int tj, vector<vector<int>>& forest) {
        
     vector<vector<bool>> visited(forest.size(),vector<bool>(forest[0].size(),false));
        visited[si][sj] = true;
        queue<pair<int,int>> q({make_pair(si,sj)});
        int len = 0;
        int di[4] = {1,0,-1,0};
        int dj[4] = {0,1,0,-1};
        while(true){
            
            int qsize = q.size();
            while(qsize--){
                
                if(q.front().first==ti && q.front().second==tj) //the function stops here
                    return len; 
                for(int k=0; k<4; ++k){
                    int i=q.front().first+di[k];
                    int j=q.front().second+dj[k];
                    if(i>=0 && i<forest.size() && j>=0 && j<forest[0].size() && !visited[i][j] && forest[i][j]>0){
                        visited[i][j] = true;
                        q.push(make_pair(i,j));
                    }
                }
                q.pop();
            }
            ++len;
           
        }
        return -999999999; //redundancy, never goes this line
      }
    
     void DFS(int i, int j, vector<vector<bool>>& visited, const vector<vector<int>>& forest, int& count){
        if(i<0 || i>=forest.size() || j<0 || j>=forest[0].size() || visited[i][j] || forest[i][j]==0)  return;
        visited[i][j] = true;
        if(forest[i][j]>1)  count++;
        DFS(i+1,j,visited,forest,count);
        DFS(i-1,j,visited,forest,count);
        DFS(i,j+1,visited,forest,count);
        DFS(i,j-1,visited,forest,count);
    }
    
    bool findpath(int x1, int y1, int x2, int y2, vector<vector<int>>& forest) {
        
        int dx = (x2>x1)? 1 : -1;
        int dy = (y2>y1)? 1 : -1;
        int minstep = abs(x1-x2)+abs(y1-y2);
        queue<pair<int,int>> q({make_pair(x1,y1)});
        while(minstep--){
            int qsize = q.size();
            if(qsize==0) 
                return false; //haven't gone minstep yet, but no path available
            while(qsize--){
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                if(x!=x2 && forest[x+dx][y]>0 && ((x+dx)!=q.back().first || y!=q.back().second))
                    q.push(make_pair(x+dx,y));
                if(y!=y2 && forest[x][y+dy]>0 && (x!=q.back().first || (y+dy)!=q.back().second))
                    q.push(make_pair(x,y+dy));
            }
        }
        return q.size()==1; //if true return, only destination [x2,y2] is in the queue
    }
        
   
};


//72ms
class Solution {
public:
    struct tree{
        int val,x,y;
        tree(int v,int x,int y):val(v),x(x),y(y){}
    };
    int cutOffTree(vector<vector<int>>& forest) {
        vector<tree> v;
        for(int i=0;i<forest.size();++i)
        for(int j=0;j<forest[i].size();++j)
            if(forest[i][j]>1){
                v.push_back(tree(forest[i][j],i,j));
            }
        sort(v.begin(),v.end(),[](const tree&a,const tree&b){return a.val<b.val;});
        int x=0,y=0,res=0;
        for(int i=0;i<v.size();++i){
            int steps = bfs(forest,x,y,v[i].x,v[i].y);
            if(steps==-1) return -1;
            res += steps;
            x = v[i].x, y = v[i].y;
        }
        return res;
    }
    vector<vector<int>> dirs = {{-1,0},{1,0},{0,-1},{0,1}};
    int bfs(vector<vector<int>>& forest,int x0,int y0,int x1,int y1){
        if(x0==x1&&y0==y1) return 0;
        int m = forest.size(),n=forest[0].size();
        vector<vector<bool>> visited(m,vector<bool>(n,false));
        deque<tree> dq;
        dq.push_back(tree(0,x0,y0));
        visited[x0][y0] = true;
        while(!dq.empty()){
            tree t = dq.front();
            if(t.x==x1&&t.y==y1) return t.val*2+abs(x0-x1)+abs(y0-y1);
            visited[t.x][t.y] = true;
            dq.pop_front();
            for(int i=0;i<4;++i){
                int x = dirs[i][0]+t.x, y = dirs[i][1]+t.y;
                if(x<0||y<0||x>=m||y>=n||visited[x][y]||forest[x][y]<1) continue;
                bool add = true;
                if(i==0) add = t.x<=x1;
                else if(i==1) add = t.x>=x1;
                else if(i==2) add = t.y<=y1;
                else add = t.y>=y1;
                if(add) dq.push_back(tree(t.val+1,x,y));
                else dq.push_front(tree(t.val,x,y));
            }
        }
        return -1;
    }
};
