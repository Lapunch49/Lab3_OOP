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
		printf("Object()");
	}
	virtual string classname() = NULL;
	virtual ~Object() {
		printf("~Object()\n");
	}
	virtual void someMethod() = NULL;
};

class Storage { // класс хранилища
private:
	int n; // размер
	int k; // количество элементов
	Object** st; // динамический массив указателей на Object
public:
	Storage() {
		st = new Object* [1];
		st[0] = nullptr; /// добавлено
		n = 1;
		k = 0;
	}
	Storage(int size) {
		st = new Object* [size];
		n = size;
		k = 0;
		for (int i = 0; i < n; ++i) // Добавлено
			st[i] = nullptr;
	}
	~Storage()
	{
		for (int i = 0; i < k; i++)
			if (st[i] != nullptr)
				delete (st[i]);
		delete[] st;
		//delete st;
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
			for (int i = k; i < n; ++i) /// добавлено
				st_[i] = nullptr;
			st = st_;
		}
	}
	void insert(int ind, Object* new_obj) { 
		// вставляем в конец и меняем местами с элементом, имеющим нужный индекс
		add(new_obj);
		Object* tmp = st[ind]; // поверхностное копирование
		st[ind] = st[k-1];
		st[k-1] = tmp;
	}
	void del(int ind) {
		for (int i = ind; i < k - 1; ++i)
			st[i] = st[i + 1];
		k = k - 1;
		st[k] = nullptr;
	}
	void delWithDelObj(int ind) {
		Object* tmp = st[ind];
		for (int i = ind; i < k - 1; ++i)
			st[i] = st[i + 1];
		k = k - 1;
		st[k] = nullptr;
		delete tmp; // изменено
	}
	Object* get_el(int ind) {
		return st[ind];
	}
	int get_count() {
		return k;
	}
	int get_size() {
		return n;
	}
};
 // классы-потомки базового
class Point: public Object {
	int x;
	int y;
public:
	Point() {
		printf("Point()");
		x = rand() % 200 - 100; 
		y = rand() % 200 - 100;
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
		printf("Point::get_x()->%d\n",x);
		return x;
	}
	int get_y() {
		printf("Point::get_y()->%d\n",y);
		return y;
	}
	void set_x(int new_x) {
		printf("Point::set_x(int new_x)->%d-->%d\n", x, new_x);
		x = new_x;
	}
	void set_y(int new_y) {
		printf("Point::set_y(int new_y)->%d-->%d\n", y, new_y);
		y = new_y;
	}
	~Point() {
		printf("~Point()");
	}
	void someMethod() {
		int rand_num = rand() % 5;
		switch (rand_num) {
		case 0: { classname(); break; }
		case 1: { get_x(); break; }
		case 2: { get_y(); break; }
		case 3: { set_x(rand()%100); break; }
		default: { set_y(rand()%100); break; }
		}
	}
};

class Circle : public Point {
	int r;
public:
	Circle() {
		printf("Circle()");
		r = rand() % 100;
	}
	Circle(int rad) {
		printf("Circle(int rad)");
		if (rad >= 0)
			r = rad;
		else r = rand() % 100;
	}
	string classname() {
		printf("Circle::classname()\n");
		return "Circle";
	}
	int get_r() {
		printf("Circle::get_r()->%d\n",r);
		return r;
	}
	void set_r(int new_r) {
		printf("Circle::set_r(int new_r)->%d-->%d\n", r, new_r);
		r = new_r;
	}
	void calc_diameter() {
		printf("Circle: the diameter is %d\n", 2 * r);
	}
	void calc_perimeter() {
		printf("Circle: the perimeter is %f\n", 2 * M_PI * r);
	}
	void calc_square() {
		printf("Circle: the square is %f\n", M_PI * r * r);
	}
	~Circle() {
		printf("~Circle()");
	}
	void someMethod() {
		int rand_num = rand() % 10;
		switch (rand_num) {
		case 0: case 1: case 2: case 3:
		case 4: { printf("Circle::"); Point::someMethod(); break; }
		case 5: { get_r(); break; }
		case 6: { set_r(rand()%100); break; }
		case 7: { calc_diameter(); break; }
		case 8: { calc_perimeter(); break; }
		default: { calc_square(); break; }
		}
	}
};

