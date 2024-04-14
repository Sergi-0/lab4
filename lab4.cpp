#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <list>
#include <algorithm>
#include <set>
#include <unordered_set>
using namespace std;

class Kredit { // Класс кредит

	friend void operator <<(ofstream& t, Kredit& b) { // оператор вывода полей класса в поток
		t << "name:" << b.name << "   " << "summa:" << b.sum << "   " << "valuta:" << b.type_v << "   " << "percent:" << b.percent << endl;
	}

public:
	Kredit(); // конструктор по умолчанию
	Kredit(string a, double b, string c, double d); // конструктор со значениями
	Kredit(const Kredit& a); // конструктор копирования
	Kredit(Kredit&& a); // конструктор перемещения
	void operator =(const Kredit& b); // оператор = копирования
	void operator =(const Kredit&& b); // оператор = перемещения
	bool operator <(const Kredit& b) const; // оператор < сравнения классов

	string getname() const{ return name; } // геттеры полей, будут использованы для получения хэша
	double getsum() const{ return sum; }
	string gettype_v() const{ return type_v; }
	double getpercent() const{ return percent; }

	bool operator ==(const Kredit& b) const { // оператор "равно" для unordered_set
		return sum == b.sum;
	}
private:
	string name; // имя кредита
	double sum; // сумма кредита
	string type_v; // тип валюты
	double percent; // проценты кредита
};

struct KreditHesh { // функтор для создания хэша
	hash<string> shash;
	hash<double> dhash;
	
	size_t operator()(const Kredit& a) const {
		const size_t coef = 5171;
		return (coef * coef * coef * shash(a.getname()) + coef * coef * dhash(a.getsum()) + coef * shash(a.gettype_v()) + dhash(a.getpercent()));
	}
};

Kredit::Kredit() : name("noname"), sum(0), type_v("unknown"), percent(0) {}

Kredit::Kredit(string a, double b, string c, double d) {
	name = a;
	sum = b;
	type_v = c;
	percent = d;
}

Kredit::Kredit(const Kredit& a) {
	name = a.name;
	sum = a.sum;
	type_v = a.type_v;
	percent = a.percent;
}

Kredit::Kredit(Kredit&& a) {
	swap(name, a.name);
	swap(sum, a.sum);
	swap(type_v, a.type_v);
	swap(percent, a.percent);
}

void Kredit::operator =(const Kredit& b) {
	name = b.name;
	sum = b.sum;
	type_v = b.type_v;
	percent = b.percent;
}

void Kredit::operator =(const Kredit&& b) {
	name = b.name;
	sum = b.sum;
	type_v = b.type_v;
	percent = b.percent;
}

bool Kredit::operator <(const Kredit& b) const{
	return sum < b.sum;
}

int main()
{
	ifstream file("input.txt"); // связывание файла с файловым потоком
	string l1, l2, l3, l4, p; // переменные для считывания информации из файла
	getline(file, p);
	int n = atoi(p.c_str()); // количество переменных класса(число в начале файла)
	deque<Kredit> deq1;
	while (!file.eof()) {
		getline(file, l1, '/');
		getline(file, l2, '/');
		getline(file, l3, '/');
		getline(file, l4, '/');
		getline(file, p); // в файле каждая строка оканчивается служебным сиволом /n, этот гитлайн нужен для того чтобы его съесть
		deq1.push_back(Kredit(l1, atof(l2.c_str()), l3, atof(l4.c_str())));
	}

	list<Kredit> list1;
	sort(deq1.begin(), deq1.end()); // сортировка deque с помощью перегрузки оператора < 
	//cout << deq1[1];
	copy(deq1.begin(), deq1.end(), back_inserter(list1));
	//cout << deq1[0];
	//cout << list1.front();
	ofstream gogo("output.txt"); // связывание потока вывода с файлом
	if (gogo.is_open()) for (auto& i : list1) gogo << i;
	gogo.close(); // закрытие файла
	file.close(); // закрытие файла

	set<Kredit> aboba;
	aboba.insert(Kredit("Losos", 11, "dollar", 1));

	unordered_set<Kredit, KreditHesh> boaba;
	boaba.insert(Kredit("Paltus", 12, "Shekel", 228));
}