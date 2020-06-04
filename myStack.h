#ifndef MYSTACK_H
#define MYSTACK_H
#include<vector>

// Some forward declaration wizardry
/*
According to this very helpful post on stackoverflow:
https://stackoverflow.com/questions/35819831/friend-template-overloaded-operator-unresolved-external-symbol
What's happening is that the friend operator is not matching up with the proper
template. To fix this, we forward declare the class and friend function as below.
We also include <T> typing in the operator+ which is implied when we later use it.
Note, the <T> is required in the function definition in the class.
*/
template<typename T>
class Stack;

template<typename T>
Stack<T> operator+(const Stack<T>& lhs, const Stack<T>& rhs);

template<typename T>
class Stack {
private:
	// Stores the data for the stack
	std::vector<T> data;
	// Size of the stack
	int size; // Nominally not needed
public:
	// Default constructor, make an empty stack
	Stack();
	// Check if the stack is empty
	bool empty() const;
	// Put item on top of the stack
	void push(const T& item);
	// Retrieve top item from the stack
	const T& top() const;
	// Remove top item from the stack
	void pop();
	// Friend function operator overloading +
	friend Stack<T> operator+<T>(const Stack<T>& lhs, const Stack<T>& rhs);
	// <T> Required!!
};

#include "myStack.cpp"

#endif
