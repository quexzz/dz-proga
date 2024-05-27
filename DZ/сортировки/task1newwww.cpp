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

// Функция для преобразования строки с датой в структуру Date
Employee parseEmployee(const string& line) {
    Employee emp; // экземпляр структуры Employee
    stringstream ss(line); // строковый поток ss и передаем в него строку line
    ss >> emp.surname >> emp.position; // Извлекаем фамилию и должность из строки и записываем в структуру emp
    char dot;// Создаем переменную для символа точки
    ss >> emp.day >> dot >> emp.month >> dot >> emp.year >> emp.experience >> emp.salary; // Извлекаем день, месяц, год рождения, стаж работы и зарплату из строки и записываем в структуру emp
    return emp; // Возвращаем структуру emp
}
// Функция для сортировки сотрудников по году рождения с использованием сортировки подсчетом
void sortByYearOfBirth(vector<Employee>& employees) {
    const int MAX_YEAR = 2024; // Максимальный возможный год рождения
    const int MIN_YEAR = 1900; // Минимальный возможный год рождения

    vector<vector<Employee>> buckets(MAX_YEAR - MIN_YEAR + 1);

    for (const auto& emp : employees) {
        buckets[emp.year - MIN_YEAR].push_back(emp);
    }

    employees.clear(); //Очищаем вектор сотрудников перед заполнением отсортированными данными
    for (auto& bucket : buckets) {
        for (auto& emp : bucket) {
            employees.push_back(emp);
        }
    }
}
// Функция для записи данных сотрудников в файл
void writeToFile(const vector<Employee>& employees, const string& filename) {
    ofstream outFile(filename);// Определение функции writeToFile, которая принимает вектор сотрудников и имя файла для записи.
    if (!outFile) {
        cerr << "Не могу открыть файл: " << filename << endl;
        return;
    }
    // Проверка, удалось ли открыть файл. Если файл не удалось открыть, выводится сообщение об ошибке 
    for (const auto& emp : employees) {
        outFile << emp.surname << " " << emp.position << " "
            << emp.day << "." << emp.month << "." << emp.year << " "
            << emp.experience << " " << emp.salary << endl;
    }
    cout << "Шеф все находится в " << filename << endl;
}
int main() {
    std::setlocale(LC_ALL, "Russian");
    vector<Employee> employees;
    string inputFilename = "in.txt";
    string outputFilename = "output.txt";
    // Проверка, удалось ли открыть файл. Если файл не удалось открыть, выводится сообщение об ошибке  1
    ifstream inFile(inputFilename);
    if (!inFile) {
        cerr << "Не могу открыть файл: " << inputFilename << endl;
        return 1;
    }
    //Считывание данных о сотрудниках из входного файла построчно.
    string line;
    while (getline(inFile, line)) {
        employees.push_back(parseEmployee(line));
    }
    inFile.close();
    // Сортируем сотрудников по году рождения
    sortByYearOfBirth(employees);
    // Записываем отсортированные данные в новый файл
    writeToFile(employees, outputFilename);
    return 0;
}
