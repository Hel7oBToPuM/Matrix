#include "ArrayList.h"

template<class TempClass>
ArrayList<TempClass>::ArrayList() : capacity(1), _size(0) {
	vector = new TempClass[capacity];
}

template<class TempClass>
ArrayList<TempClass>::~ArrayList() { delete[] vector; }

template<class TempClass>
void ArrayList<TempClass>::reserve()
{
	TempClass* temp = new TempClass[capacity *= 2];

	for (size_t i = 0; i < _size; i++)
		temp[i] = vector[i];
	delete[] vector;
	vector = temp;
}

template<class TempClass>
size_t ArrayList<TempClass>::size() { return _size; }

template<class TempClass>
TempClass& ArrayList<TempClass>::operator[](size_t index)
{
	if (index >= _size)
		throw "index out of bound";

	return vector[index];
}

template<class TempClass>
void ArrayList<TempClass>::erase(size_t pos)
{
	if (pos >= _size)
		throw "insert(size_t) called on invalid position";

	for (size_t i = pos + 1; i < _size; i++)
		vector[i - 1] = vector[i];

	--_size;
}

template<class TempClass>
void ArrayList<TempClass>::insert(size_t pos, const TempClass& value)
{
	if (pos > _size)
		throw "insert(size_t) called on invalid position";
	if (_size == capacity)
		reserve();

	for (size_t i = _size - 1; i >= pos; --i)
		vector[i + 1] = vector[i];

	vector[pos] = value;
	++_size;
}

template<class TempClass>
void ArrayList<TempClass>::push_back(const TempClass& value)
{
	if (_size == capacity)
		reserve();
	vector[_size++] = value;
}

template<class TempClass>
void ArrayList<TempClass>::pop_back() { --_size; }

template<class TempClass>
void ArrayList<TempClass>::clear() {
	_size = 0;
	delete[] vector;
	capacity = 1;
	vector = new TempClass[capacity];
}

template<class TempClass>
template<class ...ArgsTypes>
void ArrayList<TempClass>::emplace_back(ArgsTypes && ...args)
{
	if (_size == capacity)
		reserve();
	vector[_size++] = TempClass(std::forward<ArgsTypes>(args)...);
}

