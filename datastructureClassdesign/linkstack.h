
#pragma once
#ifndef LINKSTACK_H
#define LINKSTSCK_H

#include <cmath>

#include "linklist.h"
#include "linkqueue.h"

// base stack -- ADT
template <typename E>
class Stack {
private:
	//void operator ={ const Stack& } {}
	
public:
	Stack(const Stack&) {}
	Stack() {}
	virtual ~Stack() {}
	virtual void clear() = 0;
	virtual void push(const E& it) = 0;
	virtual E pop() = 0;
	virtual const E& topValue() const = 0;
	virtual int length() const = 0;
};

// linked stack implementation
template <typename E>
class LStack : public Stack<E> {
public:
	LStack() {
		top = NULL;
		size = 0;
	}

	~LStack() { clear(); }

	void clear() {
		while (top != NULL) {
			Link<E>* temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}

	void push(const E& it) {
		top = new Link<E>(it, top);
		++size;
	}

	E pop() {
		E it = top->element;
		Link<E>* ltemp = top->next;
		//delete top;
		top = ltemp;
		--size;
		return it;
	}

	const E& topValue() const {
		return top->element;
	}

	int length() const { return size; }

private:
	Link<E>* top;
	int size;
};

// 4.17
int recurrence(const int& n) {
	LStack<int> S; // need a stack
	int result = 0; // init
	S.push(n);
	while (S.length() > 0) {
		int temp = S.pop();
		result += temp;
		if (temp != 1) {
			S.push(ceil(temp / 2.0));
			S.push(floor(temp / 2.0));
		}
	}
	return result;
}

// Use a blank Stack and a Queue
// invert a Queue
template <typename E>
void invertQueue(LQueue<E>& target_que) {
	LStack<E> trans_stack; // need a null stack
	// move the element of Queue to Stack
	while (target_que.length() > 0) {
		trans_stack.push(target_que.dequeue());
	}
	// move the element of Stack to Queue
	while (trans_stack.length() > 0) {
		target_que.enqueue(trans_stack.pop());
	}
}

#endif