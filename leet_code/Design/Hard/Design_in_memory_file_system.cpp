/*

Design an in-memory file system to simulate the following functions:

ls: Given a path in string format. If it is a file path, return a list that
only contains this file's name. If it is a directory path, return the list of
file and directory names in this directory. Your output (file and directory names 
together) should in lexicographic order.

mkdir: Given a directory path that does not exist, you should make a new directory 
according to the path. If the middle directories in the path don't exist either, you should 
create them as well. This function has void return type.

addContentToFile: Given a file path and file content in string format. If the file doesn't 
exist, you need to create that file containing given content. If the file already exists, you need 
to append given content to original content. This function has void return type.

readContentFromFile: Given a file path, return its content in string format.

 

Example:

Input: 
["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]
[[],["/"],["/a/b/c"],["/a/b/c/d","hello"],["/"],["/a/b/c/d"]]

Output:
[null,[],null,null,["a"],"hello"]


*/

//Standard Solution
// Read the explanation, especially performance analysis.
struct File {
    bool isFile;
    string content;
    unordered_map<string, File*> child;
    
    File() {
        isFile = false;
    }
};

struct fs {
    File *root;
    
    fs(){
        root = new File();
    }
    
    void mkdir(string str){
        auto cur = root;
        int n = str.size(), i = 1;
        while(i < n)
        {
            int j = i;
            while(j < n && str[j] != '/') j++;
            string sub = str.substr(i, j - i);
            if(cur->child.count(sub) == 0) {
                cur->child[sub] = new File();
            }
            cur = cur->child[sub];
            i = j + 1;
        }
    }
    
    string read (string str){
        auto cur = root;
        int n = str.size(), i = 1;
        while(i < n){
            int j = i;
            while(j < n && str[j] != '/') j++;
            string sub = str.substr(i, j - i);
            cur = cur->child[sub];
            i = j + 1;
        }
        
        return cur->content;
    }
    
    void write(string str, string c){
        auto cur = root;
        int n = str.size(), i = 1;
        while(i < n){
            int j = i;
            while(j < n && str[j] != '/') j++;
            string sub = str.substr(i, j - i);
            if(cur->child.count(sub) == 0) cur->child[sub] = new File();
            cur = cur->child[sub];
            i = j + 1;
        }
        
        cur->isFile = true;
        cur->content += c;
    }
    
    vector<string> ls(string str){
        auto cur = root;
        int n = str.size(), i = 1;
        string sub;
        while(i < n){
            int j = i;
            while(j < n && str[j] != '/') j++;
            sub = str.substr(i, j - i);
            if(cur->child.count(sub) == 0) return {};
            cur = cur->child[sub];
            i = j + 1;
        }
        
        if(cur->isFile) return {sub};
        
        vector<string> ans;
        for(auto p : cur->child) ans.push_back(p.first);
        sort(ans.begin(), ans.end());
        return ans;
    }
};

class FileSystem {
public:
    fs _fs;
    FileSystem() {
        
    }
    
    vector<string> ls(string path) {
        return _fs.ls(path);
    }
    
    void mkdir(string path) {
        _fs.mkdir(path);
    }
    
    void addContentToFile(string filePath, string content) {
        _fs.write(filePath, content);
    }
    
    string readContentFromFile(string filePath) {
        return _fs.read(filePath);
    }
};


//Trie solution seems to be popular

//Solution using Trie
class TrieNode {
public:
    map<string, TrieNode*> dict;
    bool isFile;
    string content;
    TrieNode(){
        isFile = false;
        content = "";
    } 
};

class FileSystem {
private:   
    TrieNode* root;
    
    vector<string> getabbr(string& path){
        
        vector<string> res;
        string temp;
        
        istringstream ss(path);
        
        while(getline(ss,temp,'/')){
            if(temp != "")
                res.push_back(temp);
        }
        
        return res; 
    }
    
    TrieNode* createPath(string& path){
        vector<string> temp = getabbr(path);
        TrieNode* curr = root;
        for(auto&ele:temp){
            if(!curr->dict.count(ele))
                curr->dict[ele] = new TrieNode();
            curr = curr->dict[ele];
        }
        
        return curr;
    }
    
public:
    FileSystem() {
        root = new TrieNode();
    }
    
    vector<string> ls(string path) {
        vector<string> res;
        vector<string> temp = getabbr(path);
        TrieNode* curr = root;
        
        for(auto&ele:temp)
            curr = curr->dict[ele];
        
        if(curr->isFile)
            res.push_back(temp.back());
        else{
            for(auto&ele:curr->dict)
                res.push_back(ele.first);
        }
        return res;
    }
    
    void mkdir(string path) {
        createPath(path);
    }
    
    void addContentToFile(string filePath, string content) {
        TrieNode* curr = createPath(filePath);
        curr->isFile = true;
        curr->content += content;
    }
    
    string readContentFromFile(string filePath) {
        TrieNode* curr = createPath(filePath);
        return curr->content;
    }
};





