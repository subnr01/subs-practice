/*
Suppose you are at a party with n people (labeled from 0 to n - 1) and among them, there may exist one celebrity.
The definition of a celebrity is that all the other n - 1 people know him/her but he/she does not know any of them.

Now you want to find out who the celebrity is or verify that there is not one. The only thing you are allowed to
do is to ask questions like: "Hi, A. Do you know B?" to get information of whether A knows B. You need to find out
the celebrity (or verify there is not one) by asking as few questions as possible (in the asymptotic sense).

You are given a helper function bool knows(a, b) which tells you whether A knows B. Implement a function 
int findCelebrity(n), your function should minimize the number of calls to knows.

Note: There will be exactly one celebrity if he/she is in the party. Return the celebrity's label 
if there is a celebrity in the party. If there is no celebrity, return -1.

*/


// Forward declaration of the knows API.
bool knows(int a, int b);

class Solution {
public:
    int findCelebrity(int n) {
        
        int candidate = 0;
        
        for (int i = 1; i < n; i++)
        {
            // Does i know the candidate, if no
            // then reset the candidate function.
            // what happens if we get two candidate funcitons.
            // the candidate will have the outer index.
            if (knows(i, candidate) == false) {
                candidate = i;
            }
        }
        
        /* 
        If we found two candidates, but recorded only one in the
        last loop iteration, we need to make sure that these two
        come face to face to decide whether they know each other 
        or not
        */
        for (int j = 0; j < n; j++)
        {
            if (j == candidate) continue;
            // if J does not know the candidate or 
            // candidate knows j then exit.
            // the condition must be, j knows the candidate and 
            // the candidate does not know j(keeping with the requirements)
            // 
            if (!knows(j, candidate) || knows(candidate, j)) {
                return -1;
            }
        }
        
        return candidate;
        
    }
};
