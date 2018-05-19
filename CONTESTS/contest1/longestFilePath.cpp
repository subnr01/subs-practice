
/*

The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:

dir
    subdir1
        file1.ext
        subsubdir1
    subdir2
        subsubdir2
            file2.ext
            
The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.ext and 
an empty second-level sub-directory subsubdir1. subdir2 contains a second-level sub-directory subsubdir2 
containing a file file2.ext.

We are interested in finding the longest (number of characters) absolute path to a file within our file system. 
For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext",
and its length is 32 (not including the double quotes).



Given a string representing the file system in the above format, return the length of the longest absolute path to 
file in the 
abstracted file system. If there is no file in the system, return 0.

*/



class Solution {
public:
    int lengthLongestPath(string input) {
        istringstream ss(input);
        string token;
        size_t max_len = 0;
        unordered_map<int, int> path_len;
        path_len[0] = 0;
        while (getline(ss, token)) {
            auto pos = token.find_last_of("\t");
            string name = (pos != std::string::npos) ? token.substr(pos + 1) : token;
            
            int depth = token.size() - name.size();
            if (token.find(".") != std::string::npos) {
                max_len = max(max_len, path_len[depth] + name.size());
            } else {
                path_len[depth + 1] = path_len[depth] + name.size() + 1;
            }
        }
        return max_len;
    }
};
