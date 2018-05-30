/*
Given a chemical formula (given as a string), return the count of each atom.

An atomic element always starts with an uppercase character, then zero or more lowercase letters, 
representing the name.

1 or more digits representing the count of that element may follow if the count is greater than 1. 
If the count is 1, no digits will follow. For example, H2O and H2O2 are possible, but H1O2 is impossible.

Two formulas concatenated together produce another formula. For example, H2O2He3Mg4 is also a formula.

A formula placed in parentheses, and a count (optionally added) is also a formula. For example, (H2O2) 
and (H2O2)3 are formulas.

Given a formula, output the count of all elements as a string in the following form: the first name
(in sorted order), followed by its count (if that count is more than 1), followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.

Example 1:
Input: 
formula = "H2O"
Output: "H2O"
Explanation: 
The count of elements are {'H': 2, 'O': 1}.
Example 2:
Input: 
formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation: 
The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.
Example 3:
Input: 
formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation: 
The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.


*/


//Related topics:  hash table, stack, recursion

//REcursive parser
class Solution {
public:
    string countOfAtoms(string formula) {
        string output;
        const int n = formula.size();
        int i = 0;
        map<string, int> counts = parseFormula(formula, i);
        for (pair<string, int> p : counts) {
            output += p.first;
            if (p.second > 1) output += to_string(p.second);
        }
        return output;
    }

private:
    map<string, int> parseFormula(string& s, int& i) {
        map<string, int> counts;
        const int n = s.size();
        while (i < n && s[i] != ')') {
            map<string, int> cnts = parseUnit(s, i);
            merge(counts, cnts, 1);
        }
        return counts;
    }

    map<string, int> parseUnit(string& s, int& i) {
        map<string, int> counts;
        const int n = s.size();
        if (s[i] == '(') {
            map<string, int> cnts = parseFormula(s, ++i); // ++i for '('
            int digits = parseDigits(s, ++i); // ++i for ')'
            merge(counts, cnts, digits);
        }
        else {
            int i0 = i++; // first letter
            while (i < n && islower(s[i])) { i++; }
            string atom = s.substr(i0, i - i0);
            int digits = parseDigits(s, i);
            counts[atom] += digits;
        }
        return counts;
    }

    int parseDigits(string& s, int& i) {
        int i1 = i;
        while (i < s.size() && isdigit(s[i])) { i++; }
        int digits = i == i1 ? 1 : stoi(s.substr(i1, i - i1));
        return digits;
    }

    void merge(map<string, int>& counts, map<string, int>& cnts, int times) {
        for (pair<string, int> p : cnts) counts[p.first] += p.second * times;
    }
};


//stack
class Solution {
public:
    string countOfAtoms(string f) {
        stack<map<string,int>> st;
        map<string, int> cur;
        for (int i = 0; i < f.size();) {
            if (f[i] == '(') {
                st.push(move(cur));
                cur = map<string,int>();
                ++i;
            }
            else if (f[i] == ')') {
                int j = i+1;
                int num = 0;
                while (j < f.size() && isdigit(f[j])) num = num*10 + (f[j++] - '0');
                num = max(num,1);
                for (auto p:cur) st.top()[p.first] += p.second * num;
                cur = move(st.top());
                st.pop();
                i = j;
            }
            else {
                int j = i + 1;
                while (j < f.size() && f[j] >= 'a' && f[j] <= 'z') ++j;
                auto name = f.substr(i,j-i);
                int num = 0;
                while (j < f.size() && isdigit(f[j])) num = num*10 + (f[j++] - '0');
                num = max(num,1);
                cur[name] += num;
                i = j;
            }
        }
        string ans;
        for (auto p:cur) {
            ans += p.first;
            if (p.second > 1) ans += to_string(p.second);
        }
        
        return ans;
    }
};

