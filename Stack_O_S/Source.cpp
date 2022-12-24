#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
using namespace std;
template<class T>
struct Node {
	Node* next = nullptr;
	T value = 0;
};
template<class T>
class Stack {
	//Node<T> *head;
	atomic<Node<T>*> head;
public:
	bool IsEmpty() {
		if (head == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	void Push(T value) {
		if (head == nullptr) {
			
			head = atomic <Node<T>>;
			head->value = value;
			head->next = nullptr;
		}

		atomic <Node<T>*> mem = head;
		head = atomic <Node<T>>;
		head->value = value;
		head->next = mem;
	}
	void Pop() {
		if (IsEmpty()) {
			return;
		}
		/*Node* current = head;
		Node* previous = nullptr;
		while (current != nullptr || current->value != value) {
			current = current->next;
		}
		if (current != nullptr) {

		}*/
		Node<T>* mem = head;
		head = head->next;
		delete mem;
		cout << head->value;
	}

	
	
	
};



//condition_variable cv;
//mutex m;
//void NextPrime(int& value) {
//	unique_lock<mutex> ul(m);
//	while (!IsPrime(value)) {
//		value++;
//	}
//	cv.notify_one();
//}
//void PrintNextPrime(int &value) {
//	unique_lock<mutex> ul(m);
//	cv.wait(ul);
//	cout << value;
//}

/*class Semaphore {

};*/
int main() {
	Stack<int> st;
	int a = 8;
	st.Push(3);
	st.Push(5);
	st.Push(6);
	st.Pop();
	
	
	
	
	/*int value = 14;
	thread th1(PrintNextPrime, ref(value));
	thread th2(NextPrime, ref(value));
	th1.join();
	th2.join();*/





}