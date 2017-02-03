/*
Convert number to hexadecimal
*/


class Solution {
public:
    string toHex(int n) {
        
        string hex ="0123456789abcdef";
        if (n == 0) {
            return "0";
        }
        
        string result;
        int count = 0;
        unsigned int num = static_cast<unsigned int>(n);
        while(num)
        {
            result = hex[(num & 0xf)] + result;
            num >>= 4;
        }
        
        return result;
    }
};


/* What happens if the number is signed */
