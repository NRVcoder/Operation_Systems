#include <iostream>
#include<vector>
#include<thread>
#include<mutex>
using namespace std;
void CountOdd(const vector<int>& vec, int l, int r, mutex& m, int& counter) {
	for (int i = l; i < r; ++i) {
		if (vec[i] % 2 == 1) {
			unique_lock<mutex> guard(m);
			counter++;
		}
	}
}
int main(){
	int n;
	cin >> n;
	vector<int> vec(n);
	for (int i = 0; i < vec.size(); ++i) {
		cin >> vec[i];
	}
	/*for (int value : vec) {
		cin >> value;
	}*/
	int num_threads;
	cin >> num_threads;
	vector<thread> threads;
	int counter = 0;
	for (int i = 0; i < num_threads; ++i) {
		int ln = vec.size() / num_threads;
		int l = i * ln;
		int r = (i + 1) * ln;
		if (i == num_threads - 1) {
			r = vec.size();
		}
		mutex m;
		threads.push_back(thread(CountOdd, ref(vec), l, r, ref(m), ref(counter)));
	}
	for (int i = 0; i < num_threads; ++i) {
		threads[i].join();
	}
	cout << counter << endl;
	return 0;
}
