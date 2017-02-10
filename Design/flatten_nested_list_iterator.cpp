






/*
Difficult but great performance
from the master itself
*/

class NestedIterator {
public:
    stack<NestedInteger> stk;
    NestedIterator(vector<NestedInteger> &nestedList) {
        for (int i = nestedList.size() - 1; i >= 0; i--)
            stk.push(nestedList[i]);
    }       

    int next() {
        int val = stk.top().getInteger();
        stk.pop(); 
        return val;
    }       

    bool hasNext() {
        while (!stk.empty()) {
            NestedInteger curr = stk.top();
            if (curr.isInteger()) return true;
            stk.pop();
            for (int i = curr.getList().size() - 1; i >= 0; i--)
                stk.push((curr.getList())[i]);
        }           
        return false;
    }       
};


/*
Easier version
*/
class NestedIterator {
public:
    stack<NestedInteger> stk;
    NestedIterator(vector<NestedInteger> &nestedList) {
        for (int i = nestedList.size() - 1; i >= 0; i--)
            stk.push(nestedList[i]);
    }       

    int next() {
        int val = stk.top().getInteger();
        stk.pop(); 
        return val;
    }       

    bool hasNext() {
        while (!stk.empty()) {
            NestedInteger curr = stk.top();
            if (curr.isInteger()) return true;
            stk.pop();
            for (int i = curr.getList().size() - 1; i >= 0; i--)
                stk.push((curr.getList())[i]);
        }           
        return false;
    }       
};




