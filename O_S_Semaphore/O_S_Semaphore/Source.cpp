#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <unordered_set>
#include <unordered_map>
#include <condition_variable>
using namespace std;
class Semaphore {
	Semaphore(int max_thr) : max_threads(max_thr), counter(0) {}
	void Enter() {
		unique_lock<mutex> guard(m);
		while (counter == max_threads) {
			cv.wait(guard);
		}
		counter++;
	}
	void Leave() {
		unique_lock<mutex> guard(m);
		if (counter == max_threads) {
			cv.notify_one();
		}
		counter--;
	}
private:
	condition_variable cv;
	mutex m;
	int max_threads;
	int counter;
};
int main() {
	unordered_set<int> set;
	for (size_t i = 0; i < 10; i++) {
		set.insert(i);
	}
	int x;
	cin >> x;
	if (set.count(x)) {
		cout << x;
	}

}
