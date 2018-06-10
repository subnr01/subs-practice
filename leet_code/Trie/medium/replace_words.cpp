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

Basically the logic is to take all the words in the dictionary and
insert them into the trie and mark the end as root.
The catch however is if we find a subroot inside the word, then we stop
and do not add the full word.

Now when we go into the sentece, we add the space and then take the sentence
and process it through the trie, until we found a root or we found a space.
If there is no root, then leave the root in the as is, if
we found a root, then we replace the word with the root in the sentence.

*/



class trie {
    bool isRoot = false;
    trie* l[26] = {};
public:
   void insert(string& word, int index, int sz) {
       // We are able to insert the
       // the root as we reached the word
       // size, so let us mark the end to
       // signify that this is a root.
        if (index == sz) {
            isRoot = true;
            return;
        }
       
       // if the current word/root already has a root in it
       // then stop at the shortest root and do not
       // continue till the end of the root.
        if (!isRoot) { // stop at the shortest root.
            int ch = word[index] - 'a';
            if (l[ch] == nullptr) l[ch] = new trie();
            l[ch]->insert(word, index + 1, sz);
        }
    }
    int root(string& word, int st, int index, int sz) {
        // if we are at the word length or if we found a space
        // or if we found a root.
        // if we found a space, but no root, then just return the size
        // of the word, without reducing its size to say that
        // we are just leaving the word as is.
        if (st + index == sz || word[st + index] == ' ' || this->isRoot) {
            return index;
        }
        
        int ch = word[st + index] - 'a';
        
        if (l[ch] == nullptr) { 
            // root was not found
            while (st + index < sz && word[st + index] != ' ') 
            {
                ++index; // skipping the entire word
            }
            return index;
        }
        return l[ch]->root(word, st, index + 1, sz);
    }
};


class Solution {
public:
    string replaceWords(vector<string>& dict, string snt) 
    {
        trie t;
        string res;
        for (auto s : dict) {
            t.insert(s, 0, s.size());
        }
    
        int i = 0;
        while (i < snt.size()) 
        {
            //If this is a space, take in
            // the space.
            if (snt[i] == ' ') {
                res += snt[i++];
            }
            
            auto chars = t.root(snt, i, 0, snt.size());
            res += snt.substr(i, chars);
        
            // Since we have omitted some part of the word, for its
            // root, we will skip past the omitted parts until
            // we find the next space.
            for (i += chars; i < snt.size() && snt[i] != ' '; ++i);
    
        }
        return res;
    }
};



