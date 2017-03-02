/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: 
get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, 
it should invalidate the least recently used item before inserting a new item.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4



https://discuss.leetcode.com/topic/6812/c-11-code-74ms-hash-table-list

https://discuss.leetcode.com/topic/25792/clean-short-standard-c-solution-not-writing-c-in-c-like-all-other-lengthy-ones

class LRUCache{
public:
    LRUCache(int capacity):cap(capacity) {
        
    }
    
    int get(int key) {
        if(map.find(key) == map.end()) {
            return -1;
        }
        else {
            //lst.splice(lst.begin(),lst,map[key]);
            touch(map[key]);
            return lst.begin()->second;
        }
    }
    
    void put(int key, int value) {
        if(map.find(key) != map.end()) {
            //lst.splice(lst.begin(),lst,map[key]);
            touch(map[key]);
            lst.begin()->second = value;
        }
        else {
            if(map.size() == cap) {
                int dkey = lst.back().first;
                map.erase(dkey);
                lst.pop_back();
            }
            lst.push_front({key,value});
            map[key] = lst.begin();
        }
    }
private:
    typedef std::list<std::pair<int,int>> PList; // PAIR IS THE (KEY,VALUE) PAIR
    
    int cap;
    PList lst;
    std::unordered_map<int,PList::iterator> map;
    
    // UPDATE THE LIST AND THE MAP (AFTER UPDATE, IT WILL BE THE LIST HEAD)
    void touch(PList::iterator it) {
        int key = it->first;
        int value = it->second;
        lst.erase(it);
        lst.push_front({key,value});
        map[key] = lst.begin();
    }
};
