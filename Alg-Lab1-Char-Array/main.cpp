#include <iostream>
#include <chrono>

// Этот код - заготовка для следующей лабораторной
// С ним ничего не делать и в отчет не включать!!!

void add(int* a, int len, char c);

void del(int* a, int len, char c);

void init_array(int* a, int len);

void print_array(int* a, int len);

int main() {
	setlocale(LC_ALL, "Rus");

	const int ELEMENTS_COUNT = 26;

	int alphabet[ELEMENTS_COUNT];

	init_array(alphabet, ELEMENTS_COUNT);

	auto start_add = std::chrono::high_resolution_clock::now();

	for (int i = 'a'; i <= 'z'; i++) {
		add(alphabet, ELEMENTS_COUNT, i);
	}

	auto end_add = std::chrono::high_resolution_clock::now();

	auto start_delete = std::chrono::high_resolution_clock::now();

	for (int i = 'a'; i <= 'z'; i++) {
		add(alphabet, ELEMENTS_COUNT, i);
	}

	auto end_delete = std::chrono::high_resolution_clock::now();

	std::cout << "Время добавления элементов в массив: "
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(end_add - start_add).count()
		<< " нс" << std::endl;

	std::cout << "Время удаления элементов из массива: "
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(end_delete - start_delete).count()
		<< " нс" << std::endl;

	return 0;
}

void add(int* a, int len, char c) {
	a[c - 'a'] = c;
}

void del(int* a, int len, char c) {
	a[c - 'a'] = -1;
}

void init_array(int* a, int len) {
	for (int i = 0; i < len; i++) {
		a[i] = -1;
	}
}

void print_array(int* a, int len) {
	for (int i = 0; i < len; i++) {
		std::cout << a[i] << ' ';
	}
}