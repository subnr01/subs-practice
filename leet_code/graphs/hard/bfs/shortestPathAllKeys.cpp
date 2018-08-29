/*


*/


//Solution 1

class Solution {
public:
     int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size();
        int n = m? grid[0].size() : 0;
        if (!m || !n) return 0;
        int dir[] = {0,-1,0,1,0};
        vector<vector<vector<bool>>> isVisited(m, vector<vector<bool>>(n,vector<bool>(64,0))); // bitmap 111111                                           
        int K=0, path=0;
        queue<pair<int, int>> q;
        for (int i=0; i<m; i++)
           {
               for (int j=0; j<n; j++)
               {
                   if (grid[i][j] == '@')
                   {
                       q.push({i*n+j,0});
                       isVisited[i][j][0] = 1;
                   }
                   if (grid[i][j]>='a' && grid[i][j]<='f')
                       K++;
               }
           }
        while (!q.empty())
           {
                int N = q.size();
                for (int i=0; i<N; i++)
                {
                    int x=q.front().first/n, y=q.front().first%n, carry=q.front().second;
                    q.pop();
                    if (carry == ((1<<K)-1)) return path;
                    for (int j=0; j<4;j++)
                    {
                        int cx = x+dir[j];
                        int cy = y+dir[j+1];
                        int k = carry;
                        if (cx>=m || cx <0 || cy>=n || cy<0 || grid[cx][cy] == '#')
                            continue;
                        if (grid[cx][cy]>='a' && grid[cx][cy]<='f')
                        {
                            k = carry | (1<<(grid[cx][cy] - 'a'));
            
                        }
                        else if (grid[cx][cy]>='A' && grid[cx][cy]<='F')
                        {
                            if (! (carry & (1<<(grid[cx][cy] - 'A'))))
                                continue;
                        }
                        if (!isVisited[cx][cy][k])
                        {
                            isVisited[cx][cy][k]=1;
                            q.push({cx*n+cy,k});
                        }
                    }
                    
                }
               path++;
           }
        return -1;     
    }
};


//Different Soln
class Solution {
    struct Position{
        int x, y;
    };
    const int di[4] = {0, 1, 0, -1};
    const int dj[4] = {1, 0, -1, 0};
    int n, m;
    vector<string> grid;
    Position pos[13];
    int G[13][13];
    unsigned int dist[1<<6][13];
    int target;
    
    int toID(char c){
        if(c == '@') return 12;
        if(islower(c)) return c-'a';    //0-5
        if(isupper(c)) return c-'A'+6;  //6-11
        return -1;
    }
    void init(vector<string>& grid){
        this->grid = grid;
        this->n = grid.size();
        this->m = grid[0].size();
        
        for(int i = 0; i < 13; i++) pos[i].x = pos[i].y = -1;
        for(int i = 0; i < 13; i++)
            for(int j = 0; j < 13; j++)
                G[i][j] = -1;
        memset(dist, 0x3f, sizeof dist);
        target = 0;
    }
    void getPositions(){
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(grid[i][j] != '.' && grid[i][j] != '#')
                    pos[toID(grid[i][j])] = Position{i, j};
    }
    void getEdges(int from){
        if(pos[from].x == -1 || pos[from].y == -1) return;
        queue<Position> Q;
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        Q.push(pos[from]);
        vis[pos[from].x][pos[from].y] = true;
        int level = 0;
        while(Q.size()){
            int sz = Q.size();
            while(sz--){
                Position cur = Q.front(); Q.pop();
                if(grid[cur.x][cur.y] != '.'){
                    G[from][toID(grid[cur.x][cur.y])] = level;
                    if(toID(grid[cur.x][cur.y]) != from) continue;
                }
                for(int k = 0; k < 4; k++){
                    Position newPos {cur.x+di[k], cur.y+dj[k]};
                    if(newPos.x >= 0 && newPos.x < n && newPos.y >= 0 && newPos.y < m &&
                       grid[newPos.x][newPos.y] != '#' && !vis[newPos.x][newPos.y]){
                        Q.push(newPos);
                        vis[newPos.x][newPos.y] = true;
                    }
                }
            }
            level++;
        }
    }
    void calcTarget(){
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(toID(grid[i][j]) >= 0 && toID(grid[i][j]) <= 5)
                    target |= (1 << toID(grid[i][j]));
    }
    
    struct state{
        int dist;
        int keyState;
        int node;
        bool operator<(const state& b) const{
            return -dist < -b.dist;
        }
    };
    int getRes(){
        priority_queue<state> Q;
        
        Q.push(state{0, 0, 12});
        dist[0][12] = 0;
        
        while(Q.size()){
            state s = Q.top(); Q.pop();
            if(s.keyState == target) return s.dist;
            if(dist[s.keyState][s.node] < s.dist) continue;
            
            for(int i = 0; i < 13; i++) if(G[s.node][i] != -1){
                state newS {G[s.node][i] + s.dist, s.keyState, i};
                if(i >= 6 && i <= 11 && ((s.keyState>>(i-6))&1) == 0) continue;
                if(i >= 0 && i <= 5) newS.keyState |= (1<<i);
                if(newS.dist < dist[newS.keyState][newS.node]){
                    dist[newS.keyState][newS.node] = newS.dist;
                    Q.push(newS);
                }
            }
        }
        return -1;
    }
    
    
    
    
    void printGrid(){
        cout << "Grid:\n";
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                cout << grid[i][j] << " \n"[j==m-1];
    }
    void printG(){
        cout << "G:\n";
        for(int i = 0; i < 13; i++)
            for(int j = 0; j < 13; j++)
                cout << G[i][j] << "\t\n"[j==12];
    }
    void printPos(){
        cout << "pos:\n";
        for(int i = 0; i < 13; i++)
            cout << pos[i].x << ' ' << pos[i].y << endl;
    }
    void printDist(){
        cout << "dist:\n";
        for(int i = 0; i < 1<<6; i++)
            for(int j = 0; j < 13; j++)
                cout << dist[i][j] << "\t\n"[j==12];
    }
    void printDistIfEQ(int x){
        cout << "Dist if = " << x << ":\n";
        for(int i = 0 ; i < (1<<6); i++)
            for(int j = 0; j < 13; j++)
                if(dist[i][j] == x)
                    cout << i << ' ' << j << endl;
    }
    void printTarget(){
        cout << "Target: " << target << endl;
    }
    public:
    int shortestPathAllKeys(vector<string>& grid) {
        if(grid.size() == 0 || grid[0].size() == 0) return -1;
        
        init(grid);
        getPositions();
        for(int i = 0; i < 13; i++) getEdges(i);
        calcTarget();
        int res = getRes();
        
        // printGrid();
        // printPos();
        printG();
        // printDist();
        printDistIfEQ(2);
        return res;
    }
};

