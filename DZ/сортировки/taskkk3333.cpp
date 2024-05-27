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
    cout << "Шеф все находится в " << filename << endl; // Выводим сообщение об успешной записи данных
}
// Функция для сортировки сотрудников по дате рождения (год, месяц, день) с помощью сортировки перемешиванием
void cocktailSort(vector<Employee>& employees) {
    int n = employees.size(); // Получаем количество элементов вектора
    int left = 0; // Устанавливаем начальный левый индекс
    int right = n - 1; // Устанавливаем начальный правый индекс
    bool swapped = true; // Флаг для отслеживания совершения обмена
    while (swapped) { // Пока происходят обмены
        swapped = false; // Сбрасываем флаг обмена
        // Проход снизу вверх
        for (int i = left; i < right; ++i) {
            // Сравниваем текущий элемент с следующим
            if (employees[i].year > employees[i + 1].year ||
                (employees[i].year == employees[i + 1].year && employees[i].month > employees[i + 1].month) ||
                (employees[i].year == employees[i + 1].year && employees[i].month == employees[i + 1].month && employees[i].day > employees[i + 1].day)) {
                // Если текущий элемент больше следующего, меняем их местами
                swap(employees[i], employees[i + 1]);
                swapped = true; // Устанавливаем флаг обмена
            }
        }
        if (!swapped) // Если обменов не было, завершаем сортировку
            break;
        swapped = false; // Сбрасываем флаг обмена
        --right; // Уменьшаем правый индекс
        // Проход сверху вниз
        for (int i = right - 1; i >= left; --i) {
            // Сравниваем текущий элемент с предыдущим
            if (employees[i].year > employees[i + 1].year ||
                (employees[i].year == employees[i + 1].year && employees[i].month > employees[i + 1].month) ||
                (employees[i].year == employees[i + 1].year && employees[i].month == employees[i + 1].month && employees[i].day > employees[i + 1].day)) {
                // Если текущий элемент больше следующего, меняем их местами
                swap(employees[i], employees[i + 1]);
                swapped = true; // Устанавливаем флаг обмена
            }
        }
        ++left; // Увеличиваем левый индекс
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
    inFile.close(); // Закрываем входной файл
    // Сортируем сотрудников по дате рождения с помощью сортировки перемешиванием
    cocktailSort(employees);
    // Записываем отсортированные данные в выходной файл
    writeToFile(employees, outputFilename);
    return 0;
}
