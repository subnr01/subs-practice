/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 
if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

*/


//look at below, the question is ambiqgious.
https://leetcode.com/problems/read-n-characters-given-read4-ii-call-multiple-times/discuss/49607/The-missing-clarification-you-wish-the-question-provided

int read4(char *buf);

class Solution {
private:
    int bp = 0;
    int len = 0;
    char buffer[4];
public:
    int read(char *buf, int n) {
        int i = 0;
        while (i < n) {
            if (bp == len) {
                // bp is reset, such that
                // when we read again, 
                // we will run it till len
                bp = 0;
                len = read4(buffer);
                // This is the exit condition
                // of the loop, do not forget.
                if (len == 0)
                    break;
            }
            // increment i and bp
            // if i > n, then bp is still valid
            // so the next call will start from
            // where it left off.
            buf[i++] = buffer[bp++];
        }

        return i;
    }
};
