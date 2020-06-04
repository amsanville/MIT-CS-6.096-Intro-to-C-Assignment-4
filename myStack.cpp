#ifndef MYSTACK_CPP
#define MYSTACK_CPP
#include "myStack.h"

/*
Note: because all these functions are so simple it might make sense to just
include them in the header file as inline functions. Recall, inline is a key
word that attempts to remove the overhead associated with function calls
through find and replace type tricks at compile time. It should be reserved
for code that is small and non-recursive.

These are good candidates. All the difficulty of template classes and separate
implemenation amounts to naught if it is not needed. Oh well, proof of concept.
*/

// Constructor
template<typename T>
Stack<T>::Stack() {
	data = std::vector<T>();
	size = 0;
}

// Empty
template<typename T>
bool Stack<T>::empty() const {
	return size == 0;
}

// Push
template<typename T>
void Stack<T>::push(const T& item) {
	data.push_back(item);
	size++;
}

// Top
template<typename T>
const T& Stack<T>::top() const {
	return data.back();
}

// Pop
template<typename T>
void Stack<T>::pop() {
	data.pop_back();
	size--;
}

// Operator +
template<typename T>
Stack<T> operator+(const Stack<T>& lhs, const Stack<T>& rhs) {
	// Construct a new stack
	Stack<T> result = Stack<T>();

	// Combine the vectors
	// Pre-allocate memory
	result.data.reserve(lhs.size + rhs.size);
	// Insert left-hand 
	result.data.insert(result.data.end(), lhs.data.begin(), lhs.data.end());
	// Insert right-hand
	result.data.insert(result.data.end(), rhs.data.begin(), rhs.data.end());

	// Combine sizes
	result.size = lhs.size + rhs.size;

	return result;
};

#endif