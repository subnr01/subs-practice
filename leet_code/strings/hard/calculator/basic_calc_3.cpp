/*
Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus
sign -, non-negative integers and empty spaces .

The expression string contains only non-negative integers, +, -, *, / operators , 
open ( and closing parentheses ) and empty spaces . The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will
be in the range of [-2147483648, 2147483647].

Some examples:

"1 + 1" = 2
" 6-4 / 2 " = 4
"2*(5+5*2)/3+(6/2+8)" = 21
"(2+6* 3+5- (3*14/7+2)*5)+3"=-12


*/


class Solution {
public:
    int calculate(string s) {
        int i = 0;
        return parseExpr(s, i);
    }
    
    int parseExpr(string& s, int& i) {
        vector<int> nums;
        char op = '+';
        for (; i < s.length() && op != ')'; i++) {
            if (s[i] == ' ') continue;
            int n = s[i] == '(' ? parseExpr(s, ++i) : parseNum(s, i);
            switch(op) {
                case '+' : nums.push_back(n); break;
                case '-' : nums.push_back(-n); break;
                case '*' : nums.back() *= n; break;
                case '/' : nums.back() /= n; break;
            }            
            op = s[i];
        }
        int res = 0;
        for (int n : nums) res += n;
        return res;
    }
    
    int parseNum(string& s, int& i) {
        int n = 0;
        while(i < s.length() && isdigit(s[i]))
            n = s[i++] - '0' + 10 * n;
        return n;
    }
};




//using stack
class Solution {
public:
	int calculate(string s) {
		stack<int> nums;
		stack<char> ops;
		int num = 0;
		for (int i = 0; i < s.length(); i++) {
			char c = s[i];
			if (c == ' ') continue;
			if (isdigit(c)) {
				num = c - '0';
				while (i < s.length() - 1 && isdigit(s[i + 1])) {
					num = num * 10 + s[i + 1] - '0';
					i++;
				}
				nums.push(num);
				num = 0;
			}
			else {
				if (c == '(') ops.push(c);
				if (c == ')') {
					while (ops.top() != '(') nums.push(eval(ops, nums));
					ops.pop();
				}
				if (c == '+' || c == '-' || c == '*' || c == '/') {
					while (!ops.empty() && lowPriority(c, ops.top())) nums.push(eval(ops, nums));
					ops.push(c);
				}
			}
		}
		while (!ops.empty()) {
			nums.push(eval(ops, nums));
		}
		return nums.top();
	}

private:
	int eval(stack<char>& ops, stack<int>& nums) {
		char op = ops.top();
		ops.pop();
		int num2 = nums.top();
		nums.pop();
		int num1 = nums.top();
		nums.pop();
		if (op == '+') return num1 + num2;
		if (op == '-') return num1 - num2;
		if (op == '*') return num1 * num2;
		if (op == '/' && num2 != 0) return num1 / num2;
		return 0;
	}

	bool lowPriority(char cur, char pre) {
		if (pre == '(' || pre == ')') return false;
		if ((cur == '*' || cur == '/') && (pre == '+' || pre == '-')) return false;
		return true;
	}
};




