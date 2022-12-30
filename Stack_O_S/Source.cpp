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
			//head.store(oldv);
		}
		else {
			Node<T>* oldv = head.load();

			while (oldv != nullptr) {
				oldv = oldv->next;
			}
			/*do {
				
			} while (!head.compare_exchange_weak(oldv, nullptr));*/
			//unique_lock<mutex> guard(m);
			oldv = new Node<T>;
			oldv->value = value;
			//guard.unlock();
			
		}
	}
	void Pop() {
		if (IsEmpty()) {
			return;
		}
		Node<T>* mem = head.load();
		Node<T>* oldv = head.load();

		oldv = oldv->next;
		delete mem;
		head.store(oldv);
		cout << oldv->value;
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

	}
	
	
	/*int value = 14;
	thread th1(PrintNextPrime, ref(value));
	thread th2(NextPrime, ref(value));
	th1.join();
	th2.join();*/

