#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Структура для хранения данных о сотруднике
struct Employee {
    string surname;
    string position;
    int day;
    int month;
    int year;
    int experience;
    int salary;
};
// Функция для преобразования строки с данными о сотруднике в структуру Employee
Employee parseEmployee(const string& line) {
    Employee emp; // экземпляр структуры Employee
    stringstream ss(line); // строковый поток ss и передаем в него строку line
    ss >> emp.surname >> emp.position; // Извлекаем фамилию и должность из строки и записываем в структуру emp
    char dot; // Создаем переменную для символа точки
    ss >> emp.day >> dot >> emp.month >> dot >> emp.year >> emp.experience >> emp.salary; // Извлекаем день, месяц, год рождения, стаж работы и зарплату из строки и записываем в структуру emp
    return emp; // Возвращаем структуру emp
}
// Функция для записи данных сотрудников в файл
void writeToFile(const vector<Employee>& employees, const string& filename) {
    ofstream outFile(filename); // Открываем файл для записи
    if (!outFile) { // Проверяем, удалось ли открыть файл
        cerr << "Не могу открыть файл: " << filename << endl; // Если не удалось, выводим сообщение об ошибке
        return;
    }
    // Записываем данные о сотрудниках в файл
    for (const auto& emp : employees) {
        outFile << emp.surname << " " << emp.position << " "
            << emp.day << "." << emp.month << "." << emp.year << " "
            << emp.experience << " " << emp.salary << endl;
    }
    cout << "Шеф все находится в  " << filename << endl; // Выводим сообщение об успешной записи данных
}
// Функция для сортировки сотрудников по фамилии, а затем по должности с помощью сортировки Шелла
void shellSort(vector<Employee>& employees) {
    int n = employees.size(); // Получаем количество элементов вектора
    for (int d = n / 2; d > 0; d /= 2) { // Выбираем шаг сортировки
        for (int i = d; i < n; ++i) { // Начинаем сортировку с i-го элемента
            Employee temp = employees[i]; // Запоминаем текущий элемент
            int j;
            for (j = i; j >= d && (employees[j - d].surname > temp.surname ||
                (employees[j - d].surname == temp.surname && employees[j - d].position > temp.position)); j -= d) {
                // Пока не достигнут начало массива и текущий элемент меньше, чем элемент на расстоянии d, сдвигаем элементы
                employees[j] = employees[j - d];
            }
            employees[j] = temp; // Вставляем сохраненный элемент на свое место
        }
    }
}
int main() {
    std::setlocale(LC_ALL, "Russian");
    vector<Employee> employees; // Создаем вектор для хранения данных о сотрудниках
    string inputFilename = "in.txt"; // Задаем имя входного файла
    string outputFilename = "output.txt"; // Задаем имя выходного файла
    ifstream inFile(inputFilename); // Открываем входной файл для чтения
    if (!inFile) { // Проверяем, удалось ли открыть файл
        cerr << "Не могу открыть файл: " << inputFilename << endl; // Если не удалось, выводим сообщение об ошибке
        return 1;
    }
    string line; // Создаем строку для считывания данных из файла
    while (getline(inFile, line)) { // Считываем данные о сотрудниках из файла построчно
        employees.push_back(parseEmployee(line)); // Преобразуем строку в структуру Employee и добавляем ее в вектор
    }
    inFile.close();
    // Сортируем сотрудников по фамилии, а затем по должности с помощью сортировки Шелла
    shellSort(employees);
    // Записываем отсортированные данные в выходной файл
    writeToFile(employees, outputFilename);
    return 0;
}
