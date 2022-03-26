#ifndef List_H
#define List_H
#include <string>

using namespace std;

template <typename T>
class List {
public:

	List(string name);
	~List();

	void pushFront(T data);
	void remove(size_t index, size_t range);
	void popFront();
	void clear();
	size_t getSize() { return size; }
	string getName() { return name; }

	T& operator[](const size_t index);

private:

	template <typename T>
	class Node {
	public:

		Node* pNext;
		T data;

		Node(T data = T(), Node* pNext = nullptr) {

			this->data = data;
			this->pNext = pNext;
		};

		~Node() {};
	};

	size_t size;
	Node<T>* head;
	string name;
};

#endif