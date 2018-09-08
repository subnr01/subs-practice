/*
countRangeSum
*/










//Use mergeSort
class Solution {
public:
    int mergeSort(vector<long>& sum, int lower, int upper, int low, int high)
    {
        if(high-low <= 1) return 0;
        int mid = (low+high)/2, m = mid, n = mid, count =0;
        count =mergeSort(sum,lower,upper,low,mid) +mergeSort(sum,lower,upper,mid,high);
        for(int i =low; i< mid; i++)
        {
            while(m < high && sum[m] - sum[i] < lower) m++;
            while(n < high && sum[n] - sum[i] <= upper) n++;
            count += n - m;
        }
        inplace_merge(sum.begin()+low, sum.begin()+mid, sum.begin()+high);
        return count;
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int len = nums.size();
        vector<long> sum(len + 1, 0);
        for(int i =0; i< len; i++) sum[i+1] = sum[i]+nums[i];
        return mergeSort(sum, lower, upper, 0, len+1);
    }
};



//Another soln
class Solution {
private:
  int countRange(vli& sums, int lower, int upper, int left, int right) {
    if (left == right)
      return (lower <= sums[left] && sums[left] <= upper) ? 1 : 0;
    int mid = (left + right)/2;
    int count = countRange(sums, lower, upper, left, mid) + countRange(sums, lower, upper, mid + 1, right);
    int ilower = mid + 1, iupper;
    for (int i = left; i <= mid; ++i) {
      while (ilower <= right && sums[ilower] - sums[i] < lower) ++ilower;
      iupper = ilower;
      while (iupper <= right && sums[iupper] - sums[i] <= upper) ++iupper;
      count += (iupper - ilower);
      if (ilower == right + 1) break;
    }
    int i = left, j = mid + 1, k = 0;
    vli temp(right - left + 1);
    while (i <= mid) {
      while (j <= right && sums[j] < sums[i]) temp[k++] = sums[j++];
      temp[k++] = sums[i++];
    }
    while (j <= right) temp[k++] = sums[j++];
    for (i = left; i <= right; ++i) sums[i] = temp[i-left];
    return count;
  }
public:
  int countRangeSum(vector<int>& nums, int lower, int upper) {
    vli sums;
    if (nums.size() > 0)
      sums.push_back(nums[0]);
    else
      return 0;
    for (int i = 1; i < nums.size(); ++i) sums.push_back(sums.back() + nums[i]);
    return countRange(sums, lower, upper, 0, sums.size() - 1);
  }
};

//BST
class Solution {
    struct Node{
        long val;
        int count,height,size;
        Node* left,*right;
        Node(long x):val(x),count(1),height(1),size(1),left(NULL),right(NULL){}
    };
    
public:
    inline int height(Node* x){
        return (x?x->height:0);
    }
    inline int size(Node* x){
        return (x?x->size:0);
    }
    
    inline int balance(Node* x){
        if(!x)return 0;
        return height(x->left) - height(x->right);
    }
    
    Node* LeftRotate(Node* x){
        Node* y = x->right;
        Node* z = y->left;
        x->right = z;
        y->left = x;
        
        x->height = max(height(x->left),height(x->right))+1;
        x->size = size(x->left) + size(x->right) + x->count;
        
        y->height = max(height(y->left),height(y->right))+1;
        y->size = size(y->left) + size(y->right) + y->count;
        return y;
    }
    Node* RightRotate(Node* x){
        Node* y = x->left;
        Node* z = y->right;
        x->left = z;
        y->right = x;
        
        x->height = max(height(x->left),height(x->right))+1;
        x->size = size(x->left) + size(x->right) + x->count;
        
        y->height = max(height(y->left),height(y->right))+1;
        y->size = size(y->left) + size(y->right) + y->count;
        return y;
    }
    
    Node* insert(Node* root,long val){
        if(!root)
            return new Node(val);
        if(root->val < val)
            root->right = insert(root->right,val);
        else if(root->val > val)
            root->left = insert(root->left,val);
        else{
            root->count++,root->size++;
            return root;
        }
        root->height = max(height(root->left),height(root->right))+1;
        root->size = size(root->left) + size(root->right) + root->count;
        int bal = balance(root);
        
        if(bal>1 && root->left->val > val)
            root=RightRotate(root);
        else if(bal<-1 && root->right->val < val)
            root = LeftRotate(root);
        else if(bal>1 && root->left->val < val){
            root->left = LeftRotate(root->left);
            root = RightRotate(root);
        }
        else if(bal<-1 && root->right->val > val){
            root->right = RightRotate(root->right);
            root = LeftRotate(root);
        }
        return root;
        
    }
    
    int search(Node* root,long val){
        Node* cur = root;
        int ans = 0;
        while(cur){
            if(cur->val < val){
                ans += size(cur) - size(cur->right);
                cur = cur->right;
            }
            else{
                cur = cur->left;
            }
        }
        return ans;
    }
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        long ans = 0,presum = 0;
        Node* root=NULL;
        root = insert(root,presum);
        for(auto n:nums){
            presum += n;
            ans -= search(root,presum-upper);
            ans += search(root,presum-lower+1);
            root = insert(root,presum);
        }
        
        return ans;
    }
};


//SHortest soln
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int res = 0;
        long long sum = 0;
        multiset<long long> sums;
        sums.insert(0);
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            res += distance(sums.lower_bound(sum - upper), sums.upper_bound(sum - lower));
            sums.insert(sum);
        }
        return res;
    }        
};

//Another short soln
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        map<long, int> sumToSumNum;
        sumToSumNum[0] = 1;
        long sum = 0;
        int ans = 0;
        for(int i = 0; i < nums.size(); ++i){
            sum += nums[i];
            map<long, int>::iterator lId = sumToSumNum.lower_bound(sum - upper);
            auto UId = sumToSumNum.upper_bound(sum - lower);
            for(; lId != UId; lId++){
                ans += lId->second;
            }
            sumToSumNum[sum] += 1;
        }
        return ans;
    }
};
