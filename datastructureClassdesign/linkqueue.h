

#pragma once
#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "linklist.h"
// Abstract queue clss
template <typename E>
class Queue {
private:
	void operator =(const Queue&) {}
	Queue(const Queue&) {}
public:
	Queue() {}
	virtual ~Queue() {}
	virtual void clear() = 0;
	// place an element at the near of the queue
	virtual void enqueue(const E&) = 0;
	// remove and return element at the front of the queue
	virtual E dequeue() = 0;
	virtual const E& frontValue() const = 0;
	virtual int length() const = 0;
};

// linked queue implementation
template <typename E>
class LQueue : public Queue < E > {
private:
	Link<E>* front;
	Link<E>* rear;
	int size;

public: 
	LQueue() {
		front = rear = new Link<E>();
		size = 0;
	}

	~LQueue() { 
		clear(); 
		delete front;
	}

	void clear() {
		while (front->next != NULL) {
			rear = front;
			//delete rear;
		}
		rear = front;
		size = 0;
	}

	void enqueue(const E& it) {
		rear->next = new Link<E>(it, NULL);
		rear = rear->next;
		++size;
	}

	E dequeue() {
		// Assert
		E it = front->next->element;
		Link<E>* ltemp = front->next;
		front->next = ltemp->next;
		if (rear == ltemp) rear = front;
		//delete ltemp;
		--size;
		return it;
	}

	const E& frontValue() const {
		//Assert
		return front->next->element;
	}

	int length() const { return size; }
};

#endif