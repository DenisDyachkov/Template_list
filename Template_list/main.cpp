#include <iostream>
#include <string>
using namespace std;


template<typename T>
class List 
{
public:
	List();
	~List();

	void push_back(T data);
private:

	template<typename T>
	class Node
	{
	public:
		Node* ptrNext;
		T data;

		Node(T data, Node* ptr = nullptr) : data{data} 
		{
		}
	};
	size_t size;
	Node<T> *head;
};

template<typename T>
List<T>::List() {
	size = 0;      
	head = nullptr;
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr) {
		head = new Node<T>(data);
	}
	else {
		  
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	List<int>first;
	first.push_back(5);

}