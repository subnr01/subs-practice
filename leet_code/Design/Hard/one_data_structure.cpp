/*
Implement a data structure supporting the following operations:

Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1.
           Key is guaranteed to be a non-empty string.
           
Dec(Key) - If Key's value is 1, remove it from the data structure. 
           Otherwise decrements an existing key by 1. If the key does not exist, this function does nothing. 
           Key is guaranteed to be a non-empty string.
           
GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".

GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".

Challenge: Perform all these in O(1) time complexity.

*/


//https://discuss.leetcode.com/topic/63827/c-solution-with-comments


The premise that you have a set of keys that can map to a value.
Everytime you inc using a key, then the value associated with the key increments
by one.
Everytime you dec using a key, then the value associated with the key decrements
by one.
You have to remember that everytime a key is associated with a different element
from last time, then it starts to having its node associated with the new value, 
compared to the previous value.

And now this brings us to the notion of thing called node.
Node is a key value pair, having a value and a set of keys associated with 
that value. Everytime a key is incremented or decremented, then a new node
is created to assicated with the new value, while the other keys remain with the
old value in the old node.

           
           
class AllOne {
public:

    void inc(string key) {
        
        // If the key doesn't exist, insert it with value 0.
        if (!bucketOfKey.count(key)) {
            bucketOfKey[key] = buckets.insert(buckets.begin(), {0, {key}});
        }    
        // Insert the key in next bucket and update the lookup.
        auto next = bucketOfKey[key];
        auto bucket = next;
        next++;
               
        if (next == buckets.end() || next->value > bucket->value + 1) {
            next = buckets.insert(next, {bucket->value + 1, {}});
        }
               
        next->keys.insert(key);
        bucketOfKey[key] = next;
        
        // Remove the key from its old bucket.
        bucket->keys.erase(key);
               
        if (bucket->keys.empty()) {
            buckets.erase(bucket);
        }           
    }

    void dec(string key) {

        // If the key doesn't exist, just leave.
        if (!bucketOfKey.count(key))
            return;

        // Maybe insert the key in previous bucket and update the lookup.
        auto prev = bucketOfKey[key], bucket = prev--;
        bucketOfKey.erase(key);
        if (bucket->value > 1) {
            if (bucket == buckets.begin() || prev->value < bucket->value - 1)
                prev = buckets.insert(bucket, {bucket->value - 1, {}});
            prev->keys.insert(key);
            bucketOfKey[key] = prev;
        }
        
        // Remove the key from its old bucket.
        bucket->keys.erase(key);
        if (bucket->keys.empty())
            buckets.erase(bucket);
    }

    string getMaxKey() {
        return buckets.empty() ? "" : *(buckets.rbegin()->keys.begin());
    }
    
    string getMinKey() {
        return buckets.empty() ? "" : *(buckets.begin()->keys.begin());
    }

private:
    struct Bucket { int value; unordered_set<string> keys; };
    list<Bucket> buckets;
    unordered_map<string, list<Bucket>::iterator> bucketOfKey;
};



//Solution using multimap

class AllOne {
public:
    /** Initialize your data structure here. */
    AllOne() {
        
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if (look_map_.count(key)) {
            int temp = look_map_[key]->first;
            cache_map_.erase(look_map_[key]);
            auto it = cache_map_.insert(make_pair(temp+1, key));
            look_map_[key] = it;
        }
        else {
            auto it = cache_map_.insert(make_pair(1, key));
            look_map_[key] = it;
        }
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if (look_map_.count(key)) {
            if (look_map_[key]->first==1) {
                cache_map_.erase(look_map_[key]);
                look_map_.erase(key);
            }
            else {
                int temp = look_map_[key]->first;
                cache_map_.erase(look_map_[key]);
                auto it = cache_map_.insert(make_pair(temp-1, key));
                look_map_[key] = it;
            }
        }
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if (cache_map_.empty()) return "";
        else return prev(cache_map_.end())->second;
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if (cache_map_.empty()) return "";
        else return cache_map_.begin()->second;
    }
    
private:
    multimap<int, string> cache_map_;  // <value, key>
    unordered_map<string, multimap<int, string>::iterator> look_map_;  // <key, iterator>
};


