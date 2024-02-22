#include <iostream>
#include <chrono>
#include <cstdlib>
#include <locale.h>

const int INITIAL_CAPACITY = 10; 

int* stackArray; // Массив для хранения элементов стека
int arrayCapacity = INITIAL_CAPACITY; // Емкость массива
int arrayTop = -1; // Индекс вершины стека на массиве

struct Node {
	int data;
	Node* next;

	Node(int val) : data(val), next(nullptr) {}
};

Node* listTop = nullptr; // Указатель на вершину стека на списке

bool arrayIsEmpty() {
	return arrayTop == -1;
}

void arrayPush(int val) {
	if (arrayTop == arrayCapacity - 1) {
		arrayCapacity *= 2;
		int* newArr = new int[arrayCapacity];
		for (int i = 0; i <= arrayTop; ++i) {
			newArr[i] = stackArray[i];
		}
		delete[] stackArray;
		stackArray = newArr;
	}
	stackArray[++arrayTop] = val;
}

int arrayPop() {
	if (arrayIsEmpty()) {
		std::cout << "Стек пуст\n";
		return -1;
	}
	return stackArray[arrayTop--];
}

bool listIsEmpty() {
	return listTop == nullptr;
}

void listPush(int val) {
	Node* newNode = new Node(val);
	newNode->next = listTop;
	listTop = newNode;
}

int listPop() {
	if (listIsEmpty()) {
		std::cout << "Стек пуст\n";
		return -1;
	}
	int data = listTop->data;
	Node* temp = listTop;
	listTop = listTop->next;
	delete temp;
	return data;
}

int main() {
	setlocale(LC_ALL, "Rus");

	std::cout << "Реализация стека" << std::endl;

	stackArray = new int[arrayCapacity];

	const int ELEMENTS_COUNT = 100000;

	auto startArrayPush = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < ELEMENTS_COUNT; ++i) {
		arrayPush(rand() % 100);
	}

	auto endArrayPush = std::chrono::high_resolution_clock::now();

	auto startArrayPop = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < ELEMENTS_COUNT; ++i) {
		arrayPop();
	}

	auto endArrayPop = std::chrono::high_resolution_clock::now();

	auto startListPush = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < ELEMENTS_COUNT; ++i) {
		listPush(rand() % 100);
	}

	auto endListPush = std::chrono::high_resolution_clock::now();

	auto startListPop = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < ELEMENTS_COUNT; ++i) {
		listPop();
	}

	auto endListPop = std::chrono::high_resolution_clock::now();

	std::cout << "Время добавления элементов в массив: "
		<< std::chrono::duration_cast<std::chrono::microseconds>(endArrayPush - startArrayPush).count()
		<< " мкс" << std::endl;

	std::cout << "Время удаления элементов из массива: "
		<< std::chrono::duration_cast<std::chrono::microseconds>(endArrayPop - startArrayPop).count()
		<< " мкс" << std::endl;

	std::cout << "Время добавления элементов в список: "
		<< std::chrono::duration_cast<std::chrono::microseconds>(endListPush - startListPush).count()
		<< " мкс" << std::endl;

	std::cout << "Время удаления элементов из списка: "
		<< std::chrono::duration_cast<std::chrono::microseconds>(endListPop - startListPop).count()
		<< " мкс" << std::endl;

	delete[] stackArray;

	return 0;
}
