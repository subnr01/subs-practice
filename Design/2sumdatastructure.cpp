/*

Design and implement a TwoSum class. It should support the following operations: add and find.

add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,

add(1); 
add(3); 
add(5);
find(4) -> true
find(7) -> false


*/

class TwoSum {
  unordered_map<int, int> ctr;
public:
  void add(int number) {
    ctr[number]++;
  }

  bool find(int value) {
    for (auto nc : ctr)
      if (ctr.count(value - nc.first) && (nc.first != value - nc.first || nc.second > 1))
        return true;
    return false;
  }
};
