
/*

Given a string representing the file system in the above format, return the length of the longest absolute path to file in the 
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
