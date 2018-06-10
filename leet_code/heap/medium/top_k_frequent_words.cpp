/*
Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency, 
then the word with the lower alphabetical order comes first.

Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
    with the number of occurrence being 4, 3, 2 and 1 respectively.
Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Input words contain only lowercase letters.
Follow up:
Try to solve it in O(n log k) time and O(n) extra space.

*/

/***************************************

LOGIC:
Problem statement:
We have been given a list of words and we have to find out
the words that are occurring k times.

Solution:
We have to keep a count of the words to find the number of occcurences.
So we use a map to keep count.

We will setup the priority queue such that the topmost
element is the min, and we keep inserting elements one by
one and stop when it exceeds k and pop the top.

Since the elements are inserted in ascending order, the top
has always the smallest number of occurrences and hence will 
get removed and at the end, we will left with k elements
that we will put in a vector and return back.

We will always have two elements in the priority queue at the end.


Time complexity: O(NLogK), N elements K at a time in the heap.
Space complexity: O(N) for the map
*************************************/



//C++
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> freq;
        for(auto w : words){
            freq[w]++;
        }
        
        auto comp = [&](const pair<string,int>& a, const pair<string,int>& b) {
            return a.second < b.second || (a.second == b.second && a.first > b.first);
        };
        typedef priority_queue< pair<string,int>, vector<pair<string,int>>, decltype(comp) > my_priority_queue_t;
        my_priority_queue_t  pq(comp);
        
        for(auto w : freq ){
            pq.emplace(w.first, w.second); //what does emplace do
            
        }
        
        vector<string> output;
        for (int i = 0; i < k; i++)
        {
            output.push_back(pq.top().first);
            pq.pop();
        }
        return output;
    }
};

/*
The size of the priority queue is k. Each insertion takes logk time and 
we are iterating over n distinct words in the worst case and inserting them 
into the priority queue which makes the total runtime nlogk.
*/
