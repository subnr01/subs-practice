/*
Merge k sorted linked lists and return it as one sorted list. 
Analyze and describe its complexity.

*/

//Using priority_queue
class Solution {
public:
   struct compare {
    bool operator()(const ListNode* l, const ListNode* r) {
        return l->val > r->val;
    }
};
ListNode *mergeKLists(vector<ListNode *> &lists) { //priority_queue
    priority_queue<ListNode *, vector<ListNode *>, compare> q;
    for(auto l : lists) {
        if(l)  q.push(l);
    }
    if(q.empty())  return NULL;
    ListNode* result = q.top();
    q.pop();
    if(result->next) q.push(result->next);
    ListNode* tail = result;            
    while(!q.empty()) {
        tail->next = q.top();
        q.pop();
        tail = tail->next;
        if(tail->next) q.push(tail->next);
    }
    return result;
}

};


//Using heap
static bool heapComp(ListNode* a, ListNode* b) {
        return a->val > b->val;
}
ListNode* mergeKLists(vector<ListNode*>& lists) { //make_heap
    ListNode head(0);
    ListNode *curNode = &head;
    vector<ListNode*> v;   
    for(int i =0; i<lists.size(); i++){
        if(lists[i]) v.push_back(lists[i]);
    }
    make_heap(v.begin(), v.end(), heapComp); //vector -> heap data strcture

    while(v.size()>0){
        curNode->next=v.front();
        pop_heap(v.begin(), v.end(), heapComp); 
        v.pop_back(); 
        curNode = curNode->next;
        if(curNode->next) {
            v.push_back(curNode->next); 
            push_heap(v.begin(), v.end(), heapComp);
        }
    }
    return head.next;
}


//using recursion
class Solution {
private:
    static ListNode* mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr) {
            return l2;
        }

        if (l2 == nullptr) {
            return l1;
        }

        if (l2->val < l1->val) {
            swap(l2, l1);
        }

        for (auto n = l1;;) {
            while (n->next != nullptr && n->next->val <= l2->val) {
                n = n->next;
            }

            if (n->next == nullptr) {
                n->next = l2;
                return l1;
            }

            swap(n->next, l2);
        }
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        
        while (lists.size() > 1) {
            auto len = lists.size();
            for (size_t i = 0; i < len/2; ++i) {
                lists[i] = mergeTwoLists(lists[i], lists[len - i - 1]);
            }
            lists.resize((len + 1)/2);
        }
        return lists[0];
    }
};
