#include<iostream>
#include<chrono>
#include<sstream>
#include<thread>
#include<vector>
#include<mutex>
using namespace std;
   
//const int sz = 1e8;
//int vec[sz];
//uint64_t CurrentMillisecond(){
//	using namespace chrono;
//    return duration_cast<milliseconds>(
//	system_clock::now().time_since_epoch()).count();
//	}
//void SqrtParallel(int* vec, int start, int num_threads, int sz) {
//	for (int i = start; i < sz; i += num_threads) {
//		vec[i] = sqrt(vec[i]);
//	}
//}

std::mutex hw_mutex;
void PrintHelloWorld() {
	lock_guard<mutex> hw_guard(hw_mutex);
//	hw_mutex.lock();
	cout << "[";
	cout << this_thread::get_id();
	cout << "]:";
	cout << "Hello, World!" << endl;
//	hw_mutex.unlock();
}
class Counter {
	int sum = 0;
	int count = 0;
	mutex mutex_;
public:
	/*Counter(Counter&& other) {

	}*/
	void Update(int value) {
		lock_guard<mutex> g(mutex_);
		sum += value;
		count++;
	}
	double Mean() {
		lock_guard<mutex> g(mutex_);
		return 1.0 * sum / count;
	}
};
int main() {
	/*for (int i = 0; i < sz; ++i) {
		vec[i] = i;
	}
	auto start = CurrentMillisecond();
	cout << "Time elapsed (non-parallel): " << (finish - start) / 1000.0 << endl;

	auto start_parallel = CurrentMillisecond();
	vector<thread> workers;
	for (int i = 0; i < 100; ++i) {
		workers.emplace_back(SqrtParallel, vec, i, 100, sz);
	}
	for (auto& worker : workers) {
		worker.join();
	}
	auto finish_parallel = CurrentMillisecond();
	cout << vec[sz / 2] << endl;
	cout << "Time elapsed (parallel): "
		<< (finish_parallel - start_parallel) / 1000.0 << endl;
	return 0;*/
	/*thread first_thread(PrintHelloWorld);
	thread second_thread = thread(PrintHelloWorld);
	first_thread.join();
	second_thread.join();*/
	//auto counter = Counter();
	Counter counter;
	thread first_thread([&counter]() {
		for (int i = 0; i < 100000; ++i) {
			counter.Update(1);
		}
		});
	first_thread.join();
	thread second_thread([&counter]() {
		for (int i = 0; i < 100000; ++i) {
			counter.Update(2);
		}
		});
	   
	    second_thread.join();
	cout << counter.Mean() << endl;
}