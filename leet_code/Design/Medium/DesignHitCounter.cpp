



/*
Design a hit counter which counts the number of hits received in the past 5 minutes.
Each function accepts a timestamp parameter (in seconds granularity) and you may assume that calls are being made
to the system in chronological order (ie, the timestamp is monotonically increasing). You may assume that the earliest
timestamp starts at 1.
It is possible that several hits arrive roughly at the same time.
Example:
HitCounter counter = new HitCounter();

// hit at timestamp 1.
counter.hit(1);

// hit at timestamp 2.
counter.hit(2);

// hit at timestamp 3.
counter.hit(3);

// get hits at timestamp 4, should return 3.
counter.getHits(4);

// hit at timestamp 300.
counter.hit(300);

// get hits at timestamp 300, should return 4.
counter.getHits(300);

// get hits at timestamp 301, should return 3.
counter.getHits(301);
*/
https://discuss.leetcode.com/topic/48758/super-easy-design-o-1-hit-o-s-gethits-no-fancy-data-structure-is-needed
http://stackoverflow.com/questions/17562089/how-to-count-number-of-requests-in-last-second-minute-and-hour



2 Solutions available
One using queue and the other using vector.
    
    
    
//Using queue
class HitCounter {
public:
    /** Initialize your data structure here. */
    HitCounter() {
    }
    
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        q.push(timestamp);
    }
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        while(!q.empty() && timestamp - q.front() >= 300) q.pop();
        return q.size();
    }
private:
    queue<int> q;
};


//Using vector
class HitCounter {
    vector<pair<int, int> > hits;
public:
    /** Initialize your data structure here. */
    HitCounter() : hits(300) {        
    }
    
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        int i = timestamp % 300;
        if (hits[i].first != timestamp) 
            hits[i] = make_pair(timestamp, 1);
        else
            hits[i].second++;
    }
    
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        int t = 0;
        for (int i = 0; i < 300; i++) {
            if (timestamp - hits[i].first < 300)
                t += hits[i].second;
        }
        return t;
    }
};


