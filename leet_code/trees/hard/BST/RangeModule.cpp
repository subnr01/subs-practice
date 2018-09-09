/*

A Range Module is a module that tracks ranges of numbers. Your task is to design and implement the following interfaces
-- addRange(int left, int right) Adds the half-open interval [left, right), tracking every real number in that interval. 
-- queryRange(int left, int right) Returns true if and only if every real number in the interval [left, right) is 
   currently being tracked.
-- removeRange(int left, int right) Stops tracking every real number currently being tracked in the interval [left, right)

Example 1:
addRange(10, 20): null
removeRange(14, 16): null
queryRange(10, 14): true (Every number in [10, 14) is being tracked)
queryRange(13, 15): false (Numbers like 14, 14.03, 14.17 in [13, 15) are not being tracked)
queryRange(16, 17): true (The number 16 in [16, 17) is still being tracked, despite the remove operation)

*/


//fyi
//Half-Closed Interval. An interval in which one endpoint is included but not the other. 

class RangeModule {
public:
   void addRange(int left, int right) {
        int n = invals.size();
        vector<pair<int, int>> tmp;
        for (int i = 0; i <= n; i++) {
            if (i == n || invals[i].first > right) {
                tmp.push_back({left, right});
                while (i < n) tmp.push_back(invals[i++]);
            }
            else if (invals[i].second < left) 
                tmp.push_back(invals[i]);
            else {
                left = min(left, invals[i].first);
                right = max(right, invals[i].second);
            }
        }
        swap(invals, tmp);
    }
    
    bool queryRange(int left, int right) {
        int n = invals.size(), l = 0, r = n-1;
        while (l <= r) {
            int m = l+(r-l)/2;
            if (invals[m].first >= right)
                r = m-1;
            else if (invals[m].second <= left)
                l = m+1;
            else 
                return invals[m].first <= left && invals[m].second >= right;
        }
        return false;
    }
    
    void removeRange(int left, int right) {
        int n = invals.size();
        vector<pair<int, int>> tmp;
        for (int i = 0; i < n; i++) {
            if (invals[i].second <= left || invals[i].first >= right)
                tmp.push_back(invals[i]);
            else {
                if (invals[i].first < left)  tmp.push_back({invals[i].first, left});
                if (invals[i].second > right) tmp.push_back({right, invals[i].second});
            }
        }
        swap(invals, tmp);
    }
private:
    vector<pair<int, int>> invals;
};



//124 ms
class RangeModule {
private:
    vector<int> start, end;
public:
    RangeModule() {

    }
    
    void print(){
        for(int i=0; i<start.size(); ++i)
            cout << start[i] << " " << end[i] << endl;
    }
    
    void addRange(int left, int right) {
        int idx = upper_bound(start.begin(), start.end(), left) - start.begin();
        if(idx == 0 || end[idx - 1] < left){
            start.insert(start.begin() + idx, left);
            end.insert(end.begin() + idx, right);
        }else{
            end[idx - 1] = max(end[idx - 1], right);
            --idx; 
        }
        
        // Merge overlapping range.
        while(idx < start.size() - 1 && end[idx] >= start[idx + 1]){
            end[idx] = max(end[idx], end[idx + 1]);
            start.erase(start.begin() + idx + 1);
            end.erase(end.begin() + idx + 1);
        }
        // print();
    }
    
    bool queryRange(int left, int right) {
        int idx = upper_bound(start.begin(), start.end(), left) - start.begin();
        return idx > 0 && end[idx - 1] >= right;
    }
    
    void removeRange(int left, int right) {
        int idx = upper_bound(start.begin(), start.end(), left) - start.begin();
        if(idx != 0 && end[idx - 1] > left){
            int tmp = end[idx - 1];
            end[idx - 1] = left;
            if(tmp > right){
                start.insert(start.begin() + idx, right);
                end.insert(end.begin() + idx, tmp);
                ++idx;
            }
        }
        
        while(idx < start.size() && start[idx] < right){
            if(end[idx] <= right){
                start.erase(start.begin() + idx);
                end.erase(end.begin() + idx);
            }else{
                start[idx] = right;
            }
        }
        // print();
    }
};


