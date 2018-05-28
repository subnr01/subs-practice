



//Not a good one for interview, but take a look
class Solution {
public:
    int evaluate(string expression) {
        unordered_map<string,int> myMap;
        return help(expression,myMap);
    }
    
    int help(string expression,unordered_map<string,int> myMap) {
        if ((expression[0] == '-') || (expression[0] >= '0' && expression[0] <= '9'))
            return stoi(expression);
        else if (expression[0] != '(')
            return myMap[expression];
        //to get rid of the first '(' and the last ')'
        string s = expression.substr(1,expression.size()-2);
        int start = 0;
        string word = parse(s,start);
        if (word == "let") {
            while (true) {
                string variable = parse(s,start);
                //if there is no more expression, simply evaluate the variable
                if (start > s.size())
                    return help(variable,myMap);
                string temp = parse(s,start);
                myMap[variable] = help(temp,myMap);                    
            }
        }
        else if (word == "add") 
            return help(parse(s,start),myMap) + help(parse(s,start),myMap);
        else if (word == "mult") 
            return help(parse(s,start),myMap) * help(parse(s,start),myMap);
    }
    
    //function to seperate each expression
    string parse(string &s,int &start) {
        int end = start+1, temp = start, count = 1;
        if (s[start] == '(') {
            while (count != 0) {
                if (s[end] == '(')
                    count++;
                else if (s[end] == ')')
                    count--;
                end++;
            }
        }
        else {
            while (end < s.size() && s[end] != ' ')
                end++;
        }
        start = end+1;
        return s.substr(temp,end-temp);
    }
};

//non recursive soln
class Solution {
public:
    int evaluate(string expression) {        
        scopes_.clear();
        int pos = 0;
        return eval(expression, pos);
    }
private:
    int eval(const string& s, int& pos) {
        scopes_.push_front(unordered_map<string, int>());
        int value = 0; // The return value of current expr        
        if (s[pos] == '(') ++pos;
 
        // command, variable or number
        const string token = getToken(s, pos);
 
        if (token == "add") {
            int v1 = eval(s, ++pos);
            int v2 = eval(s, ++pos);
            value = v1 + v2;
        } else if (token == "mult") {
            int v1 = eval(s, ++pos);
            int v2 = eval(s, ++pos);
            value = v1 * v2;
        } else if (token == "let") {
            string var;
            // expecting " var1 exp1 var2 exp2 ... last_expr)"
            while (s[pos] != ')') {
                ++pos;
                // Must be last_expr
                if (s[pos] == '(') {
                    value = eval(s, ++pos);
                    break;
                }                
                // Get a token, could be "x" or "-12" for last_expr
                var = getToken(s, pos);                
                // End of let, var is last_expr
                if (s[pos] == ')') {
                    if (isalpha(var[0]))
                        value = getValue(var);
                    else
                        value = stoi(var);
                    break;
                }
                // x -12 -> set x to -12 and store in the current scope and take it as the current return value
                value = scopes_.front()[var] = eval(s, ++pos);
            }
        } else if (isalpha(token[0])) {            
            value = getValue(token); // symbol
        } else {            
            value = std::stoi(token); // number
        }
        if (s[pos] == ')') ++pos;        
        scopes_.pop_front();        
        return value;
    }
    
    int getValue(const string& symbol) {
        for (const auto& scope : scopes_)        
            if (scope.count(symbol)) return scope.at(symbol);
        return 0;
    }
    
    // Get a token from current pos.
    // "let x" -> "let"
    // "-12 (add x y)" -> "-12"
    string getToken(const string& s, int& pos) {        
        string token;
        while (pos < s.length()) {            
            if (s[pos] == ')' || s[pos] == ' ') break;
            token += s[pos++];
        }
        return token;
    }
    
    deque<unordered_map<string, int>> scopes_; 
};
