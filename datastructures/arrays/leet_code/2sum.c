/*

Sum of two numbers

*/

class Solution {
public:
      vector<int> twoSum(vector<int> &num, int target) {
          unordered_map<int, int> mapping;
          vector<int> result;
          for (int i = 0; i < num.size(); i++) {
              mapping[num[i]] = i;
          }
          for (int i = 0; i < num.size(); i++) {
              const int gap = target - num[i];
              if (mapping.find(gap) != mapping.end() && mapping[gap] > i) {  // the number must exist and it should not be equal to itself	
                  result.push_back(i + 1);
                  result.push_back(mapping[gap] + 1);
                  break;
} }
          return result;
      }
};