//128ms (really fast)
class RangeModule {
public:
    RangeModule() {
        
    }
    
    void addRange(int left, int right) {
        map<int, int>::iterator it, it2 = intervals.end(), it3;
        
        it = intervals.lower_bound(left);
        /* if no interval with >= left starting point */
        if(it == intervals.end())
        {
            /* if no inteval with < left starting poing (tree is empty), directly insert new one */
            if(it == intervals.begin())
                intervals[left] = right;
            else
            {
                it--;
                /* if intersect, update the end point of current interval */
                if(it->second >= left)
                    it->second = max(it->second, right);
                /* no intersect, insert a new one */
                else
                    intervals[left] = right;
            }
        }
        else
        {
            /* it2 is used to point to the interval that has starting point < left */
            if(it != intervals.begin())
            {
                it2 = it;
                it2--;
            }
            
            /* for every interval that has starting point >= left, remove it if it intersects with [left, right) and update right */
            while(it != intervals.end() && right >= it->first)
            {
                it3 = it;
                it3++;
                right = max(right, it->second);
                intervals.erase(it);
                it = it3;
            }
            /* then insert new one */
            intervals[left] = right;

            /* if there is previous node and it intersects with current one, update the previous node then remove current one */
            if(it2 != intervals.end() && it2->second >= left)
            {
                it2->second = max(it2->second, right);
                intervals.erase(left);
            }   
        }
    }
    
    bool queryRange(int left, int right) {
        map<int, int>::iterator it;
        
        it = intervals.lower_bound(left);
        if(it == intervals.end())
        {
            if(it == intervals.begin())
                return false;
            else
            {
                it--;
                return it->second >= right;
            }
        }
        else
        {
            if(it->first == left)
                return it->second >= right;
            else if(it->first < right)
            {
                if(it->second < right)
                    return false;
                else
                    right = it->first;
            }
            
            if(it == intervals.begin())
                return false;
            else
            {
                it--;
                return it->second >= right;
            }
        }
    }
    
    void removeRange(int left, int right) {
        map<int, int>::iterator it, it2 = intervals.end(), it3;
        int new_left, new_right;
        
        it = intervals.lower_bound(left);
        if(it == intervals.end())
        {
            if(it != intervals.begin())
            {
                it--;
                if(it->second > left)
                {
                    if(it->second <= right)
                        it->second = left;
                    else
                    {
                        new_left = right;
                        new_right = it->second;
                        it->second = left;
                        intervals[new_left] = new_right;
                    }
                }
            }
        }
        else
        {
            if(it != intervals.begin())
            {
                it2 = it;
                it2--;
            }
            
            while(it != intervals.end() && right >= it->second)
            {
                it3 = it;
                it3++;
                intervals.erase(it);
                it = it3;
            }
            
            if(it != intervals.end() && right > it->first)
            {
                new_left = right;
                new_right = it->second;
                intervals.erase(it);
                intervals[new_left] = new_right;
            }
            
            if(it2 != intervals.end() && it2->second > left)
            {
                if(it2->second <= right)
                    it2->second = left;
                else
                {
                    new_left = right;
                    new_right = it2->second;
                    it2->second = left;
                    intervals[new_left] = new_right;
                }
            }
        }
    }
private:
    map<int, int> intervals;
};


//using upper and lower bound (140ms) (quite fast)
class RangeModule {
    map<int, int> intervals;
    pair<map<int, int>::iterator, map<int, int>::iterator> findIntervals(int left, int right) {
        // first range with l.left > left
        auto l = intervals.upper_bound(left);
        // first non-overlapping range
        auto r = intervals.upper_bound(right);
        
        // let's check l's prev range since it might be affected
        if (l != intervals.begin() && (--l)->second < left) {
            ++l;
        }
        
        return {l, r};
    }
public:
    RangeModule() {
        
    }
    // Adds the half-open interval [left, right)
    void addRange(int left, int right) {
        auto ranges = findIntervals(left, right);
        auto l = ranges.first;
        auto r = ranges.second;

        if (l != r) {
            left = min(left, l->first);
            right = max(right, (--r)->second);
            intervals.erase(l, ++r);
        }
        intervals[left] = right;
    }

