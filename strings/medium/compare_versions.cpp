/*
Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the
fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:
0.1 < 1.1 < 1.2 < 13.37
*/




//This is really a good telephonic interview question
// The inputs could be of different size.
int compareVersion(string version1, string version2) {
    int i = 0; 
    int j = 0;
    int n1 = version1.size(); 
    int n2 = version2.size();
    
    int num1 = 0;
    int num2 = 0;
    
    //Look at the "OR" condition below.
    // This ensures that we continue processing
    // even if we run out of length in one
    // of the strings
    while(i<n1 || j<n2)
    {
        while(i<n1 && version1[i]!='.'){
            num1 = num1*10+(version1[i]-'0');
            i++;
        }
        
        while(j<n2 && version2[j]!='.'){
            num2 = num2*10+(version2[j]-'0');;
            j++;
        }
        
        if(num1>num2) return 1;
        else if(num1 < num2) return -1;
        
        // Setting num(s) back to 0 is
        // very important.
        num1 = 0;
        num2 = 0;
        i++;
        j++;
    }
    
    return 0;
}


//crazy version
class Solution {
public:
    int compareVersion(string version1, string version2) {
        //Replace "." with space (' ') in the string
        for(auto& w : version1)
        {
            if (w == '.') {
                w=' ';
            }
        }
        //Replace "." with space (' ') in the string
        for(auto& w : version2)
        {
            if (w == '.') {
                w=' ';
            }
        }
        cout<<endl<<" version1 " <<version1;
        cout<<endl<<" version2 " <<version2;
        //Tokenize with space (' ') as delimiter
        istringstream s1(version1), s2(version2);
        while(1) {
            int n1,n2;
            if (!(s1 >> n1) ) n1 = 0;
            if (!(s2 >> n2) ) n2 = 0;
            if (!s1 && !s2) return 0;
            cout<<endl<<" n1 " <<n1;
            cout<<endl<<" n2 " <<n2;
            if (n1<n2) return -1;
            if (n1>n2) return 1;
        }
        
    }
};

//Input
("10.9", "10.3")

//Output
version1 10 9
 version2 10 3
 n1 10
 n2 10
 n1 9
 n2 3


