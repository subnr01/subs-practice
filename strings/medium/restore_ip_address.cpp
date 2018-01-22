/*

Restore IP Addresses

Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)


*/

//related topics backtracking


class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        string ip;
        dfs(s,0,0,ip,result); //paras:string s,start index of s,step(from0-3),intermediate ip,final result
        return result;
    }
    void dfs(string s,int start,int step,string ip,vector<string>& result){
        
        //did we get a full ipaddress
        // notice step should be equal to 4.
        // and start should be equal to the
        // size of the string.
        if(start==s.size() && step==4){
            ip.erase(ip.end()-1); //remove the last '.' from the last decimal number
            result.push_back(ip);
            return;
        }
        /*
        This step is very important.
        This acts as the exit for the backtrack.
        This helps us to verify whether the "." is 
        placed at the right spot given the size of the 
        input string.
        */
        if(s.size()-start>(4-step)*3) {
            //cout<<done1;
            return;
        };
        
        int num=0;
        
        //start is not 0 everytime, but only
        // in the first call.
        for(int i=start;i<start+3;i++){
            num=num*10+(s[i]-'0');
            if(num<=255){
                ip+=s[i];
                //DFS with both i++ and step++
                dfs(s,i+1,step+1,ip+'.',result);
            }
            // we need the below condition as we do not
            // want 0 prefix on real numbers
            if(num==0) {
                break;
            }
        }
    }
};


Input:
"010010"
    
Output:
["0.10.0.10","0.100.1.0"]

Output:

2.
done1
25.
25.5.
done1
25.52.
done1
255.
255.2.
done1
255.25.
255.25.5.
done1
255.25.51.
done1
255.255.
255.255.1.
done1
255.255.11.
255.255.11.1.
done1
255.255.11.13.
done1
255.255.11.135.
255.255.111.
255.255.111.3.
done1
255.255.111.35.Hello, World!
