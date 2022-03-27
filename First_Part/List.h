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
	void popFront(); // removes first node of the list
	void clear(); // removes all nodes of the list
	size_t getSize() { return size; }
	string getName() { return name; }

	T& operator[](const size_t index); // operator [] override

private:

	// inserted class Node describes an element of the list
	template <typename T>
	class Node {
	public:
		
		Node* pNext; // pointer to the next Node object
		T data; // info in a list cell

		// T() means zero value for template type
		Node(T data = T(), Node* pNext = nullptr) {

			this->data = data;
			this->pNext = pNext;
		};

		~Node() {};
	};

	size_t size; // the size of the list
	Node<T>* head; // pointer to the head Node object
	string name; // name of the list
};

#endif