
#include "linklist.h"

//template <typename E>
//LList<E>::LList(E *it, int& len) {
//	for (int i = 0; i < len; ++i) {
//		append(it[i]);
//	}
//}

//template <typename E> //E means element
//void LList<E>::init() {
//	curr = head = tail = new Link < E >;
//	cnt = 0;
//}
//
//template <typename E>
//void LList<E>::removeAll() {
//	while (head != NULL) {
//		curr = head;
//		head = head->next;
//		delete curr;
//	}
//	init();
//}
//
//template <typename E>
//void LList<E>::print() {
//	curr = head;
//	while (curr->next != NULL) {
//		std::cout << curr->element << " ";
//		curr = curr->next;
//	}
//}
//
//template <typename E>
//void LList<E>::invert() {
//	// move curr to top
//	Link<E>* temp;
//	curr = head;
//	while (curr->next != NULL) {
//		temp = curr->next;
//		curr->next = curr->next->next;
//		temp->next = head;
//		// refresh head
//		head = temp;
//	}
//	//refresh tail
//	tail = curr;
//	print();
//}