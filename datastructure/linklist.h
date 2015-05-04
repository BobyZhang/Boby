
#pragma once
#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>
//#include <cassert>

// base class
template <typename E>
class List {
private:
	//void operator ={ const List& } {}
	
public:
	List(const List&) {}
	List() {}
	virtual ~List() {}
	virtual void clear() = 0;
	virtual void insert(const E& item) = 0;
	virtual void append(const E& item) = 0;
	virtual E remove() = 0;
	virtual void moveToStart() = 0;
	virtual void moveToEnd() = 0;
	virtual void prev() = 0;
	virtual void next() = 0;
	virtual int length() const = 0;
	virtual int currPos() const = 0;
	virtual void moveToPos(const int& pos) = 0;
	virtual const E& getValue() const = 0;
};

template <typename E>
class Link {
public:
	E element;
	Link* next;
	// Constructors

	Link(const E& elemval, Link* nextval) {
		element = elemval;
		next = nextval;
	}
	Link(Link* nextval = NULL) { next = nextval; }
};

template <typename E>
class LList : public List<E> {
private:
	Link<E>* head;
	Link<E>* tail;
	Link<E>* curr;
	int cnt;

	void init();
	void removeAll();

public:
	LList() { init(); }
	LList(E *it, int& len);
	~LList() { removeAll(); }

	void clear() { removeAll(); init(); }
	void print(); // show all of element
	
	const E& getValue() const;
	void insert(const E& it); // insert after curr node
	void append(const E& it); // append at the tail
	E remove(); // remove and return the curr element

	void moveToStart() { curr = head; }
	void moveToEnd() { curr = tail; }
	void prev(); // move the curr to prev
	void next(); // move the curr to next

	int length() const { return cnt; } // get the length of the LList
	int currPos() const; // get the number of curr postion
	void moveToPos(const int& pos);
	
	void invert(); // invert the LList

	friend LList<E> merge(LList<E>& a, LList<E>& b){
		LList<E> result_list;
		a.curr = a.head->next;  //a.moveToStart();
		b.curr = b.head->next;//b.moveToStart();

		while ((a.curr != NULL) && (b.curr != NULL))  {
			if (a.curr->element < b.curr->element) {
				result_list.curr->next = a.curr;
				a.next();
			} else {
				result_list.curr->next = b.curr;
				b.next();
			}
			result_list.next();
		}

		//
		if (a.curr == NULL) {
			result_list.curr->next = b.curr;
			result_list.tail = b.tail;
		} else {
			result_list.curr->next = a.curr;
			result_list.tail = a.tail;
		}
		// the length of result is the addition of a and b
		result_list.cnt = a.cnt + b.cnt;
		return result_list;
	};
};


template <typename E>
void LList<E>::init() {
	curr = head = tail = new Link < E >;
	cnt = 0;
}

template <typename E>
LList<E>::LList(E *it, int& len) {
	init();
	for (int i = 0; i < len; ++i) {
		append(it[i]);
	}
	cnt = len;
}

template <typename E>
void LList<E>::removeAll() {
	while (head != NULL) {
		curr = head;
		head = head->next;
		//delete curr;  there has some problom
	}
	init();
}
template <typename E>
void LList<E>::print() {
	if (head == tail) return;
	curr = head;
	while (curr->next != NULL) {
		std::cout << curr->next->element << " ";
		curr = curr->next;
	}
}
template <typename E>
void LList<E>::insert(const E& it) {
	curr->next = new Link<E>(it, curr->next);
	if (curr == tail) tail = curr->next;
	++cnt;
}
template <typename E>
void LList<E>::append(const E& it) {
	tail->next = new Link<E>(it, NULL);
	tail = tail->next;
	++cnt;
}
template <typename E>
E LList<E>::remove() {
	//Assert(curr->next != NULL, "No element");
	E it = curr->next->element;
	Link<E>* ltemp = curr->next;
	if (curr->next == tail) tail = curr;
	curr->next = curr->next->next;
	delete ltemp;
	--cnt;
	return it;
}
template <typename E>
void LList<E>::prev() {
	if (curr = head) return;
	Link<E>* temp = head;
	while (temp->next != curr) { temp = temp->next; }
	curr = temp;
}
template <typename E>
void LList<E>::next() {
	//Assert(curr->next != NULL, "There has not next!");
	curr = curr->next;
}
template <typename E>
int LList<E>::currPos() const {
	Link<E>* temp = head;
	int count;
	for (count = 0; temp != curr; ++count) temp = temp->next;
	return count;
}
template <typename E>
void LList<E>::moveToPos(const int& pos) {
	//Assert((pos >= 0) && (pos <= cnt), "Out of range!");
	curr = head;
	for (int i = 0; i < pos; ++i) curr = curr->next;
}
template <typename E>
const E& LList<E>::getValue() const {
	//Assert(curr->next != NULL, "No value!");
	return curr->next->element;
}
template <typename E>
void LList<E>::invert() {
	// move curr to top
	Link<E>* temp;
	curr = head->next;
	while (curr->next != NULL) {
		temp = curr->next;
		curr->next = curr->next->next;
		temp->next = head->next;
		// refresh head
		head->next = temp;
	}
	//refresh tail
	tail = curr;
}



#endif