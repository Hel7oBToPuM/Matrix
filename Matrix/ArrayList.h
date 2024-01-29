#pragma once
#include "List.h"
#include <type_traits>
template <class TempClass>
class ArrayList : public List<TempClass>
{
private:
	size_t _size;
	size_t capacity;
	TempClass* vector;

	void reserve();
public:

	ArrayList();

	~ArrayList();

	size_t size() override;

	TempClass& operator[] (size_t index);

	void erase(size_t pos) override;

	void insert(size_t pos, const TempClass& value) override;

	void push_back(const TempClass& value) override;

	void pop_back();

	template<class ...ArgsTypes>
	void emplace_back(ArgsTypes&& ...args);

	void clear();

};

#include "ArrayList.inl"