// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#include <iostream>
#include <algorithm>
#include <stdexcept>
template<typename T>
class TStack {
private:
	T* data;
	int capacity;
	int topIndex;
public:
	TStack(int initialCapacity = 10) : capacity(initialCapacity), topIndex(-1) {
		if (initialCapacity <= 0) {
			throw std::invalid_argument("Stack capacity must be positive");
		}
		data = new T[capacity];
	}
	void resize(int newCapacity) {
		T* newData = new T[newCapacity];
		for (int i = 0; i <= topIndex; i++) 
			newData[i] = data[i];
		delete[] data;
		data = newData;
		capacity = newCapacity;
	}
	TStack(const TStack& other) : capacity(other.capacity), topIndex(other.topIndex) {
		data = new T[capacity];
		for (int i = 0; i <= topIndex; i++) {
			data[i] = other.data[i];
		}
	}
	TStack& operator=(const TStack& other) {
		if (this != &other) {
			delete[] data;
			capacity = other.capacity;
			topIndex = other.topIndex;
			data = new T[capacity];
			for (int i = 0; i <= topIndex; i++) {
				data[i] = other.data[i];
			}
		}
		return *this;
	}
	~TStack() {
		delete[] data;
		data = nullptr;
	}
	void push(const T& value) {
		if (isFull()) {
			resize(capacity * 2);
		}
		data[++topIndex] = value;
	}
	T pop() {
		if (isEmpty()) {
			throw std::underflow_error("Cannot pop from empty stack");
		}
		return data[topIndex--];
	}
	T peek() const {
		if (isEmpty()) {
			throw std::underflow_error("Cannot peek empty stack");
		}
		return data[topIndex];
	}
	bool isFull() const {
		return topIndex == capacity - 1;
	}
	bool isEmpty() const {
		return topIndex == -1;
	}
	int GetSize() const {
		return topIndex + 1;
	}
	int GetCapacity() const {
		return capacity;
	}
	void clear() {
		topIndex = -1;
	}
	void print() {
		std::cout << "Stack (size: " << GetSize() << ", capacity: " << capacity << "): ";
		if (isEmpty()) {
			std::cout << "empty";
		}
		else {
			for (int i = 0; i <= topIndex; i++) {
				std::cout << data[i];
				if (i < topIndex) {
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl;
	}
};