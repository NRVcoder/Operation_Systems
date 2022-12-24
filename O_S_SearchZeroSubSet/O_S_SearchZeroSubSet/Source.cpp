#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <unordered_set>
#include <set>
#include <unordered_map>
using namespace std;
vector<int> FindSubset(vector<int>& vec, int n) {
	for (int i = 1; i <= n; ++i) {
		vector<int> a(i);
		for (int j = 0; j < n; ++j) {
			for (int t = 0; t < a.size(); ++t) {
				a[t] = vec[j];
				for (int k = 0; k < n; ++k) {
					if (a[0] + vec[k] == 0) {

					}

				}
		    }
		}
	}
}
int main() {
	//unordered_set<int> set;
	//for (size_t i = 0; i < 10; i++){
	//	set.insert(i);
	//}
	//int x;
	//cin >> x;
	//for (size_t i = 0; i < 10; i++) {
	//	cout << set[i];
	//}
	//if (set.count(x)) {
	//	cout << x;
	//}
	int n;
	cin >> n;
	vector<int> vec(n);
	for (int i = 0; i < n; ++i) {
		cin >> vec[i];
	}
	
	for (int i = 0; i < 10; ++i) {
		cout << it
	}
}
