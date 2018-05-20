
Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].

Example 2:
Given the list [1,[4,[6]]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].






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




