/*
Get the compliment of a number
*/

class Solution {
public:
    int findComplement(int num) {
        unsigned int mask = ~0;
        
        while(num & mask) {
            mask = mask << 1;
        }
        return ~mask & ~num;
    }
};

