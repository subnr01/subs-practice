/*


Given an expression such as expression = "e + 8 - a + 5" and an evaluation map such as {"e": 1}
(given in terms of evalvars = ["e"] and evalints = [1]), return a list of tokens representing 
the simplified expression, such as ["-1*a","14"]

An expression alternates chunks and symbols, with a space separating each chunk and symbol.
A chunk is either an expression in parentheses, a variable, or a non-negative integer.
A variable is a string of lowercase letters (not including digits.) Note that variables 
can be multiple letters, and note that variables never have a leading coefficient or unary operator like "2x" or "-x".
Expressions are evaluated in the usual order: brackets first, then multiplication, 
then addition and subtraction. For example, expression = "1 + 2 * 3" has an answer of ["7"].

The format of the output is as follows:

For each term of free variables with non-zero coefficient, we write the free variables
within a term in sorted order lexicographically. For example, we would never write a term like "b*a*c", only "a*b*c".
Terms have degree equal to the number of free variables being multiplied, counting 
multiplicity. (For example, "a*a*b*c" has degree 4.) We write the largest degree terms
of our answer first, breaking ties by lexicographic order ignoring the leading coefficient of the term.
The leading coefficient of the term is placed directly to the left with an asterisk separating 
it from the variables (if they exist.)  A leading coefficient of 1 is still printed.
An example of a well formatted answer is ["-2*a*a*a", "3*a*a*b", "3*b*b", "4*a", "5*c", "-6"] 
Terms (including constant terms) with coefficient 0 are not included.  For example, 
an expression of "0" has an output of [].
Examples:

Input: expression = "e + 8 - a + 5", evalvars = ["e"], evalints = [1]
Output: ["-1*a","14"]

Input: expression = "e - 8 + temperature - pressure",
evalvars = ["e", "temperature"], evalints = [1, 12]
Output: ["-1*pressure","5"]

Input: expression = "(e + 8) * (e - 8)", evalvars = [], evalints = []
Output: ["1*e*e","-64"]

Input: expression = "7 - 7", evalvars = [], evalints = []
Output: []

Input: expression = "a * b * c + b * a * c * 4", evalvars = [], evalints = []
Output: ["5*a*b*c"]

Input: expression = "((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c - a))",
evalvars = [], evalints = []
Output: ["-1*a*a*b*b","2*a*a*b*c","-1*a*a*c*c","1*a*b*b*b","-1*a*b*b*c","-1*a*b*c*c",
"1*a*c*c*c","-1*b*b*b*c","2*b*b*c*c","-1*b*c*c*c","2*a*a*b","-2*a*a*c","-2*a*b*b","2*a*c*c",
"1*b*b*b","-1*b*b*c","1*b*c*c","-1*c*c*c","-1*a*a","1*a*b","1*a*c","-1*b*c"]

*/


//Related topics: hash table, string, stack


//Soln 1 .. 13 ms
class Solution {
public:
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        unordered_map<string, int> mp;
        int n = evalvars.size();
        // create a map for variable value pairs
        for (int i = 0; i < n; ++i) mp[evalvars[i]] = evalints[i];
        // helper function is recursion using implicit stack
        int pos = 0;
        unordered_map<string, int> output = helper(expression, mp, pos);
        vector<pair<string, int>> ans(output.begin(), output.end());
        // sort result based on variable degree
        sort(ans.begin(), ans.end(), mycompare);
        vector<string> res;
        for (auto& p: ans) {
            // only consider non-zero coefficient variables
            if (p.second == 0) continue;
            res.push_back(to_string(p.second));
            if (p.first != "") res.back() += "*"+p.first;
        }
        return res;
    }