class Rectangle : public Point {
	int l; // длина
	int w; // ширина
public:
	Rectangle() {
		printf("Rectangle()");
		l = rand() % 100;
		w = rand() % 100;
	}
	Rectangle(int length, int weigth) {
		printf("Rectangle()");
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
		printf("Rectangle:: the perimeter is %d\n", P);
	}
	void calc_square() {
		int S = l * w;
		printf("Rectangle:: the square is %d\n", S);
	}
	~Rectangle() {
		printf("~Rectangle()");
	}
	void someMethod() {
		int rand_num = rand() % 11;
		switch (rand_num) {
		case 0: case 1: case 2: case 3:
		case 4: { printf("Rectangle::"); Point::someMethod(); break; }
		case 5: { get_l(); break; }
		case 6: { get_w(); break; }
		case 7: { set_l(rand() % 100); break; }
		case 8: { set_w(rand() % 100); break; }
		case 9: { calc_perimeter(); break; }
		default: { calc_square(); break; }
		}
	}
};

class Triangle : public Object {
	int a,b,c; // длины сторон
public:
	Triangle() {
		printf("Triangle()");
		a = rand() % 100;
		b = rand() % 100;
		c = rand() % 100;
	}
	Triangle(int A, int B, int C) {
		printf("Triangle(int A, int B, int C)");
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
		printf("Triangle:: the perimeter is %d\n", P);
		return P;
	}
	float calc_square() {
		float p = (calc_perimeter())/2;
		float S = sqrt(p * (p - a) * (p - b) * (p - c));
		printf("Triangle:: the square is %f\n", S);
		return S;
	}
	void get_r_and_R() {
		float p = (calc_perimeter()) / 2;
		float S = calc_square();
		float r = 0;
		float R = 0;
		if (p != 0)
			r = S / p;
		if (S != 0 )
			R = a * b * c / 4 / S;
		printf("Triangle:: the radius of inscribed circle is %f\n", r);
		printf("And the radius of circumscribed circle is %f\n", r);
	}
	~Triangle() {
		printf("~Triangle()");
	}
	void someMethod() {
		int rand_num = rand() % 8;
		switch (rand_num) {
		case 0: { classname(); break; }
		case 1: { get_a(); break; }
		case 2: { get_b(); break; }
		case 3: { get_c(); break; }
		case 4: { set_abc(rand()%100, rand() % 100, rand() % 100); break; }
		case 5: { calc_perimeter(); break; }
		case 6: { calc_square(); break; }
		default: {get_r_and_R(); break; }
		}
	}
};

Object* someObj() { // возвращает объект случайно выбранного класса 
	int rand_num = rand() % 4;
	switch (rand_num)
	{
	case 0: return new Circle();
	case 1: return new Rectangle();
	case 2: return new Triangle();
	default: return new Point();
	}
}

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
	unsigned int start_time = clock();

	srand(time(NULL));

	// создаем хранилище
	Storage myStor(100);

	// заполняем какими-то объектами
	for (int i = 0; i < myStor.get_size(); ++i) {
		myStor.add(someObj());
		printf("\n");
	}
	printf("-----------------------------------------------\n");

	// вызываем случайные методы у каждого объекта
	for (int i = 0; i < myStor.get_count(); ++i) {
		printf("%-3d:", i + 1);
		(myStor.get_el(i))->someMethod();
	}
	printf("-----------------------------------------------\n");

	// запускаем цикл из 1000 случайных действий(удаление и уничтожение объекта из хранилища, 
	// добавление в конец или вставка по индексу нового объекта, запуск любого метода у случайного объекта)
	for (int i = 0; i < 1000; ++i) {
		printf("%-3d:", i+1);
		int rand_num = rand() % 5; 
		int ind = rand() % (myStor.get_count()); // индекс элемента, с которым что-то произойдет (кроме случая 2)
		switch (rand_num)
		{
		case 0: {printf("myStor.del(ind) "); myStor.del(ind); printf("\n"); break; }
		case 1: {printf("myStor.delWithDelObj(ind) "); myStor.delWithDelObj(ind); break; }
		case 2: {printf("myStor.add(someObj()) "); myStor.add(someObj());printf("\n"); break; }
		case 3: {printf("myStor.insert(ind,someObj()) "); myStor.insert(ind,someObj()); printf("\n"); break; }
		default: {printf("myStor.get_el(ind)->someMethod() ");
			myStor.get_el(ind)->someMethod(); 
			break; 
		}
		}
	}
	printf("-----------------------------------------------\n");

	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	printf("Time of program`s execution is %d ms\n", search_time);

	printf("The count of objects in storage: %d\n", myStor.get_count());
	printf("The size of storage: %d\n", myStor.get_size());

	return 0;
}