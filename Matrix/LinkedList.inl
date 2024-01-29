#include "LinkedList.h"

template <class TempClass>
LinkedList<TempClass>::LinkedList() : _size(0), head(nullptr), tail(nullptr) { }

template <class TempClass>
LinkedList<TempClass>::~LinkedList()
{
	for (int i = 0; i < _size; i++) {
		if (head == tail) {
			delete tail;
			break;
		}
		head = head->next;
		delete head->prev;
	}
}

template <class TempClass>
size_t LinkedList<TempClass>::size() { return _size; }

template<class TempClass>
void LinkedList<TempClass>::push(Node*& where, Node* value)
{
	_size++;
	if (&where == &head) {
		if (tail == nullptr)
			tail = value;

		if (head != nullptr) {
			head->prev = value;
			value->next = head;
		}
		head = value;
	}
	else if (&where == &tail) {
		if (head == nullptr)
			head = value;

		if (tail != nullptr) {
			tail->next = value;
			value->prev = tail;
		}
		tail = value;
	}
	else {
		where->prev->next = value;
		value->prev = where->prev;
		where->prev = value;
		value->next = where;
	}
}

template<class TempClass>
void LinkedList<TempClass>::pop(Node*& where)
{
	_size--;
	if (_size == 0) {
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else if (&where == &head) {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	}
	else if (&where == &tail) {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
	}
	else {
		where->prev->next = where->next;
		where->next->prev = where->prev;
		delete where;
	}
}

template<class TempClass>
void LinkedList<TempClass>::insert(size_t pos, const TempClass& value)
{
	if (pos >= _size && pos != 0)
		throw "insert(size_t) called with invalid position of element!";

	Node* data = new Node(value);

	if (pos == 0)
		push(head, data);
	else if (pos == _size)
		push(tail, data);
	else {
		Node* val_pos = head;
		for (size_t i = 0; i < pos; i++, val_pos = val_pos->next) {};
		push(val_pos, data);
	}
}

template<class TempClass>
void LinkedList<TempClass>::erase(size_t pos)
{
	if (pos >= _size)
		throw "erase(size_t) called with invalid position of element!";
	else if (_size == 0)
		throw "erase(size_t) called on empty list!";

	if (pos == 0)
		pop(head);
	else if (pos == _size - 1)
		pop(tail);
	else {
		Node* val_pos = head;
		for (size_t i = 0; i < pos; i++, val_pos = val_pos->next) {};
		pop(val_pos);
	}
}

template<class TempClass>
void LinkedList<TempClass>::remove(Iterator& pos)
{
	if (pos == nullptr)
		throw "Invalid Iterator!";
	if (_size == 0)
		throw "Invalid Iterator!";

	if (pos.node_ptr == head) {
		pos.node_ptr = pos.node_ptr->next;
		pop(head);
	}
	else if (pos.node_ptr == tail) {
		pos.node_ptr = pos.node_ptr->prev;
		pop(tail);
	}
	else {
		Node* position = pos.node_ptr;
		pos.node_ptr = pos.node_ptr->next;

		pop(position);
	}
}

template<class TempClass>
template<class Function>
void LinkedList<TempClass>::remove_if(const Function& condition)
{
	Iterator it = begin();
	while (it != end()) {
		Iterator rem = it;
		it++;
		if (condition(*rem))
			remove(rem);
	}
}

template<class TempClass>
template<class ...ArgsTypes>
void LinkedList<TempClass>::emplace_back(ArgsTypes&&... args)
{
	Node* data = new Node(std::forward<ArgsTypes>(args)...);
	push(tail, data);
}


template<class TempClass>
void LinkedList<TempClass>::push_back(const TempClass& value)
{
	Node* data = new Node(value);
	push(tail, data);
}

template<class TempClass>
void LinkedList<TempClass>::push_back(TempClass&& value)
{
	Node* data = new Node(std::forward<TempClass>(value));
	push(tail, data);
}

template<class TempClass>
void LinkedList<TempClass>::pop_back()
{
	if (_size == 0)
		throw "pop_back() called on empty list!";

	pop(tail);
}

template<class TempClass>
TempClass& LinkedList<TempClass>::back()
{
	if (_size == 0)
		throw "back() called on empty LinkedList!";
	return tail->value;
}

template<class TempClass>
typename LinkedList<TempClass>::Iterator LinkedList<TempClass>::begin()
{
	if (_size == 0)
		throw "begin() called on empty LinkedList!";
	return Iterator(head);
}

template<class TempClass>
template<class ...ArgsTypes>
void LinkedList<TempClass>::emplace_front(ArgsTypes&&... args)
{
	Node* data = new Node(std::forward<ArgsTypes>(args)...);
	push(head, data);
}

template<class TempClass>
void LinkedList<TempClass>::push_front(const TempClass& value)
{
	Node* data = new Node(value);
	push(head, data);
}

template<class TempClass>
void LinkedList<TempClass>::push_front(TempClass&& value)
{
	Node* data = new Node(std::forward<TempClass>(value));
	push(head, data);
}

template<class TempClass>
void LinkedList<TempClass>::pop_front()
{
	if (_size == 0)
		throw "pop_front() called on empty list!";
	
	pop(head);
}

template<class TempClass>
TempClass& LinkedList<TempClass>::front() 
{ 
	if (_size == 0)
		throw "front() called on empty LinkedList!";
	return head->value; 
}

template<class TempClass>
typename LinkedList<TempClass>::Iterator LinkedList<TempClass>::end() { return Iterator(nullptr); }
