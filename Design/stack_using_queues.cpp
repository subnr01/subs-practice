/*
 Implement Stack using Queues


push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.
*/




class MyStack {
public:
	queue<int> que;
	// Push element x onto stack.
	void push(int x) {
		que.push(x);
		for(int i=0;i<que.size()-1;++i){
			que.push(que.front());
			que.pop();
		}
	}

	// Removes the element on top of the stack.
	int pop() {
		int x = que.front();
		que.pop();
		return x;
	}

	// Get the top element.
	int top() {
		return que.front();
	}

	// Return whether the stack is empty.
	bool empty() {
		return que.empty();
	}
};
