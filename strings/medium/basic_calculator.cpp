/*

Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer 
division should truncate toward zero.

You may assume that the given expression is always valid.

Some examples:
"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5
Note: Do not use the eval built-in library function.
*/


int calculate(string s) {
    stack<int> myStack;
    char sign = '+';
    int res = 0, tmp = 0;
    for (unsigned int i = 0; i < s.size(); i++) {
        if (isdigit(s[i]))
            tmp = 10*tmp + s[i]-'0';
        //if it is not a digit
        if (!isdigit(s[i]) && !isspace(s[i]) || i == s.size()-1) {
            if (sign == '-')
                myStack.push(-tmp);
            else if (sign == '+')
                myStack.push(tmp);
            else {
                //if sign is not '+' or '-'
                //multiply with top and pop, and
                //put it back in
                
                int num;
                if (sign == '*' )
                    num = myStack.top()*tmp;
                else
                    num = myStack.top()/tmp;
                //Replacing the top with the
                //result
                myStack.pop();
                myStack.push(num);
            }
            //temp and sign reset
            sign = s[i];
            tmp = 0;
        }
    }
    
    //Here is where addition happens
    while (!myStack.empty()) {
        res += myStack.top();
        myStack.pop();
    }
    return res;
}


//stephen
class Solution {
public:
    int calculate(string s) {
    istringstream in('+' + s + '+');
    long long total = 0, term = 0, n;
    char op;
    while (in >> op) {
        if (op == '+' or op == '-') {
            total += term;
            in >> term;
            term *= 44 - op;
        } else {
            in >> n;
            if (op == '*')
                term *= n;
            else
                term /= n;
        }
    }
    return total;
}
};
