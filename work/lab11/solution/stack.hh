#include<cassert>

#ifndef STACK_HH
#define STACK_HH

#define STACK_CAPACITY 16

class Stack{
private:
	char stk[STACK_CAPACITY];
	int top;

public:

	Stack() { top = -1; }

	~Stack() { }

	void operator=(Stack& s) = delete;
	//Stack(const Stack s) = delete; why does this not work??

	void push(int val) { assert(top < 16); stk[++top] = val; }
  
	char pop() { return stk[top--]; }

	char peek() { return stk[top]; }

	bool isEmpty() { return (top == -1); }

};




#endif //ifndef STACK_HH