    //          12-----15
    // 5-----9             20----50
    //        10---13
    //        10---------16
    bool queryRange(int left, int right) {
        auto l = intervals.upper_bound(left);
        
        // there's a gap between l-1 & l ranges (otherwise they'd be merged)
        // (l-1)->left < left && l->left > left, so [left, right) must be fully covered by the l-1 range
        if (l == intervals.begin() || (--l)->second < right) { // some numbers are in the gap
            return false;
        }

         return true;
    }
    
    void removeRange(int left, int right) {
        auto ranges = findIntervals(left, right);
        auto l = ranges.first;
        auto r = ranges.second;

        if (l == r) return; // nothing to remove

        // figure out the most left & most right points
        int l1 = min(l->first, left);
        int r1 = max((--r)->second, right);

        intervals.erase(l, ++r);

        // add back the "leftovers" for both sides of [left, right)
        if (l1 < left) {
            intervals[l1] = left;
        }
        if (r1 > right) {
            intervals[right] = r1;
        }
    }
};

//very short
class RangeModule {
    // add range 
    //  c-d [a  e-f   l-m   b)  g-h  
    //  c - [a - d   b)  e-f
    //  [a   e - b) - f  
    //  
    //  p- [l   r)

    map<int, int> m; 

public:
    RangeModule() {}

    void addRange(int l, int r) {
        removeIn(l, r);
        m[l] = r; 
    }

    // first consider i then consider j 
    void removeIn(int& l, int& r){
        auto i = m.upper_bound(l), j = m.upper_bound(r); 
        if (i != m.begin()){
            i--;
            if (i->second < l) i++;
        }
        if (i != j){
            j--; 
            l = min(l, i->first); 
            r = max(r, j->second);
            j++;
            m.erase(i, j); 
        }
    }

    void removeRange(int l, int r) {
        int a = l, b = r; 
        removeIn(a, b); 
        m[a] = l, m[r] = b; 
    }

    bool queryRange(int l, int r) {
        auto i = m.upper_bound(l); 
        if (i == m.begin() || (--i)->second < r) return false; 
        return true; 
    }
};


//using set
class RangeModule {
    struct Comparator
    {
        bool operator()(const std::pair<int, int>&a, const std::pair<int, int>&b)
        {
            return a.second <= b.first;
        }
    };

    std::set<std::pair<int, int>, Comparator> data;
public:
    RangeModule() {}
    
    void addRange(int left, int right) {
        auto range = data.equal_range({left, right});
        if(range.first!=range.second)
        {
            int newleft = std::min(range.first->first, left);
            int newright = std::max(std::prev(range.second)->second, right);
            data.erase(range.first, range.second);
            data.emplace(newleft, newright);
        }
        else
            data.emplace(left, right);
    }
    
    bool queryRange(int left, int right) {
        auto range = data.equal_range({left, right});
        
        if(range.first==range.second) return false;
        
        // if there are non-tracked points in the end
        if(std::prev(range.second)->second < right) return false;
        
        // if there are non-tracked points at the beginning and middle
        for(auto it=range.first; it!=range.second; ++it)
        {
            if(left < it->first) return false;
            else left = it->second;
        }
        
        return true;
    }
    
    void removeRange(int left, int right) {
        auto range = data.equal_range({left, right});
        
        if(range.first!=range.second)
        {
            auto lo = range.first->first;
            auto hi = std::prev(range.second)->second;
            data.erase(range.first, range.second);
            
            // if there are tracked point at the beginning
            if(lo < left)
                data.emplace(lo, left);

            // if there are tracked point at the end
            if(right < hi)
                data.emplace(right, hi);
        }
    }
};


