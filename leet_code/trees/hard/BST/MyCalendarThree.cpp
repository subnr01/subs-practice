
/*

Implement a MyCalendarThree class to store your events. A new event can always be added.

Your class will have one method, book(int start, int end). Formally, this represents a
booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.

A K-booking happens when K events have some non-empty intersection (ie., there is some 
time that is common to all K events.)

For each call to the method MyCalendar.book, return an integer K representing the 
largest integer such that there exists a K-booking in the calendar.

Your class will be called like this: MyCalendarThree cal = new MyCalendarThree(); 
MyCalendarThree.book(start, end)


Example 1:
MyCalendarThree();
MyCalendarThree.book(10, 20); // returns 1
MyCalendarThree.book(50, 60); // returns 1
MyCalendarThree.book(10, 40); // returns 2
MyCalendarThree.book(5, 15); // returns 3
MyCalendarThree.book(5, 10); // returns 3
MyCalendarThree.book(25, 55); // returns 3
Explanation: 
The first two events can be booked and are disjoint, so the maximum K-booking is a 1-booking.
The third event [10, 40) intersects the first event, and the maximum K-booking is a 2-booking.
The remaining events cause the maximum K-booking to be only a 3-booking.
Note that the last event locally causes a 2-booking, but the answer is still 3 because
eg. [10, 20), [10, 40), and [5, 15) are still triple booked.


*/



//fastest
class MyCalendarThree {
        map<int, int> m;
        int res;
    public:
        MyCalendarThree() {
            res = 0;
        }
        
        int book(int start, int end) {
            auto itStart = m.lower_bound(start);
            if(itStart == m.end()) {
                m[start] = 0;
                m[end] = 1;
                res = max(1, res);
                return res;
            } else if (itStart->first !=start) {
                m[start] = itStart->second;
            }
            
            auto itEnd = m.lower_bound(end);
            if(itEnd == m.end()) {
                m[end] = 0;
            } else if (itEnd->first != end) {
                m[end] = itEnd->second;
            }   
            
            if(itStart == itEnd) {
                int tmp = ++m[end];
                res = max(res, tmp);
                return res;
            }
            
            if(itStart->first == start) {
                itStart++;
            }
            if(itEnd->first == end) {
                itEnd++;
            }
                        
            for(auto it = itStart; it != itEnd; it++) {
                it->second++;
                res = max(res, it->second);
            }
            
            /*
            cout << "start: " << start << endl;
            cout << "end: " << end << endl;
            for(auto it : m) { 
                cout << "(" << it.first << "," << it.second << ") ";
            }
            cout << endl;
            */
            return res;
        }
};







//faster soln

class MyCalendarThree {
    map<int, int> points; // <point, depth>
    int m_depth = 0; // res
public:
    int book(int start, int end) {
        auto p_left = points.find(start);
        if(p_left == points.end()){
            p_left = points.emplace(start, -1).first;
            if(p_left != points.begin()){
                int val = (--p_left) -> second; ++p_left;
                p_left -> second = val;
            }
            else{
                p_left -> second = 0;
            }
        }
        
        auto p_right = points.find(end);
        if(p_right == points.end()){
            p_right = points.emplace(end, -1).first;
        }
        
        int last_depth = p_left -> second;
        do {
            last_depth = ++ (p_left -> second);
            if(last_depth > m_depth){
                m_depth = last_depth;
            }
        } while(++ p_left != p_right);
        if(p_right -> second == -1){
            p_right -> second = last_depth - 1;
        }
        
//         for(auto& pd: points){
//             printf("point: %d, depth: %d.\n", pd.first, pd.second);
//         }
//         printf("\n");
        
        return m_depth;
    }
};



//Alexander
class MyCalendarThree {
    map<int, int> timeline;
public:
    int book(int s, int e) {
        timeline[s]++; // 1 new event will be starting at [s]
        timeline[e]--; // 1 new event will be ending at [e];
        int ongoing = 0, k = 0;
        for (pair<int, int> t : timeline)
            k = max(k, ongoing += t.second);
        return k;
    }
};

//faster than alexander
class MyCalendarThree {
private:
    map<int, int> freq;
        
public:
    MyCalendarThree() {
        
    }
    
    int book(int start, int end) {
        ++freq[start];
        --freq[end];
        
        int cnt = 0;
        int maxCnt = 0;
        
        for (auto p : freq) {
            cnt += p.second;
            maxCnt = max(maxCnt, cnt);
        } // for
        
        return maxCnt;
    }
};

