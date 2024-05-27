#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// Функция для переупорядочивания элементов в стеке так, чтобы сначала шли четные, а потом нечетные числа
stack<int> reorderStack(stack<int>& originalStack) {
    queue<int> evenQueue; // Очередь для четных чисел
    queue<int> oddQueue; // Очередь для нечетных чисел

    // Перемещаем четные числа в очередь четных чисел, а нечетные - в очередь нечетных чисел
    while (!originalStack.empty()) {
        int current = originalStack.top(); // Получаем верхний элемент исходного стека
        originalStack.pop(); // Удаляем его из исходного стека

        if (current % 2 == 0) { // Если текущий элемент четный
            evenQueue.push(current); // Добавляем его в очередь четных чисел
        }
        else { // Если текущий элемент нечетный
            oddQueue.push(current); // Добавляем его в очередь нечетных чисел
        }
    }

    // Переносим элементы из очередей обратно в стек в нужном порядке
    while (!oddQueue.empty()) {
        originalStack.push(oddQueue.front()); // Добавляем передний элемент очереди нечетных чисел в исходный стек
        oddQueue.pop(); // Удаляем его из очереди нечетных чисел
    }
    while (!evenQueue.empty()) {
        originalStack.push(evenQueue.front()); // Добавляем передний элемент очереди четных чисел в исходный стек
        evenQueue.pop(); // Удаляем его из очереди четных чисел
    }

    // Переносим все элементы из оригинального стека в результирующий стек, чтобы они оказались в правильном порядке
    stack<int> reorderedStack;
    while (!originalStack.empty()) {
        reorderedStack.push(originalStack.top());
        originalStack.pop();
    }

    return reorderedStack; // Возвращаем результирующий стек
}

int main() {
    stack<int> originalStack;
    int n;
    cout << "Введите количество элементов в стеке: ";
    cin >> n;

    cout << "Введите элементы стека: ";
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        originalStack.push(num); // Добавляем элементы в исходный стек
    }

    // Переупорядочиваем стек вызовом функции reorderStack
    stack<int> reorderedStack = reorderStack(originalStack);

    // Выводим содержимое переупорядоченного стека
    cout << "Переупорядоченный стек: ";
    stack<int> tempStack; // Временный стек для переворота порядка вывода
    while (!reorderedStack.empty()) {
        tempStack.push(reorderedStack.top()); // Добавляем верхний элемент переупорядоченного стека во временный стек
        reorderedStack.pop(); // Удаляем его из переупорядоченного стека
    }
    while (!tempStack.empty()) {
        cout << tempStack.top() << " "; // Выводим верхний элемент временного стека
        tempStack.pop(); // Удаляем его из временного стека
    }
    cout << endl;

    return 0;
}
