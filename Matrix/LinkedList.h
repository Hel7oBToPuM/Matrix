#pragma once
#include "List.h"
#include <type_traits>

template <class TempClass>
class LinkedList : public List<TempClass>
{
private:
	class Node
	{
	public :
		TempClass value;
		Node* next;
		Node* prev;

		Node() : value(TempClass), next(nullptr), prev(nullptr) {  };

		Node(const TempClass& _value) : value(_value), next(nullptr), prev(nullptr) { };

		Node(TempClass&& _value) : value(_value), next(nullptr), prev(nullptr) { };

		template <class ...ArgsTypes>
		Node(ArgsTypes&&... args) : value(std::forward<ArgsTypes>(args)...), next(nullptr), prev(nullptr) { };

	};

public:
	class Iterator
	{
		friend class LinkedList<TempClass>;
	private:
		Node* node_ptr;
		Iterator(Node* value) : node_ptr(value) { };
	public:
		Iterator() : node_ptr(nullptr) { };

		Iterator operator++(int) { node_ptr = node_ptr->next; return *this; }

		friend bool operator==(const Iterator& it1, const Iterator& it2) { return (it1.node_ptr == it2.node_ptr); };

		friend bool operator!=(const Iterator& it1, const Iterator& it2) { return (it1.node_ptr != it2.node_ptr); };

		TempClass& operator* () { return node_ptr->value; }
	};

private:
	size_t _size;
	Node* head;
	Node* tail;
	
	void push(Node* &where, Node* value);
	void pop(Node*& where);
	void remove(Iterator& pos);
public:

	LinkedList();

	~LinkedList();

	size_t size() override;

	void erase(size_t pos) override;

	void insert(size_t pos, const TempClass& value) override;

	void push_back(const TempClass& value) override;

	void push_back(TempClass&& value);

	void push_front(const TempClass& value);

	void push_front(TempClass&& value);

	template<class... ArgsTypes>
	void emplace_front(ArgsTypes&&... args);

	template<class... ArgsTypes>
	void emplace_back(ArgsTypes&&... args);

	void pop_back();

	void pop_front();

	template<class Function>
	void remove_if(const Function& condition);

	TempClass& front();

	TempClass& back();

	Iterator begin();

	Iterator end();
};

#include "LinkedList.inl"