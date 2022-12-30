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
	atomic<Node<T>*> head;
	mutex m;
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
			head.store(new Node<T>);
			Node<T>* oldv = head.load();
			unique_lock<mutex> guard(m);
			oldv->value = value;
			guard.unlock();
		}
		else {
			Node<T>* oldv = new Node<T>;
			unique_lock<mutex> guard(m);
			oldv->value = value;
			guard.unlock();
			do {
				oldv->next = head.load();
			} while (!head.compare_exchange_weak(oldv->next, oldv));
			
		}
	}
	void Pop() {
		if (IsEmpty()) {
			return;
		}
		Node<T>* mem = head.load();
		Node<T>* result;
		do {
			result = mem->next;
		} while (!head.compare_exchange_weak(mem, result));
		cout << mem->value << endl;
		delete mem;
		cout << result->value;
	}
};

int main() {
	Stack<int> st;
	st.Push(4);
	st.Push(5);
	st.Push(6);
	st.Pop();

}
	

