/*
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 
if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

*/


int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    queue<int> left;
    int read(char *buf, int n) {
        int len = 0;
        int c;
        while (left.size() > 0) {
            buf[len++] = left.front();
            left.pop();
            if (len == n) return len;
        }
        
        while (len < n) {
            c = read4(buf+len);
            len += c;
            if (c < 4) break;
        }
        
        for (int i=n; i<len; i++) {
            left.push(buf[i]);
        }
        int e = min(len, n);
        buf[e] = '\0';
        return e;
    }
};

