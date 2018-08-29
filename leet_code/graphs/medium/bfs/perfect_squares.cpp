


class Solution {
public:
    int numSquares(int n) {
        int height = 1;
        queue<int> currentLevel;
        queue<int> nextLevel;
        currentLevel.push(n);
        
        
        while(!currentLevel.empty()){
            int val = currentLevel.front();
            currentLevel.pop();
            for(int i = (int)sqrt(val); i>=1; i--){
                int tmp = val - i*i;
                if(tmp == 0){
                    return height;
                }
                nextLevel.push(tmp);
            }
            if(currentLevel.empty()){
                swap(currentLevel,nextLevel);
                height++;
            }
        }
        
    }
};
