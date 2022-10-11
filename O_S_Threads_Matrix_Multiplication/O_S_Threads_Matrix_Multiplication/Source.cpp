#include <iostream>
#include<vector>
#include<thread>
#include<mutex>
using namespace std;
void MultiplyMatrix(int k, int n, vector<vector<int>>& a,
	vector<vector<int>>& b, vector<vector<int>>& product) {
	for (k; k < n; ++k) {
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < n; j++) {
				product[k][i] += a[k][j] * b[j][i];
			}
		}
	}
}
int main() {
	int n;
	cin >> n;
	int copy = n;
	vector < vector<int>> a(n, vector<int>(n));
	vector < vector<int>> b(n, vector<int>(n));
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			cin >> b[i][j];
		}
	}

	vector <vector<int>> product(n, vector<int>(n));

	/*thread first_thread([n, a, b, &product]() {
		for (int k = 0; k < n/2; ++k) {
			for (size_t i = 0; i < n; i++) {
				for (size_t j = 0; j < n; j++) {
					product[k][i] += a[k][j] * b[j][i];
				}
			}
		}
		});

	thread second_thread([n, a, b, &product]() {
		for (int k = n/2; k < n; ++k) {
			for (size_t i = 0; i < n; i++) {
				for (size_t j = 0; j < n; j++) {
					product[k][i] += a[k][j] * b[j][i];
				}
			}
		}
		});
	first_thread.join();
	second_thread.join();*/
	vector<thread> threads;
	int count = 0;
	for (size_t k = 0; k < n; ++k) {
		threads.emplace_back([k, n, a, b, &product]() {
			for (size_t i = 0; i < n; i++) {
				for (size_t j = 0; j < n; j++) {
					product[k][i] += a[k][j] * b[j][i];
				}
			}
			});
	}
	for (size_t i = 0; i < n; ++i) {
		threads[i].join();
	}
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			cout << product[i][j] << " ";
		}
		cout << endl;
	}
}
