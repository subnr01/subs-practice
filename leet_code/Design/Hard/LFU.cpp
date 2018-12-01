/*


Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations:
get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, 
it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, 
when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LFUCache cache = new LFUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.put(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

*/



https://discuss.leetcode.com/topic/69409/c-solution-with-detailed-explanations-using-indexed-priority-queue-i-e-hashmap-priority-queue

https://discuss.leetcode.com/topic/69436/concise-c-o-1-solution-using-3-hash-maps-with-explanation/2

https://discuss.leetcode.com/topic/69137/java-o-1-accept-solution-using-hashmap-doublelinkedlist-and-linkedhashset

class LFUCache {
public:
    LFUCache(int capacity) : capacity_(capacity), size_() {
    }
    
    int get(int key) {
        if (!dict_.count(key)) {
            return -1;
        }
        IncKey(key);
        
        return dict_[key]->value;
    }
    
    void put(int key, int value) {
        if (capacity_ == 0) {
            return;
        }
        
        if (dict_.count(key)) {
            IncKey(key);
            dict_[key]->value = value;
            return;
        }
        
        if (size_ == capacity_) {
            dict_.erase(elems_.begin()->data.begin()->key);
            elems_.begin()->pop_front();
            if (elems_.begin()->empty()) {
                elems_.pop_front();
            }
        } else {
            ++size_;
        }
        
        if (elems_.empty() || elems_.begin()->count != 1) {
            elems_.push_front(Elems{1, {}});
        }
        
        elems_.begin()->push_back(Elem{key, value, elems_.begin()});
        dict_[key] = std::prev(elems_.begin()->data.end());
    }
    
private:
    void IncKey(int key) {
        auto iter = dict_[key];    
        auto elem = *iter;
        elem.parent->data.erase(iter);
        int count = elem.parent->count + 1;
    
        auto next_parent = std::next(elem.parent);
        if (elem.parent->empty()) {
            elems_.erase(elem.parent);
        }
        
        if (next_parent == elems_.end() || next_parent->count != count) {
            auto new_parent = elems_.insert(next_parent, Elems{count, {}});
            elem.parent = new_parent;
            new_parent->push_back(elem);
            dict_[key] = std::prev(new_parent->data.end());
        } else {
            elem.parent = next_parent;
            next_parent->push_back(elem);
            dict_[key] = std::prev(next_parent->data.end());
        }
    }
    
    struct Elems;
    
    struct Elem {
        int key;
        int value;
        list<Elems>::iterator parent;
    };
    
    struct Elems {
        int count;
        list<Elem> data;
        
        void pop_front() {
            data.pop_front();
        }
        
        void push_back(const Elem& elem) {
            data.push_back(elem);
        }
        
        bool empty() const {
            return data.empty();
        }
    };
    
    unordered_map<int, list<Elem>::iterator> dict_;
    list<Elems> elems_;
    int capacity_;
    int size_;
};


//Look at other solutions too







