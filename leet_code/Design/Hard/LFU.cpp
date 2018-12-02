/*


Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations:
get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, 
it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, 
when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Follow up:
Could you do both operations in O(1) time complexity?
*/
/*
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


//multiple hashmap Solution
class LFUCache {
    int cap;
    int size;
    int minFreq;
    unordered_map<int, pair<int, int>> m; //key to {value,freq};
    unordered_map<int, list<int>::iterator> mIter; //key to list iterator;
    unordered_map<int, list<int>>  fm;  //freq to key list;
public:
    LFUCache(int capacity) {
        cap=capacity;
        size=0;
    }
    
    int get(int key) {
        if(m.count(key)==0) return -1;
        
        fm[m[key].second].erase(mIter[key]);
        m[key].second++;
        fm[m[key].second].push_back(key);
        mIter[key]=--fm[m[key].second].end();
        
        if(fm[minFreq].size()==0 ) 
              minFreq++;
        
        return m[key].first;
    }
    
   void put(int key, int value) {
        if(cap<=0) return;
        
        int storedValue=get(key);
        if(storedValue!=-1)
        {
            m[key].first=value;
            return;
        }
        
        if(size>=cap )
        {
            m.erase( fm[minFreq].front() );
            mIter.erase( fm[minFreq].front() );
            fm[minFreq].pop_front();
            size--;
        }
        
        m[key]={value, 1};
        fm[1].push_back(key);
        mIter[key]=--fm[1].end();
        minFreq=1;
        size++;
    }
};


//multiple hashmap faster solution
class LFUCache {
public:
	LFUCache(int capacity) : space(capacity), empty(!capacity) {}
	int get(int key);
	void put(int key, int value);
private:
	void update(int key);
	list<list<pair<int, int>>> values;
	unordered_map<int, list<list<pair<int, int>>>::iterator> node;
	unordered_map<int, list<pair<int, int>>::iterator> cache;
	int space;
	bool empty;
};

int LFUCache::get(int key) {
	if (node.find(key) == node.end())
		return -1;
	update(key);
	return cache[key]->second;
}

void LFUCache::put(int key, int value) {
	if (empty)
		return;
	if (node.find(key) != node.end()) {
		cache[key]->second = value;
		update(key);
		return;
	}
	if (space > 0)
		--space;
	else {
		int evicted = (++values.front().begin())->first;
		node[evicted]->erase(cache[evicted]);
		if (node[evicted]->size() == 1)
			values.erase(node[evicted]);
		node.erase(evicted);
		cache.erase(evicted);
	}
	if (values.size() && values.front().front().first == 1)
		node[key] = values.begin();
	else
		node[key] = values.insert(values.begin(), list<pair<int, int>>({ { 1, 0 } }));
	cache[key] = node[key]->insert(node[key]->end(), { key, value });
}

void LFUCache::update(int key) {
	int frequency = node[key]->front().first + 1, value = cache[key]->second;
	node[key]->erase(cache[key]);
	if (node[key]->size() == 1)
		node[key] = values.erase(node[key]);
	else
		++node[key];
	if (node[key] == values.end() || node[key]->front().first > frequency)
		node[key] = values.insert(node[key], list<pair<int, int>>({ { frequency, 0 } }));
	cache[key] = node[key]->insert(node[key]->end(), { key, value });
}






