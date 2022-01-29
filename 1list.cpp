#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Object {

};

class Storage {
private:
	int n;//размер
	int k;//количество элементов
	Object** st;//динамический массив указателей на Object
public:
	Storage() {
		st = new Object*[2];
		n = 2;
		k = 0;
	}
	Storage(int size) {
		st = new Object * [size];
		n = size;
		k = 0;
	}
	~Storage()
	{
		for (int i = 0; i < k; i++)
			if (st[i] != nullptr)
				delete (st[i]);
		delete[] st;
	}

	void add(Object* new_el) {
		if (k < n) {
			st[k] = new_el;
			k = k + 1;
		}
		else {
			n = n*2;
			Object** st_ = new Object*[n];
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
	Object* get_el(int ind) {
		return st[ind];
	}
	int get_count() {
		return k;
	}
};


int main() {
	Storage st;
	for (int i = 0; i < st.get_count(); ++i)
		st.add(new Object());
	//for (int i = 0; i < st.get_count(); ++i)
		//arr.get_el(i).some_method();

	return 0;
}