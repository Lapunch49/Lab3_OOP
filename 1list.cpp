#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <ctime>

using namespace std;

class Object { // базовый абстрактный класс
public:
	Object() {
		printf("Object() ");
	}
	virtual string classname() = NULL;
	virtual ~Object() {
		printf("~Object()\n");
	}
};

class Storage { // класс хранилища
private:
	int n; // размер
	int k; // количество элементов
	Object** st; // динамический массив указателей на Object
public:
	Storage() {
		st = new Object* [1];
		n = 1;
		k = 0;
	}
	Storage(int size) {
		st = new Object* [size];
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
		if (k < n) { // если место есть, просто вставляем в конец
			st[k] = new_el;
			k = k + 1;
		}
		else { // изменяем размер массива - увеличиваем в 2 раза
			//n = n + 1;
			n = n * 2; // чтобы не перекопировать много раз
			Object** st_ = new Object*[n];
			for (int i = 0; i < k; ++i)
				st_[i] = st[i];
			st_[k] = new_el;
			k = k + 1;
			// мб очистить память
			for (int i = 0; i < k; i++)
				if (st[i] != nullptr)
					delete (st[i]);
			////////////////
			st = st_;
		}
	}
	void del(int ind) {
		for (int i = ind; i < k - 1; ++i)
			st[i] = st[i + 1];
		k = k - 1;
		st[k] = nullptr;
	}
	void del_withDelObj(int ind) {
		delete st[ind]; // ? будет ли корректно работать 
		for (int i = ind; i < k - 1; ++i)
			st[i] = st[i + 1];
		k = k - 1;
		st[k] = nullptr;
	}
	Object* get_el(int ind) {
		return st[ind];
	}
	int get_count() {
		return k;
	}
	// мб get_size()
};
 // классы-потомки базового
class Point: public Object {
	int x;
	int y;
public:
	Point() {
		printf("Point()");
		x = 0; y = 0;
	}
	Point(int x, int y) {
		printf("Point(int x, int y)");
		this->x = x;
		this->y = y;
	}
	string classname() {
		printf("Point::classname()\n");
		return "Point";
	}
	int get_x() {
		printf("Point::get_x()\n");
		return x;
	}
	int get_y() {
		printf("Point::get_y()\n");
		return y;
	}
	void set_x(int new_x) {
		printf("Point::set_x(int new_x)\n");
		x = new_x;
	}
	void set_y(int new_y) {
		printf("Point::set_y(int new_y)\n");
		y = new_y;
	}
	~Point() {
		printf("~Point() ");
	}
};

class Circle : public Point {
	int r;
public:
	Circle() {
		printf("Circle()\n");
		r = rand() % 100;
	}
	Circle(int rad) {
		printf("Circle(int rad)\n");
		if (rad >= 0)
			r = rad;
		else r = rand() % 100;
	}
	string classname() {
		printf("Circle::classname()\n");
		return "Circle";
	}
	int get_r() {
		printf("Circle::get_r()\n");
		return r;
	}
	void set_r(int new_r) {
		printf("CCircle::set_r(int new_r)\n");
		r = new_r;
	}
	void calc_diameter() {
		printf("The diameter is %d\n", 2 * r);
	}
	void calc_perimeter() {
		printf("The perimeter of the circle is %f\n", 2 * M_PI * r);
	}
	void calc_square() {
		printf("The square of the circle is %f\n", M_PI * r * r);
	}
	~Circle() {
		printf("~Circle() ");
	}
};

class Rectangle : public Point {
	int l; // длина
	int w; // ширина
public:
	Rectangle() {
		printf("Rectangle()\n");
		l = rand() % 100;
		w = rand() % 100;
	}
	Rectangle(int length, int weigth) {
		printf("Rectangle()\n");
		if (length >= 0)
			l = length;
		else l = rand() % 100;
		if (weigth >= 0)
			w = weigth;
		else w = rand() % 100;
	}
	string classname() {
		printf("Rectangle::classname()\n");
		return "Rectangle";
	}
	int get_l() {
		printf("Rectangle::get_l()\n");
		return l;
	}
	int get_w() {
		printf("Rectangle::get_w()\n");
		return w;
	}
	void set_l(int new_l) {
		printf("Rectangle::set_l(int new_l)\n");
		if (new_l >= 0)
			l = new_l;
	}
	void set_w(int new_w) {
		printf("Rectangle::set_w(int new_w)\n");
		if (new_w >= 0)
			w = new_w;
	}
	void calc_perimeter() {
		int P = 2 * (l + w);
		printf("The perimeter of the rectangle is %d\n", P);
	}
	void calc_square() {
		int S = l * w;
		printf("The square of the rectangle is %d\n", S);
	}
	~Rectangle() {
		printf("~Rectangle()");
	}
};

class Triangle : public Object {
	int a,b,c; // длины сторон
public:
	Triangle() {
		printf("Triangle()\n");
		a = rand() % 100;
		b = rand() % 100;
		c = rand() % 100;
	}
	Triangle(int A, int B, int C) {
		printf("Triangle()\n");
		a = rand() % 100;
		b = rand() % 100;
		c = rand() % 100;
		if (A >= 0) a = A;
		if (B >= 0) b = B;
		if (C >= 0) c = C;
	}
	string classname() {
		printf("Triangle::classname()\n");
		return "Triangle";
	}
	int get_a() {
		printf("Triangle::get_a()\n");
		return a;
	}
	int get_b() {
		printf("Triangle::get_b()\n");
		return b;
	}
	int get_c() {
		printf("Triangle::get_c()\n");
		return c;
	}
	void set_abc(int a, int b, int c) {
		printf("Triangle::set_abc(int a, int b, int c)\n");
		this->a = a;
		this->b = b;
		this->c = c;
	}
	int calc_perimeter() {
		int P = a + b + c;
		printf("The perimeter of the triangle is %d\n", P);
		return P;
	}
	float calc_square() {
		float p = (calc_perimeter())/2;
		float S = sqrt(p * (p - a) * (p - b) * (p - c));
		printf("The square of the triangle is %f\n", S);
		return S;
	}
	void get_r_and_R() {
		float p = (calc_perimeter()) / 2;
		float S = calc_square();
		float r = S / p;
		float R = a * b * c / 4 / S;
		printf("The radius of inscribed circle is %f\n", r);
		printf("The radius of circumscribed circle is %f\n", r);
	}
	~Triangle() {
		printf("~Triangle() ");
	}
};

//class Animal : public Object {
//	string name;
//public:
//	Animal() {
//		printf("Animal() ");
//		name = "";
//	}
//	string classname() {
//		printf("Animal::classname()\n");
//		return "Animal";
//	}
//	void get_name() {
//		cout << "The name of " << classname() << " is " << name << endl;
//	}
//	virtual void sound() = NULL;
//};
//
//class Cat : public Animal {
//	string voice = "mew-mew";
//public:
//	//void s
//};

int main() {
	srand(time(NULL));
	// создаем хранилище
	Storage st(10);
	//for (int i = 0; i < st.get_count(); ++i)
	//	st.add(new Object());
	//for (int i = 0; i < st.get_count(); ++i)
		//arr.get_el(i).some_method();
	
	return 0;
}