private:
    unordered_map<string, int> helper(string& s, unordered_map<string, int>& mp, int& pos) {
        // every operand is an unordered_map, including single variable or nested (a * b + a * c); 
        // if the operand is a number, use pair("", number)
        vector<unordered_map<string, int>> operands;
        vector<char> ops;
        ops.push_back('+');
        int n = s.size();
        while (pos < n && s[pos] != ')') {
            if (s[pos] == '(') {
               pos++;
               operands.push_back(helper(s, mp, pos));
            }
            else {
               int k = pos;
               while (pos < n && s[pos] != ' ' && s[pos] != ')') pos++;
               string t = s.substr(k, pos-k);
               bool isNum = true;
               for (char c: t) {
                   if (!isdigit(c)) isNum = false;
               }
               unordered_map<string, int> tmp;
               if (isNum) 
                   tmp[""] = stoi(t);
               else if (mp.count(t)) 
                   tmp[""] = mp[t];
               else              
                   tmp[t] = 1;
               operands.push_back(tmp);
            }
            if (pos < n && s[pos] == ' ') {
               ops.push_back(s[++pos]);
               pos += 2;
            }
        }
        pos++;
        return calculate(operands, ops);
    }
    unordered_map<string, int> calculate(vector<unordered_map<string, int>>& operands, vector<char>& ops) {
        unordered_map<string, int> ans;
        int n = ops.size();
        for (int i = n-1; i >= 0; --i) {
            unordered_map<string, int> tmp = operands[i];
            while (i >= 0 && ops[i] == '*')
                tmp = multi(tmp, operands[--i]);
            int sign = ops[i] == '+'? 1: -1;
            for (auto& p: tmp) ans[p.first] += sign*p.second;
        }
        return ans;
    }
    unordered_map<string, int> multi(unordered_map<string, int>& lhs, unordered_map<string, int>& rhs) {
        unordered_map<string, int> ans;
        int m = lhs.size(), n = rhs.size();
        for (auto& p: lhs) {
            for (auto& q: rhs) {
                // combine and sort the product of variables
                string t = combine(p.first, q.first);
                ans[t] += p.second*q.second;
            }
        }
        return ans;
    }
    string combine(const string& a, const string& b) {
        if (a == "") return b;
        if (b == "") return a;
        vector<string> strs = split(a, '*');
        for (auto& s: split(b, '*')) strs.push_back(s);
        sort(strs.begin(), strs.end());
        string s;
        for (auto& t: strs) s += t +'*';
        s.pop_back();
        return s;
    }
    static vector<string> split(const string& s, char c) {
        vector<string> ans;
        int i = 0, n = s.size();
        while (i < n) {
            int j = i;
            i = s.find(c, i);
            if (i == -1) i = n;
            ans.push_back(s.substr(j, i-j));
            i++;
        }
        return ans;
    }
    static bool mycompare(pair<string, int>& a, pair<string, int>& b) {
        string s1 = a.first, s2 = b.first;
        vector<string> left = split(s1, '*'); 
        vector<string> right = split(s2, '*');
        return left.size() > right.size() || (left.size() == right.size() && left < right);
    }  
};


//Soln 2 58ms
class Solution {
public:
    
    
    //sort the final compound result by the number of exps, for same number of exps, sort by exp alphebet order.
    struct MyExpStrVecComp
    {
        bool operator()( pair<vector<string>,string> &a, pair<vector<string>,string> &b )
        {
            if ( a.first.size() == b.first.size() )
                return a.first < b.first;
            return a.first.size() > b.first.size();
        }
    };
    
    //split a compound exp into values by token "*"
    void SplitExp(const string &exp, vector<string> &expStrs)
    {
        int i =0;
        int pos = exp.find('*', i);
        while ( pos != -1 )
        {
            string temp = exp.substr(i,pos-i);
            expStrs.push_back(temp);
            i= pos+1;
            pos = exp.find('*', i);
        }
        expStrs.push_back(exp.substr(i));
    }
    
    //multiple two groups of expression, e.g. (e+8)*(e-8) = e*e-64;
    void MultiTwoExps( unordered_map<string,int> &exps1, unordered_map<string,int> &exps2, unordered_map<string,int> &res)
    {
        for ( auto exp1: exps1 )
        {
            for ( auto exp2: exps2 )
            {
                int count = exp1.second * exp2.second;
                if ( exp1.first == "1" )
                    res[exp2.first]+=count;
                else if ( exp2.first == "1")
                    res[exp1.first]+=count;
                else
                {
                    vector<string> expStrs;
                    SplitExp(exp1.first,expStrs);
                    SplitExp(exp2.first,expStrs);
                    
                    //sort(expStrs.begin(), expStrs.end(), MyExpStrVecComp);
                    sort(expStrs.begin(), expStrs.end());
                    
                    string newExpStr;
                    for ( auto expStr:expStrs )
                    {
                        newExpStr.append(expStr);
                        newExpStr.push_back('*');
                    }
                    newExpStr.pop_back();
                    
                    res[newExpStr]+=count;
                }
            }
        }
    }
    // get the next expression
    void GetNextExpression( string &expression, int len, int &i, unordered_map<string,int> &evals, int op, unordered_map<string,int> &res )
    {
        if ( i >= len )
            return;
        // the result is a group of expression .e.g (e-8)
        if (  expression[i] == '(')
        {
            ++i;
            basicCalculatorIVDo( expression, len, i, evals, res);
            if ( op == -1 )
            {
                for ( auto &exp : res )
                    exp.second*=-1;
            }
        }
        else // the result is a single expression, e.g. e or -8
        {
            bool allDigit = true;
            string exp;
            while ( i < len && ( (expression[i] >='a' && expression[i] <='z') || (expression[i] >='0' && expression[i] <='9') ) )
            {
                exp.push_back(expression[i]);
                if (expression[i] >='a' && expression[i] <='z')
                    allDigit = false;
                ++i;
            }
            
            if ( allDigit )
            {
                int count = stoi(exp);
                if ( op == -1)
                    res["1"] = -count;
                else
                    res["1"] = count;
            }
            else
            {
                if ( evals.find(exp) != evals.end() )
                {
                    if ( op == -1)
                        res["1"] = -evals[exp];
                    else
                        res["1"] = evals[exp];
                }
                else
                {
                    if ( op == -1)
                        res[exp] = -1;
                    else
                        res[exp] = 1;
                }
            }
        }
    }
    
