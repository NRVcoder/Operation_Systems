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
void CountOfDigits(vector<int>& vec, int l, int r, mutex& mut, int& count) {
	for (int i = l; i < r; ++i) {
		if (IsPrime(vec[i])) {
			unique_lock<mutex> guardd(mut);
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
	int r = 0;
	int l = 0;
	int num = vec.size() / threads_count;
	for (size_t i = 0; i < threads_count; ++i) {
		l = num * i;
		if (i == threads_count - 1) {
			r = vec.size();
		}
		else {
			r += vec.size() / threads_count;
		}
		mutex m;
		/*threads.push_back(thread([&vec, l, r, &m, &count]() {

			for (int i = l; i < r; ++i) {

				if (IsPrime(vec[i])== true) {
					unique_lock<mutex> guardd(m);
					count++;
					guardd.unlock();
				}
			}

			}));*/
		threads.push_back(thread(CountOfDigits, ref(vec), l,
			r, ref(m), ref(count)));
	}

	for (size_t i = 0; i < threads_count; ++i) {
		threads[i].join();
	}
	
	cout << count;
}