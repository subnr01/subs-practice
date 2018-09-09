/*

reversePairs

*/

https://leetcode.com/problems/reverse-pairs/discuss/97268/General-principles-behind-problems-similar-to-%22Reverse-Pairs%22

//What is the best soln?


//this uses the inpalce merge
class Solution {
public:
    int sort_and_count(vector<int>::iterator begin, vector<int>::iterator end) {
        if (end - begin <= 1)
            return 0;
        auto mid = begin + (end - begin) / 2;
        int count = sort_and_count(begin, mid) + sort_and_count(mid, end);
        for (auto i = begin, j = mid; i != mid; ++i) {
            while (j != end and *i > 2L * *j)
                ++j;
            count += j - mid;
        }
        inplace_merge(begin, mid, end);
        return count;
    }

    int reversePairs(vector<int>& nums) {
        return sort_and_count(nums.begin(), nums.end());
    }
};




//a slow solution??? performance can be bad
/*
This is interesting since if we do the same approach using simple merge sort (iterate over elements and count, 
then do a merge), we get time limit exceeded. However internally sort uses quick-sort so you are able to clear 
the cases here. I would think the worst case can still be > n^2 since we are essentially counting 
across each half arrays each iteration and doing a sort again (since each sort would be nlogn)
*/
class Solution {
private:
    int count;
   
    void checkCount(vector<int>& nums, int start, int mid, int end){

        // two pointers;
        int l = start, r = mid + 1;
        while(l <= mid && r <= end){
            if((long)nums[l] > (long) 2 * nums[r]){
                count += (mid - l + 1);
                r++;
            }else{
                l++;
            }
        }
       // worst case might be nlog(n) 
        sort(nums.begin() + start, nums.begin() + end + 1);
        return;
        
        
        
        //every step sort
    }
    void mergeSort(vector<int>& nums, int start, int end){
        if(start == end) return;
        
        int mid = (start + end)/2;
        mergeSort(nums,start, mid);
        mergeSort(nums,mid+1,end);
        
        checkCount(nums,start,mid,end);
        return;
        
    }
public:
    int reversePairs(vector<int>& nums) {
        if(!nums.size())return 0;
        count = 0;
        mergeSort(nums,0,nums.size()-1);
        return count;
    }
};


//Balanced Binary search tree (refer soln also).
//Its performance can be really bad, people say, so check the soln

/*

BST solution is no longer acceptable, because it's performance can be very bad, O(n^2) actually, 
for extreme cases like [1,2,3,4......49999], due to the its unbalance, but I am still providing it below just FYI.
We build the Binary Search Tree from right to left, and at the same time, search the partially built 
tree with nums[i]/2.0. 

*/

class Solution {
public:
    struct node{
        //count:number of nodes from root itself;  
        //self:number of nodes sharing the same val;
        //height: tree height
        int val,count,height,self;
        node* left;
        node* right;
        node(int k):val(k),count(1),self(1),height(1),left(0),right(0){};
        void fix_count_height() { //update count and height
            count = self + (left?left->count:0) + (right?right->count:0);
            height = 1 + max((left?left->height:0),(right?right->height:0));
        }
    };
    
    /*           p                              q            node: p,q
               /   \     right rotation       /   \          Tree: A,B,C
              q     C    -------------->     A     p
            /   \        <--------------         /   \
           A     B       left rotation          B     C
    */
    node* right_rotation(node* p){ // O(1) time complexity
        node* q = p->left;       
        p->left = q->right;    
        q->right = p;          
        p->fix_count_height();
        q->fix_count_height();
        return q; //return new root q after rotation
    }
    node* left_rotation(node* q){ // O(1) time complexity
        node* p = q->right;
        q->right = p->left;
        p->left = q;
        q->fix_count_height();
        p->fix_count_height(); 
        return p; //return new root p after rotation
    }
    
    int bfactor(node* p){ //balance factor = 1,0,-1 are considered balanced from root p 
        int hr = (p->right) ? p->right->height : 0;
        int hl = (p->left) ? p->left->height : 0;
        return hr-hl;
    }
    
    //insert k key in a tree from root r, return the new root after insertion
    node* insert(node* r, int k){ // O(log(n)) time complexity
        if(!r) return new node(k);
        if(k < r->val)
            r->left = insert(r->left,k);
        else if(k > r->val)
            r->right = insert(r->right,k);
        else{
            r->self++;
            r->count++;
            return r;
        }
        
        //balance the tree if one child's height is greater by 2 than the other child
        if(bfactor(r) >= 2){
            if(bfactor(r->right) < 0)
                r->right = right_rotation(r->right);
            return left_rotation(r);
        }
        else if(bfactor(r) <= -2){
            if(bfactor(r->left) > 0)
                r->left = left_rotation(r->left);
            return right_rotation(r);
        }
        else{ //no need to rotate the tree, just update the node's count and height 
            r->fix_count_height();
            return r;
        }
    }
    
    //search the tree from root, count the nodes n where n->val > key .
    int search(const long long key, node* root){ // O(lg(n)) time complexity
        if(!root) return 0;
        if(root->val < key)
            return search(key,root->right);
        else if(root->val > key)
            return ( root->self + (root->right ? root->right->count : 0) ) + search(key,root->left);
        else //root->val == key
            return (root->right) ? root->right->count : 0;
    }
    
    int reversePairs(vector<int>& nums) {
        int size = nums.size();
        if(size<2)  return 0;
        
        //Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2*nums[j].
        node* root = 0;
        root = insert(root,nums[0]);
        int count = 0;
        for(int j=1; j<size; j++){
            int numsj = nums[j];
            count += search(2*(long long)numsj,root);
            root = insert(root, numsj);
        }
        return count;
    }
}; 
