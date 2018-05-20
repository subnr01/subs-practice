/*

LeetCode 635. Design Log Storage System

You are given several logs that each log contains a unique id and timestamp. 
Timestamp is a string that has the following format: Year:Month:Day:Hour:Minute:Second,
for example, 2017:01:01:23:59:59. All domains are zero-padded decimal numbers.

Design a log storage system to implement the following functions:

void Put(int id, string timestamp): Given a log's unique id and timestamp, store the log in your storage system.

int[] Retrieve(String start, String end, String granularity): Return the id of logs
whose timestamps are within the range from start to end. Start and end all have the same format as timestamp. However,
granularity means the time level for consideration. For example, start = "2017:01:01:23:59:59", end = "2017:01:02:23:59:59",
granularity = "Day", it means that we need to find the logs within the range from Jan. 1st 2017 to Jan. 2nd 2017.

Example 1:

put(1, "2017:01:01:23:59:59");
put(2, "2017:01:01:22:59:59");
put(3, "2016:01:01:00:00:00");
retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Year"); // return [1,2,3], because
you need to return all logs within 2016 and 2017.
retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Hour"); // return [1,2], because 
you need to return all logs start from 2016:01:01:01 to 2017:01:01:23, where log 3 is left outside the range.


*/

//https://discuss.leetcode.com/category/803/design-log-storage-system

class LogSystem {
public:
    LogSystem() { }

    void put(int id, string time) {
        //why emplace?
        logs.emplace(time, id);
    }

    vector<int> retrieve(string s, string e, string gra) {
        vector<int> ids;
        int el = lengths[gra]; // effective length
        string es = s.substr(0, el); // effective start time string, eg.: 2017:01:01
        string ee = e.substr(0, el); // effective end time string, eg.: 2017:01:02

        for (auto it = logs.begin(); it != logs.end(); it++) {
            string time = it->first; // 2017:01:01:23:59:59
            int id = it->second;
            string etime = time.substr(0, el);
            //Do not forget the "="
            if (es <= etime && etime <= ee) {
                ids.push_back(id);
            }
        }
        return ids;
    }

private:
    multimap<string, int> logs;

    // effective lengths of time stamps for different granularity
    // look how this is intiailised
    map<string, int> lengths{ { "Year", 4 },{ "Month", 7 },{ "Day", 10 },{ "Hour", 13 },{ "Minute", 16 },{ "Second", 19 } };
};
