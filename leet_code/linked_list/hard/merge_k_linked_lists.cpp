


/*

Concept:

1.Heap is a kind of data structure. It is a name for a particular way of 
storing data that makes certain operations very efficient. We can use a tree or array to describe it.

   18
  / \
 10  16
/ \   / \
9  5  8  12

18, 10, 16, 9, 5, 8, 12
2.Priority queue is an abstract datatype. It is a shorthand way of describing a particular 
interface and behavior, and says nothing about the underlying implementation.

A heap is a very good data structure to implement a priority queue. The operations which are
made efficient by the heap data structure are the operations that the priority queue interface needs.

Implementation: c++

1.priority_queue: we can only get the top element (from ChiangKaiShrek's solution)

*/
class Solution {
public:
   struct compare {
        bool operator()(const ListNode* l, const ListNode* r) 
        {
            return l->val > r->val;
        }
    };
    ListNode *mergeKLists(vector<ListNode *> &lists) 
    {  
        priority_queue<ListNode *, vector<ListNode *>, compare> q;
        for(auto l : lists) 
        {
            if(l) 
            {
                q.push(l);
            } 
        }

        if(q.empty()) 
        {
            return NULL;
        }  
   
        ListNode* result = q.top();
        q.pop();
        if(result->next) 
        {
            q.push(result->next);
        }
       
        ListNode* tail = result;            
        while(!q.empty()) 
        {
            tail->next = q.top();
            q.pop();
            tail = tail->next;
            if(tail->next) {
                q.push(tail->next);
            }
        }
        return result;
    }
};



/*************Solution using vector of lists*********/
class Solution {
public:
    ListNode *mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (NULL == l1) return l2;
        else if (NULL == l2) return l1;
        if (l1->val <= l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty()) return NULL;
        int len = lists.size();
        while (len > 1) {
            for (int i = 0; i < len / 2; ++i) {
                lists[i] = mergeTwoLists(lists[i], lists[len - 1 - i]);
            }
            len = (len + 1) / 2;
        }
        return lists.front();
    }
};


/***********Solution using the merge sort approach ******/
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return partition(lists, 0, lists.size()-1);
    }
    ListNode* partition(vector<ListNode*>& lists, int start, int end){
        if(start == end){
            return lists[start];
        }
        if(start < end){
            int mid = (end+start)/2;
            ListNode* l1 = partition(lists, start, mid);
            ListNode* l2 = partition(lists, mid+1, end);
            return merge(l1, l2);
        }
        return NULL;
    }
    ListNode* merge(ListNode* l1, ListNode* l2){
        if(!l1) return l2;
        if(!l2) return l1;
        if(l1->val < l2->val){
            l1->next = merge(l1->next, l2);
            return l1;
        }else{
            l2->next = merge(l1, l2->next);
            return l2;
        }
    }
};
