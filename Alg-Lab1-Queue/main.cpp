#include <iostream>
#include <chrono>
#include <cstdlib>
#include <locale.h>

const int INITIAL_CAPACITY = 10;

int* queueArray; // Массив для хранения элементов очереди
int arrayCapacity = INITIAL_CAPACITY; // Емкость массива
int queueFront = 0; // Индекс начала очереди в массиве
int queueRear = -1; // Индекс конца очереди в массиве
int queueSize = 0; // Размер очереди

struct Node {
	int data;
	Node* next;

	Node(int val) : data(val), next(nullptr) {}
};

Node* queueFrontNode = nullptr; // Указатель на начало очереди на списке
Node* queueRearNode = nullptr; // Указатель на конец очереди на списке

bool queueIsEmpty() {
	return queueSize == 0;
}

void queueEnqueue(int val) {
	if (queueSize == arrayCapacity) {
		std::cout << "Очередь переполнена\n";
		return;
	}
	if (queueRear == arrayCapacity - 1) {
		queueRear = -1; // Циклический перенос конца очереди в начало массива
	}
	queueArray[++queueRear] = val;
	queueSize++;
}

int queueDequeue() {
	if (queueIsEmpty()) {
		std::cout << "Очередь пуста\n";
		return -1;
	}
	int data = queueArray[queueFront++];
	if (queueFront == arrayCapacity) {
		queueFront = 0; // Циклический перенос начала очереди в начало массива
	}
	queueSize--;
	return data;
}

void listQueueEnqueue(int val) {
	Node* newNode = new Node(val);
	if (queueFrontNode == nullptr) {
		queueFrontNode = newNode;
	}
	else {
		queueRearNode->next = newNode;
	}
	queueRearNode = newNode;
	queueSize++;
}

int listQueueDequeue() {
	if (queueIsEmpty()) {
		std::cout << "Очередь пуста\n";
		return -1;
	}
	int data = queueFrontNode->data;
	Node* temp = queueFrontNode;
	queueFrontNode = queueFrontNode->next;
	delete temp;
	queueSize--;
	return data;
}

int main() {
	setlocale(LC_ALL, "Rus");

	std::cout << "Реализация очереди" << std::endl;

	queueArray = new int[arrayCapacity];

	const int ELEMENTS_COUNT = 100000;

	auto startArrayEnqueue = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < ELEMENTS_COUNT; ++i) {
		queueEnqueue(rand() % 100);
	}

	auto endArrayEnqueue = std::chrono::high_resolution_clock::now();

	auto startArrayDequeue = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < ELEMENTS_COUNT; ++i) {
		queueDequeue();
	}

	auto endArrayDequeue = std::chrono::high_resolution_clock::now();

	std::cout << "Время добавления элементов в очередь (массив): "
		<< std::chrono::duration_cast<std::chrono::microseconds>(endArrayEnqueue - startArrayEnqueue).count()
		<< " мкс" << std::endl;

	std::cout << "Время удаления элементов из очереди (массив): "
		<< std::chrono::duration_cast<std::chrono::microseconds>(endArrayDequeue - startArrayDequeue).count()
		<< " мкс" << std::endl;

	delete[] queueArray;

	Node* queueFrontNode = nullptr;
	Node* queueRearNode = nullptr;

	auto startListEnqueue = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < ELEMENTS_COUNT; ++i) {
		listQueueEnqueue(rand() % 100);
	}

	auto endListEnqueue = std::chrono::high_resolution_clock::now();

	auto startListDequeue = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < ELEMENTS_COUNT; ++i) {
		listQueueDequeue();
	}

	auto endListDequeue = std::chrono::high_resolution_clock::now();

	std::cout << "Время добавления элементов в очередь (список): "
		<< std::chrono::duration_cast<std::chrono::microseconds>(endListEnqueue - startListEnqueue).count()
		<< " мкс" << std::endl;

	std::cout << "Время удаления элементов из очереди (список): "
		<< std::chrono::duration_cast<std::chrono::microseconds>(endListDequeue - startListDequeue).count()
		<< " мкс" << std::endl;

	return 0;
}
