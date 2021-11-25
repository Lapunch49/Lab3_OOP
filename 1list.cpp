#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

template <class S>
class Storage {
private:
	int n;//размер
	int k;//количество элементов
	S** st;//динамический массив указателей на S
public:
	Storage() {
		st = new S*[2];
		n = 2;
		k = 0;
	}
	Storage(int size) {
		st = new S * [size];
		n = size;
		k = 0;
	}
	~Storage() {
		delete[] st;
	}

	void add(S* new_el) {
		if (k < n) {
			st[k] = new_el;
			k = k + 1;
		}
		else {
			n = n + 1;
			S** st_ = new S*[n];
			for (int i = 0; i < k; ++i)
				st_[i] = st[i];
			st_[k] = new_el;
			k = k + 1;
			st = st_;
		}
	}
	void del(int ind) {
		for (int i = ind; i < k - 1; ++i)
			st[i] = st[i + 1];
		k = k - 1;
	}
	S* get_el(int ind) {
		return st[ind];
	}
	int get_count() {
		return k;
	}
};


int main() {
	return 0;
}