/*

Employee Importance
---------------------

You are given a data structure of employee information, which includes the employee's unique id, 
his importance value and his direct subordinates' id.

For example, employee 1 is the leader of employee 2, and employee 2 is the leader of employee 3. 
They have importance value 15, 10 and 5, respectively. Then employee 1 has a data structure like [1, 15, [2]],
and employee 2 has [2, 10, [3]], and employee 3 has [3, 5, []]. Note that although employee 3 is also a 
subordinate of employee 1, the relationship is not direct.

Now given the employee information of a company, and an employee id, you need to return the total 
importance value of this employee and all his subordinates.

Example 1:
Input: [[1, 5, [2, 3]], [2, 3, []], [3, 3, []]], 1
Output: 11
Explanation:
Employee 1 has importance value 5, and he has two direct subordinates: employee 2 and employee 3. 
They both have importance value 3. So the total importance value
of employee 1 is 5 + 3 + 3 = 11.

*/


//Related topics: DFS, hash table



//my soln
class Solution {
unordered_map<int, Employee*> myMap;
public:
    int getImportance(vector<Employee*> employees, int id) {
        int n = employees.size();
        if (n == 0) {
            return 0;
        }
        
        //use the map to connect the Employee and the employee id.
        for (int i = 0; i < n; i++)
        {
            myMap[employees[i]->id] = employees[i];
        }
        
        //use the id to perform the dfs
        return dfs(id);
    }
    
    int dfs(int id)
    {
        Employee *employee = myMap[id];
        int importance = employee->importance;
        vector<int> temp = employee->subordinates;
        
        //recursively traverse the subordinate array to
        //obtain the cumulative importance.
        for (int i = 0; i < temp.size(); i++)
        {
            importance += dfs(temp[i]);
        }
        
        return importance;
    }
    
};
