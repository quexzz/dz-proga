#include <iostream>
#include <climits> // Для использования константы INT_MAX
using namespace std;

// Определение узла для связанного списка
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Определение класса очереди на основе связанного списка
class Queue {
private:
    Node* front; // Указатель на начало очереди
    Node* rear;  // Указатель на конец очереди

public:
    // Конструктор, инициализирующий пустую очередь
    Queue() : front(nullptr), rear(nullptr) {}

    // Деструктор для освобождения всей выделенной памяти
    ~Queue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    // Метод для добавления элемента в конец очереди
    void enqueue(int val) {
        Node* newNode = new Node(val); // Создаем новый узел
        if (rear == nullptr) { // Если очередь пуста
            front = rear = newNode; // Устанавливаем новый узел как начальный и конечный элементы
        }
        else {
            rear->next = newNode; // Устанавливаем связь текущего последнего элемента с новым элементом
            rear = newNode; // Перемещаем указатель на конец очереди на новый элемент
        }
    }

    // Метод для удаления элемента из начала очереди
    void dequeue() {
        if (front == nullptr) {
            cout << "Очередь пуста. Невозможно выполнить удаление." << endl;
            return;
        }
        Node* temp = front; // Сохраняем указатель на начальный элемент
        front = front->next; // Перемещаем указатель на начало на следующий элемент
        if (front == nullptr) {
            rear = nullptr; // Если после удаления очередь стала пустой, обнуляем указатель на конец
        }
        delete temp; // Освобождаем память, занимаемую предыдущим начальным элементом
    }

    // Метод для получения значения переднего элемента без удаления
    int peek() const {
        if (front == nullptr) {
            throw runtime_error("Очередь пуста");
        }
        return front->data;
    }

    // Метод для проверки, пуста ли очередь
    bool isEmpty() const {
        return front == nullptr;
    }

    // Метод для вставки минимального элемента перед каждым числом, равным последнему числу
    void insertMinBeforeLast() {
        if (isEmpty()) return; // Проверка пустоты очереди

        int last = rear->data; // Сохранение последнего элемента
        int min_element = INT_MAX; // Инициализация минимального элемента

        // Нахождение минимального элемента в очереди
        Node* temp = front; // Временный указатель для прохода по очереди
        while (temp != nullptr) {
            if (temp->data < min_element) {
                min_element = temp->data; // Обновление минимального элемента
            }
            temp = temp->next; // Переход к следующему элементу
        }

        // Создание временной очереди для хранения элементов, которые нужно вставить
        Queue tempQueue;

        // Проверка каждого элемента, пока не дойдем до последнего
        while (!isEmpty()) {
            int current = peek();
            dequeue();

            // Если текущий элемент равен последнему, добавляем минимальный элемент перед ним
            if (current == last) {
                tempQueue.enqueue(min_element);
            }
            tempQueue.enqueue(current); // Добавление текущего элемента
        }

        // Перенос элементов из временной очереди обратно в основную
        while (!tempQueue.isEmpty()) {
            enqueue(tempQueue.peek());
            tempQueue.dequeue();
        }
    }

    // Метод для вывода содержимого очереди
    void display() const {
        Node* temp = front; // Указатель для прохода по элементам очереди
        while (temp != nullptr) { // Пока не достигнем конца очереди
            cout << temp->data << " "; // Выводим значение текущего элемента
            temp = temp->next; // Переходим к следующему элементу
        }
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Queue q; // Создаем объект очереди
    int n; // Переменная для хранения количества элементов

    cout << "Введите количество элементов в очереди: ";
    cin >> n; // Ввод количества элементов

    cout << "Введите элементы очереди: ";
    for (int i = 0; i < n; ++i) { // Цикл для ввода элементов
        int num;
        cin >> num;
        q.enqueue(num); // Добавление элемента в очередь
    }

    q.insertMinBeforeLast(); // Вызов функции для вставки минимального элемента

    // Вывод преобразованной очереди
    cout << "Очередь после вставки минимального элемента перед каждым числом, равным последнему: ";
    q.display(); // Печать элементов очереди

    return 0;
}
