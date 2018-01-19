/*
In English, we have a concept called root, which can be followed by some other words to form 
another longer word - let's call this word successor. For example, the root an, followed by other, 
which can form another word another.

Now, given a dictionary consisting of many roots and a sentence. You need to replace all the successor
in the sentence with the root forming it. If a successor has many roots can form it, replace it with the root
with the shortest length.

You need to output the sentence after the replacement.

Example 1:
Input: dict = ["cat", "bat", "rat"]
sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"


*/

/*

The code could be shorter but I wanted to add two performance optimizations.

You do not need to build the entire trie for roots in the dictionary. You can stop at the shortest root.
The optimized root function returns the root or the entire word (till the space).
If it returns the root, the calling function need to skip to the next space. That way, we only go through the sentence once.

*/

class trie {
    bool isRoot = false;
    trie* l[26] = {};
public:
    void insert(string& word, int ch, int sz) {
        isRoot |= ch == sz;
        if (!isRoot) { // stop at the shortest root.
            if (l[word[ch] - 'a'] == nullptr) l[word[ch] - 'a'] = new trie();
            l[word[ch] - 'a']->insert(word, ch + 1, sz);
        }
    }
    int root(string& word, int st, int ch, int sz) {
        if (st + ch == sz || word[st + ch] == ' ' || this->isRoot) return ch;
        if (l[word[st + ch] - 'a'] == nullptr) { // root was not found
            while (st + ch < sz && word[st + ch] != ' ') ++ch; // skipping the entire word
            return ch;
        }
        return l[word[st + ch] - 'a']->root(word, st, ch + 1, sz);
    }
};
string replaceWords(vector<string>& dict, string snt) {
    trie t;
    string res;
    for (auto s : dict) t.insert(s, 0, s.size());
    for (int i = 0; i < snt.size(); ) {
        if (snt[i] == ' ') res += snt[i++];
        auto chars = t.root(snt, i, 0, snt.size());
        res += snt.substr(i, chars);
        for (i += chars; i < snt.size() && snt[i] != ' '; ++i);
    }
    return res;
}
