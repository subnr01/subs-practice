/*
Given a digit string, return all possible letter combinations that the number could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below.
Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
*/
//BFS single queue
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return vector<string>();
        }
        vector<string> words{ " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        deque<string> q;
        q.push_back("");

        for (char digit : digits) {
            int d = digit - '0';
            for (int i = q.size(); i > 0; i--) {
                string token = q.front();
                q.pop_front();
                for (char ch : words[d]) {
                    q.push_back(token + ch);
                }
            }
        }

        return vector<string>(q.begin(), q.end());
    }
};

//BFS double queue
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return vector<string>();
        }
        vector<string> words{ " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        deque<string> q, next;
        q.push_back("");

        for (char digit : digits) {
            int d = digit - '0';
            while (!q.empty()) {
                string token = q.front();
                q.pop_front();
                for (char ch : words[d]) {
                    next.push_back(token + ch);
                }
            }
            swap(q, next);
        }

        return vector<string>(q.begin(), q.end());
    }
};


//Rolling vector
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (!digits.size()) {
            return {};
        }

        vector<string> combs{ "" };
        vector<string> chars = { "0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        for (char digit : digits) {
            int d = digit - '0';
            vector<string> next;
            for (string comb : combs) {
                for (char ch : chars[d]) {
                    next.push_back(comb + ch);
                }
            }
            combs.swap(next);
        }

        return combs;
    }
};

//BFS - rolling vector - Recycle Next
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (!digits.size()) {
            return {};
        }

        vector<string> combs{ "" }, next;
        vector<string> chars = { "0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        for (char digit : digits) {
            int d = digit - '0';
            for (string comb : combs) {
                for (char ch : chars[d]) {
                    next.push_back(comb + ch);
                }
            }
            combs.swap(next);
            next.clear();
        }

        return combs;
    }
};

//backtracking
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (!digits.size()) {
            return {};
        }

        vector<string> combs;
        const vector<string> chars = { "0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        string builder;
        build(builder, 0, digits, chars, combs);
        return combs;
    }

    /**
     * start with an empty builder, for every digit, use all chars it represents to attach to the builder, when i 
     * reaches the end of digits, push builder to result;
     */
    void build(string builder, int i, const string& digits, const vector<string>& chars, vector<string>& combs) {
        if (i == digits.size()) {
            combs.push_back(builder);
            return;
        }

        int d = digits[i] - '0';
        for (char ch : chars[d]) {
            build(builder + ch, i + 1, digits, chars, combs);
        }
    }
};
