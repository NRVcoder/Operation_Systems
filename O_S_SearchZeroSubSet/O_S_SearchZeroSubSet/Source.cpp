#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int main() {
	unordered_set<int> set;
	for (size_t i = 0; i < 10; i++){
		set.insert(i);
	}
	int x;
	cin >> x;
	if (set.count(x)) {
		cout << x;
	}

}
