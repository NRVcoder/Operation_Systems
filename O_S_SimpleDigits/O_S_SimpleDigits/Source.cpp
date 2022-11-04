#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<chrono>
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
int main() {
	vector<int> vec{ 1, 2, 3, 4, 5, 6 };
	int count = 0;
	int threads_count;
	cin >> threads_count;
	vector<thread> threads;
	mutex mutex_pointer;
	mutex mutex_counter;
	int p = 0;
	for (int i = 0; i < threads_count; ++i) {
		threads.push_back(thread(CountOfDigits, ref(vec), ref(p),
			ref(mutex_pointer), ref(mutex_counter), ref(count)));
	}

	for (size_t i = 0; i < threads_count; ++i) {
		threads[i].join();
	}
	
	cout << count;
}