    void basicCalculatorIVDo( string &expression, int len, int &i, unordered_map<string,int> &evals, unordered_map<string,int> &res)
    {
        vector<unordered_map<string,int>> tempRes;
        
        int op = 1;
        while ( i < len )
        {
            if ( expression[i] == ' ')
                ++i;
            else if ( expression[i] == '+')
            {
                op = 1;
                ++i;
            }
            else if ( expression[i] == '-')
            {
                op = -1;
                ++i;
            }
            else if ( expression[i] == '*')
            {
                op = 2;
                ++i;
            }
            else if ( expression[i] == ')' )
            {
                ++i;
                break;
            }
            else
            {
                unordered_map<string,int> exps;
                GetNextExpression( expression, len, i, evals, op, exps);
                
                if ( op == 2 ) // for *, do the multiple with the latest group of expression
                {
                    unordered_map<string,int> expsNew;
                    MultiTwoExps( tempRes.back(), exps, expsNew );
                    tempRes.pop_back();
                    tempRes.push_back(expsNew);  
                }
                else // for + and -, add expressions to the temp result
                    tempRes.push_back(exps);
            }                 
        }
        
        //process the final results
        for ( auto &expsTemp : tempRes )
        {
            for ( auto &expTemp : expsTemp )
            {
                res[expTemp.first]+=expTemp.second;
            }
        }
        
        for ( auto it = res.begin(); it != res.end(); )
        {
            if ( it->second == 0 ) // skip the expression with count is 0
            {
                it = res.erase(it);
            }
            else
                ++it;
        }
    }
    
    
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        unordered_map<string,int> evals;
        int len = evalvars.size();
        for ( int i = 0; i < len; ++i )
            evals[evalvars[i]] = evalints[i];
        
        //get the expressions in a compound format,{compound exp,count} e.g. {a*a*b*b,-1}
        int explen = expression.length();
        int i = 0;
        unordered_map<string,int> exps;
        basicCalculatorIVDo( expression, explen, i, evals, exps);
        
        //sort the coumpound expressions by number of single expression in the compound expression(first order),
        // and alphet order of each single expression, e.g.
        // a*a*b*b","a*a*b*c","b*b*b","*b*b*c"
        vector<pair<vector<string>,string>> resPreOrder;
        string consExp; //consExp for the constant number which will be the last one in the final result
        for ( auto exp : exps )
        {
            int count = exp.second;
            if ( count == 0 )
                continue;
            
            if ( exp.first != "1")
            {
                vector<string> expStrs;
                SplitExp(exp.first, expStrs);
                
                resPreOrder.push_back( {expStrs, exp.first} );
            }
            else
                consExp = to_string(count);
        }
        sort( resPreOrder.begin(), resPreOrder.end(), MyExpStrVecComp() );
        
        //assemble with the count into the final format
        // -1*a*a*b*b","2*a*a*b*c","1*b*b*b","-1*b*b*c"
        vector<string> res;
        for ( auto &ordered : resPreOrder )
        {
            string expStr = ordered.second;
            int count = exps[expStr];
            
            string temp = to_string(count);
            temp.push_back('*');
            temp.append(expStr);
            res.push_back(temp);
        }

        if ( consExp.length() != 0 )
            res.push_back(consExp);
        
        return res;
    }
};



