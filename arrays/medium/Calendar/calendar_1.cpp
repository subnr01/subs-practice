/*

Implement a MyCalendar class to store your events. A new event can be added if adding the
event will not cause a double booking.

Your class will have the method, book(int start, int end). Formally, this represents 
a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.

A double booking happens when two events have some non-empty intersection (ie., there is some time
that is common to both events.)

For each call to the method MyCalendar.book, return true if the event can be added to the calendar 
successfully without causing a double booking. Otherwise, return false and do not add the event to the calendar.

Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)
Example 1:
MyCalendar();
MyCalendar.book(10, 20); // returns true
MyCalendar.book(15, 25); // returns false
MyCalendar.book(20, 30); // returns true
Explanation: 
The first event can be booked.  The second can't because time 15 is already booked by another event.
The third event can be booked, as the first event takes every time less than 20, but not including 20.

*/

//Easier soln
class MyCalendar {
    vector<pair<int, int>> books;
public:
    bool book(int start, int end) {
        for (pair<int, int> p : books)
            if (max(p.first, start) < min(end, p.second)) return false;
        books.push_back({start, end});
        return true;
    }
};


class MyCalendar {
    
public:
    map<int, int> books;
    bool book(int s, int e) {
        auto next = books.lower_bound(s);
        
        cout<<"\n in fuck\n";
        
        if (next == books.begin()) {
            cout <<endl<<"begin "<<next->first<<endl;
        }
        else if (next == books.end()) {
            cout <<endl<<"end "<<next->first<<endl;
        } else {
            cout <<endl<<"niether begin or end "<<next->first<<endl;
        }
        
        
        if (next != books.end() && next->first < e)
        {
            cout<<"\n 1false" ;cout<<next->first;
            return false;
        }
        
        if (next != books.begin() && (--next)->second > s) {
            cout<<"\n 2false" ;
            cout<<next->second;
            
            return false;
        }
        
        books[s] = e;
        cout<<"\n true" ;
        return true;
    }
    
    
        
};



int main(int argc, const char * argv[]) {
    // insert code here...
    //Solution s1;
    //vector<int> s = {2,1,5,6,2,3};
    //cout<<endl<<s1.largestRectangleArea(s)<<endl;
    MyCalendar s1;
    
    
    s1.book(20,30);
    s1.book(10,10);
    s1.book(35,40);
    s1.book(15,40);
    
    
    std::cout << "Hello, World!\n";
    return 0;
}
