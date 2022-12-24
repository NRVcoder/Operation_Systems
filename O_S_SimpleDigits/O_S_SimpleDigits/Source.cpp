#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
using namespace std;
bool IsPrime(int value) {
	for (size_t j = 2; j < value; ++j) {
		if (value % j == 0) {
			return false;
		}
	}
	return true;
}
void CountOfDigits(vector<int>& vec, int& pointer, mutex& mutex_pointer, mutex& mutex_counter, int& count) {
	while(true) {
		int a = pointer;
		unique_lock<mutex> ptr(mutex_pointer);
		pointer++;
		ptr.unlock();
		if (pointer >= vec.size()) {
			return;
		}
		if (IsPrime(vec[a])) {
			unique_lock<mutex> guardd(mutex_counter);
			count++;
		}
	}
}



condition_variable cv;
mutex mm;
void NextPrime(int& value, bool& a) {
	unique_lock<mutex> l(mm);
	value++;
	while (!IsPrime(value)) {
		value++;
	}
	a = true;
	cv.notify_one();
	
}

void PrintNextPrime(int& value, bool& finished) {
	unique_lock<mutex> l(mm);
	cv.wait(l, [&]() {
		return finished;
	});
	// атомарно разлочили мьютекс и ждем
	cout << value << endl;
}



atomic<int> counter = 0;
void Increment() {
	for (int i = 0; i < 100000; ++i) {
		counter++;
	}
}
class Spinlock {
	Spinlock() : lock(false) {};
	void Lock() {
		while (lock.exchange(true)) {	}
	}
	void Unlock() {
		lock.store(false);
	}
private:
	atomic<bool> lock;
};

class Semaphore {
	Semaphore(int max_thr) : max_threads(max_thr), counter(0){}

	void Enter() {
		unique_lock<mutex> guard(mut);
		is_full.wait(guard, [&] {
			return counter < max_threads;
		});
		counter++;
	}
	void Leave() {
		unique_lock<mutex> guard(mut);
		is_full.notify_one();
		counter--;
	}
private:
	condition_variable is_full;
	mutex mut;
	int max_threads;
	int counter;
};
void AtomicMultiply(atomic<int>& value, int multiplier) {
	int temp = value.load();
	int result;
	do {
		 result = temp * multiplier;
	} while (!value.compare_exchange_weak(temp, result));
}
void AtomicPow(atomic<int>& value, int power) {
	int old_value = value.load();
	int result = 1;
	do {
		result = 1;
		while (power != 0) {
			result *= old_value;
			power--;
		}
	} while (!value.compare_exchange_weak(old_value, result));
}
//void AtomicMultiply(atomic<int>* value, int multiplier) {
//	int temp = value->load();
//	while (!value->compare_exchange_weak(temp, temp * multiplier)) {
//
//	}
//}
int main() {
	//vector<int> vec{ 1, 2, 3, 4, 5, 6 };
	//int count = 0;
	//int threads_count;
	//cin >> threads_count;
	//vector<thread> threads;
	//mutex mutex_pointer;
	//mutex mutex_counter;
	//int p = 0;
	//for (int i = 0; i < threads_count; ++i) {
	//	threads.push_back(thread(CountOfDigits, ref(vec), ref(p),
	//		ref(mutex_pointer), ref(mutex_counter), ref(count)));
	//}
	//for (size_t i = 0; i < threads_count; ++i) {
	//	threads[i].join();
	//}
	//
	//cout << count;

	/*vector<thread> threads;
	for (int i = 0; i < 16; ++i) {
		threads.emplace_back(Increment);
	}
	for (auto && thr : threads) {
		thr.join();
	}
	cout << counter;*/

	int a = 14;
	thread thr1 = thread(NextPrime, ref(a));
	thread thr2 = thread(PrintNextPrime, ref(a));
	thr1.join();
	thr2.join();

	/*vector<thread> threads;
	atomic<int> value = 5;
	for (int i = 0; i < 5; ++i) {
		threads.emplace_back(AtomicPow, ref(value), 5);
	}
	for (auto& thr : threads) {
		thr.join();
	}
	cout << value;*/
	return 0;
}