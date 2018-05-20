class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(m.find(val) != m.end()) {
            return false;
        }
        
        /* Put the element at the back */
        nums.push_back(val);
        
        /* update map */
        m[val] = nums.size() - 1;
        
        return true;
        
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(m.find(val) == m.end()) {
            return false;
        }
        
        /* Exchange last and val in the vector */
        int last = nums.back();
        int pos = m[val];
        
        nums[pos] = last;
        nums[nums.size() - 1] = val;
        
        /* Update last "value" in the map */
        m[last] = pos;
        
        /* Removal time */
        m.erase(val);
        nums.pop_back();
        
        /* bye */
        return true;
        
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return nums[rand() % nums.size()];
    }
    
    unordered_map<int, int> m;
    vector<int> nums;
};
