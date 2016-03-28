
#pragma once
#ifndef LINKSTACK_H
#define LINKSTSCK_H

#include <cmath>

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

// array-based stack implementtation
template <typename E>
class AStack : public Stack<E> {
private:
	int maxSize;           // Maximun size of stack
	int top;               // Index for top element
	E *listArray;          // Array holding stack elements

public:
	// Constructor
	AStack(int size) {
		maxSize = size;
		top = 0;
		listArray = new E[size];
	}

	~AStack() { delete[] listArray; }

	void clear() { top = 0; }

	void push(const E& it) {
		if (top == maxSize) {
			cout << "Stack is full!" << endl;
			return;
		}
		listArray[top++] = it;
	}

	E pop() {
		if (top == 0) {                // Pop top element
			cout << "Stack is empty!" << endl;
			// if err, return a empty E
			// TODO, shit design
			E err;
			return err;
		}
		return listArray[--top];
	}

	const E& topValue() const {         // Return top element
		if (top == 0) {
			cout << "Stack is empty!" << endl;
			// if err, return a empty E
			// TODO, shit design
			E err;
			return err;
		}
		return listArray[top - 1];
	}

	int length() const { return top; }  // Return length
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

#endif