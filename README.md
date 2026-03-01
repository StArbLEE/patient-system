Main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include "Menu.h" 
#include "Patient.h"
#include "Tests.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Ru");
    system("chcp 1251");
    system("cls");

    wcout << L"Здравствуйте!" << endl
        << L"ФИО: Саргсян Серёжа Арсенович" << endl
        << L"Группа: 4403" << endl
        << L"Вариант 8" << endl
        << L"Контрольная работа 1" << endl
        << L"Задание: Пациент: фамилия, имя, отчество, адрес, номер медицинской карты, диагноз." << endl
        << L"Создать массив объектов. Реализовать возможность получения:" << endl
        << L"\t– списка пациентов, имеющих данный диагноз," << endl
        << L"\t– списка пациентов, номер медицинской карты которых находится в" << endl
        << L"\tзаданном интервале." << endl << endl;

    const int Max_patients = 100;
    int choice = 0;
    int choice1 = 0;
    wstring filePath;
    vector<Patient> patients;
    int RunTests = 0;

    while (true) {
        wcout << L"Начальное меню:" << endl
            << L"0. Выход" << endl
            << L"1. Запустить тесты" << endl
            << L"Введите цифру : ";
        if (!GetIntInput(choice1) || choice1 > 1 || choice1 < 0) {
            wcout << L"Неверный ввод. Попробуйте снова." << endl << endl;
            continue;
        }

        else if (choice1 == 0) {
            return EXIT_SUCCESS;
        }
        else if (choice1 == 1) {
            break;
        }
    }

    while (true) {
        RunAllTests();
        wcout << L"Тесты завершены. Продолжить работу с программой? (0 - нет, 1 - да): ";
        if (!GetIntInput(RunTests) || RunTests > 1 || RunTests < 0) {
            wcout << L"Неверный ввод. Программа завершает работу." << endl;
            return EXIT_SUCCESS;
        }
        if (RunTests == ZERO) {
            return EXIT_SUCCESS;
        }
        while (true) {
            wcout << L"Введите путь к файлу с данными о пациентах: ";
            if (!GetStringInput(filePath)) {
                wcout << L"Неверный ввод. Программа завершает работу" << endl;
                return EXIT_SUCCESS;
            }
            if (LoadPatientsFromFile(filePath, patients)) {
                break;
            }
        }
        break;
    }

    while (true) {
        Showmenu();
        if (!GetIntInput(choice)) {
            wcout << L"Неверный ввод. Попробуйте снова." << endl;
            continue;
        }

        switch (choice) {
        case LIST_BY_DIAGNOSIS:
            wcout << L"Вы выбрали: Список пациентов с определённым диагнозом." << endl;
            wcout << L"Введите диагноз: ";
            ShowPatientsWithDiagnosis(Max_patients, patients);
            break;
        case LIST_BY_MEDICAL_CARD_RANGE:
            wcout << L"Вы выбрали: Список пациентов с номером медицинской карты в заданном интервале." << endl;
            ShowPatientWithMedicalCardNumber(Max_patients, patients);
            break;
        case LIST_ALL_PATIENTS:
            wcout << L"Вы выбрали: Вывести всех пациентов." << endl;
            ShowAllPatients(patients);
            break;
        case NEW_FILE:
            wcout << L"Вы выбрали: Выбрать новый файл." << endl;
            wcout << L"Введите путь к новому файлу с данными о пациентах: ";
            if (!GetStringInput(filePath)) {
                wcout << L"Неверный ввод. Попробуйте снова." << endl;
                break;
            }
            patients.clear();
            if (!LoadPatientsFromFile(filePath, patients)) {
                wcout << L"Не удалось загрузить данные из файла." << endl;
            }
            break;
        case EXIT:
            wcout << L"Выход из программы." << endl;
            return EXIT_SUCCESS;
        default:
            wcout << L"Я не знаю такого значения, повторите попытку." << endl;
            break;
        }
    }
}

Menu.cpp
#include <iostream>
#include <string>
#include <vector>
#include "Patient.h"
#include "Menu.h"
using namespace std;

void Showmenu() {
    wcout << L"Варианты выбора:" << endl
        << L"\t1. Список пациентов с определённым диагнозом." << endl
        << L"\t2. Список пациентов с номером медицинской карты в заданном интервале." << endl
        << L"\t3. Вывести всех пациентов." << endl
        << L"\t4. Выбрать новый файл. " << endl
        << L"\t0. Выход." << endl;
    wcout << L"Выберите номер: ";
}

bool GetIntInput(int& value) {
    wcin >> value;
    if (wcin.fail()) {
        wcin.clear();
        wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
        return false;
    }
    wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
    return true;
}
bool GetStringInput(wstring& value) {
    wcin >> value;
    if (wcin.fail()) {
        wcin.clear();
        wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
        return false;
    }
    wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
    return true;
}
void ShowAllPatients(vector <Patient>& patients) {
    for (int i = 0; i < patients.size(); i++) {
        patients[i].ShowPatient();
    }
}
void ShowPatientsWithDiagnosis(const int max_patients, vector <Patient> patients) {
    wstring diagnosis;
    if (!GetStringInput(diagnosis)) {
        wcout << L"Неверный ввод. Попробуйте снова." << endl;
        return;
    }
    vector <Patient> PatientsWithDiagnosis(max_patients);
    int diagCount = GetPatientsByDiagnosis(patients, trim(diagnosis), PatientsWithDiagnosis, max_patients);
    if (diagCount > max_patients) {
        diagCount = max_patients;
    }
    if (diagCount == 0) {
        wcout << L"Подходящих пациентов не найдено" << endl << diagnosis << endl;
    }
    else {
        wcout << L"Пациенты в " << diagnosis << L":" << endl;
        for (int i = 0; i < diagCount; ++i) {
            PatientsWithDiagnosis[i].ShowPatient();
        }
        wcout << L"Хотите сохранить данные в файл? (y/n): ";
        wstring saveChoice;
        wcin >> saveChoice;
        if (saveChoice == L"y" || saveChoice == L"Y" || saveChoice == L"yes" || saveChoice == L"Yes") {
            wcout << L"Введите путь и название файла для сохранения данных (без расширения .txt): ";
            wstring saveFilePath;
            if (!GetStringInput(saveFilePath)) {
                wcout << L"Неверный ввод. Данные не будут сохранены." << endl;
            }
            else {
                SavePatientsToFile(saveFilePath, PatientsWithDiagnosis, diagCount);
            }
        }
    }
}
void ShowPatientWithMedicalCardNumber(const int Max_patients, vector <Patient> patients) {
    int StartRange = 0;
    int FinishRange = 0;
    wcout << L"Введите диапазон" << endl;
    wcout << L"Начало: " << endl;
    if (!GetIntInput(StartRange) || StartRange < 0) {
        wcout << L"Неверный ввод. Попробуйте снова." << endl;
        return;
    }
    wcout << L"Конец: " << endl;
    if (!GetIntInput(FinishRange) || FinishRange < 0) {
        wcout << L"Неверный ввод. Попробуйте снова." << endl;
        return;
    }
    vector <Patient> medCardNumPatients(Max_patients);
    int medCardNumCount = GetPatientsByMedicalCardNumber(patients, StartRange, FinishRange, medCardNumPatients, Max_patients);
    if (medCardNumCount > Max_patients) {
        medCardNumCount = Max_patients;
    }
    if (medCardNumCount == 0) {
        wcout << L"Подходящих пациентов не найдено" << endl;
    }
    else {
        wcout << L"Пациенты в диапазоне от " << StartRange << L" до " << FinishRange << L":" << endl;
        for (int i = 0; i < medCardNumCount; ++i) {
            medCardNumPatients[i].ShowPatient();
        }
        wcout << L"Хотите сохранить данные в файл? (y/n): ";
        wstring saveChoice;
        wcin >> saveChoice;
        if (saveChoice == L"y" || saveChoice == L"Y" || saveChoice == L"yes" || saveChoice == L"Yes") {
            wcout << L"Введите путь и название файла для сохранения данных (без расширения .txt): ";
            wstring saveFilePath;
            if (!GetStringInput(saveFilePath)) {
                wcout << L"Неверный ввод. Данные не будут сохранены." << endl;
            }
            else {
                SavePatientsToFile(saveFilePath, medCardNumPatients, medCardNumCount);
            }
        }
    }
}

Menu.h
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Patient.h"
using namespace std;

enum MenuOption {
    EXIT = 0,
    LIST_BY_DIAGNOSIS = 1,
    LIST_BY_MEDICAL_CARD_RANGE = 2,
    LIST_ALL_PATIENTS = 3,
    NEW_FILE = 4,
    FIRST = 1,
    ZERO = 0
};
void Showmenu();

bool GetIntInput(int &value);
bool GetStringInput(wstring& value);

void ShowAllPatients(vector <Patient>& patients);
void ShowPatientsWithDiagnosis(const int Max_patients, vector <Patient> patients);
void ShowPatientWithMedicalCardNumber(const int Max_patients, vector <Patient> patients);

Patient.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <codecvt>
#include <sstream>
#include "Menu.h"
#include "Patient.h"
using namespace std;

wstring Patient::GetLastName() {
    return lastName;
}
void Patient::SetLastName(const wstring& lastName) {
    this->lastName = lastName;
}
wstring Patient::GetFirstName() {
    return firstName;
}
void Patient::SetFirstName(const wstring& firstName) {
    this->firstName = firstName;
}
wstring Patient::GetMiddleName() {
    return middleName;
}
void Patient::SetMiddleName(const wstring& middleName) {
    this->middleName = middleName;
}
wstring Patient::GetAddress() {
    return address;
}
void Patient::SetAddress(const wstring& address) {
    this->address = address;
}
int Patient::GetMedicalCardNumber() {
    return medicalCardNumber;
}
void Patient::SetMedicalCardNumber(const int& medicalCardNumber) {
    this->medicalCardNumber = medicalCardNumber;
}
wstring Patient::GetDiagnosis() {
    return diagnosis;
}
void Patient::SetDiagnosis(const wstring& diagnosis) {
    this->diagnosis = diagnosis;
}
void Patient::ShowPatient(){
    wcout << L"Фамилия: " << lastName << endl
        << L"Имя: " << firstName << endl
        << L"Отчество: " << middleName << endl
        << L"Адрес: " << address << endl
        << L"Диагноз: " << diagnosis << endl
        << L"Номер медицинской карты: " << medicalCardNumber << endl << endl;
}

wstring trim(const wstring& str) {
    size_t first = str.find_first_not_of(L' ');
    if (first == wstring::npos) {
        return L"";
    }
    size_t last = str.find_last_not_of(L' ');
    return str.substr(first, last - first + 1);
}

bool LoadPatientsFromFile(const wstring& filePath, vector<Patient>& patients) {
    wifstream file(filePath);

    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!file.is_open()) {
        wcout << L"Не удалось открыть файл: " << filePath << endl;
        return false;
    }

    wstring line;
    while (getline(file, line)) {
        wstringstream iss(line);
        wstring lastname, firstname, middlename, address, diagnosis, medicalCardNumberStr;
        if (!getline(iss, lastname, L',') ||
            !getline(iss, firstname, L',') ||
            !getline(iss, middlename, L',') ||
            !getline(iss, address, L',') ||
            !getline(iss, diagnosis, L',') ||
            !getline(iss, medicalCardNumberStr, L'\n')) {
            wcout << L"Ошибка формата строки: " << line << endl;
            continue;
        }

        int medicalCardNumber = stoi(medicalCardNumberStr);

        Patient patient;
        patient.SetLastName(trim(lastname));
        patient.SetFirstName(trim(firstname));
        patient.SetMiddleName(trim(middlename));
        patient.SetAddress(trim(address));
        patient.SetDiagnosis(trim(diagnosis));
        patient.SetMedicalCardNumber(medicalCardNumber);

        patients.push_back(patient);
    }
    file.close();
    return true;
}

int GetPatientsByDiagnosis(vector <Patient> patients, const wstring& diagnosis, vector <Patient>& result, const int Max_results) {
    int count = 0;
    for (int i = 0; i < patients.size(); ++i) {
        if (patients[i].GetDiagnosis() == diagnosis) {
            if (count < Max_results) {  
                result[count++] = patients[i];
            }
            else {
                wcout << L"Предупреждение: превышен максимальный размер массива результатов" << endl;
                return count;
            }
        }
    }
    return count;
}

int GetPatientsByMedicalCardNumber(vector <Patient> patients, const int& StartRange, const int& FinishRange, vector <Patient>& result, const int maxResults) {
    int count = 0;
    for (int i = 0; i < patients.size(); ++i) {
        if (patients[i].GetMedicalCardNumber() >= StartRange && patients[i].GetMedicalCardNumber() <= FinishRange) {
            if (count < maxResults) {  
                result[count++] = patients[i];
            }
            else {
                wcout << L"Предупреждение: превышен максимальный размер массива результатов" << endl;
                return count;
            }
        }
    }
    return count;
}

void SavePatientsToFile(wstring filePath, vector <Patient> patients, int PatientCount) {
    wstring fullFilePath = filePath + L".txt";
    while (true) {
        if (IsFileExist(fullFilePath)) {
            wcout << L"Файл " << fullFilePath << L" уже существует. Перезаписать? (y/n): ";
            wstring choice;
            wcin >> choice;
            if (choice == L"y" || choice == L"Y" || choice == L"yes" || choice == L"Yes") {
                break;
            }
            else {
                wcout << L"Введите новый путь для сохранения файла: ";
                if (!GetStringInput(fullFilePath)) {
                    wcout << L"Неверный ввод. Попробуйте снова." << endl;
                }
                fullFilePath += L".txt";
            }
        }
        else {
            break;
        }
    }
    wofstream file(fullFilePath);
    file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!file.is_open()) {
        while (true) {
            wcout << L"Не удалось открыть файл для записи: " << fullFilePath << endl;
            GetStringInput(fullFilePath);
        }
    }
    for (int i = 0; i < PatientCount; ++i) {
        file << trim(patients[i].GetLastName()) << L", "
            << trim(patients[i].GetFirstName()) << L", "
            << trim(patients[i].GetMiddleName()) << L", "
            << trim(patients[i].GetAddress()) << L", "
            << trim(patients[i].GetDiagnosis()) << L", "
            << patients[i].GetMedicalCardNumber()<< L"";
        file << endl;
    }
    wcout << L"Данные успешно сохранены в файл: " << fullFilePath << endl;
    file.close();
}

bool IsFileExist(const wstring& filePath) {
    ifstream file(filePath);
    return file.good();
}
Patient.h
#pragma once
#include <vector>
#include <string>

using namespace std;


class Patient {
private:
    wstring lastName;
    wstring firstName;
    wstring middleName;
    wstring address;
    int medicalCardNumber = 0;
    wstring diagnosis;

public:
    wstring GetLastName(); 
    wstring GetFirstName();
    wstring GetMiddleName();
    wstring GetAddress();
    int GetMedicalCardNumber();
    wstring GetDiagnosis();
    
    void SetLastName(const wstring& lastName);
    void SetFirstName(const wstring& firstName);
    void SetMiddleName(const wstring& middleName);
    void SetAddress(const wstring& address);
    void SetMedicalCardNumber(const int& medicalCardNumber);
    void SetDiagnosis(const wstring& diagnosis);

    void ShowPatient();
};
bool LoadPatientsFromFile(const wstring& filePath, vector <Patient>& patients);
wstring trim(const wstring& str);
int GetPatientsByDiagnosis(vector <Patient> patients,const wstring& diagnosis, vector <Patient>& result, const int Max_results);
int GetPatientsByMedicalCardNumber(vector <Patient> patients, const int& StartRange, const int& FinishRange, vector <Patient>& result, const int maxResults);

void SavePatientsToFile(wstring filePath, vector <Patient> patients, int PatientCount);
bool IsFileExist(const wstring& filePath);


Tests.cpp
#include <iostream>
#include <vector>
#include <string>
#include "Patient.h"
#include "Menu.h"
#include "Tests.h"

#define TESTS_PATH L"Patient/testpatients.txt"
using namespace std;

bool EXPECT_EQ(int expected, int actual) {
    if (expected == actual) {
        return true;
    }
    else {
        return false;
    }
}

bool TESTGetPatientsByAstma() {
    vector <Patient> patients;
    vector <Patient> result(10);
    LoadPatientsFromFile(TESTS_PATH, patients);
    int count = GetPatientsByDiagnosis(patients, L"Астма", result, 10);
    bool testResult = EXPECT_EQ(1, count);
    if (!testResult) {
        wcout << L"\nВ GetPatientsByAstma:\n" << L"Ожидалось: 1, фактически: " << count << endl;
    }
    return testResult;
}

bool TESTGetPatientsByRak() {
    vector <Patient> patients;
    vector <Patient> result(10);
    LoadPatientsFromFile(TESTS_PATH, patients);
    int count = GetPatientsByDiagnosis(patients, L"Рак", result, 10);
    bool testResult = EXPECT_EQ(1, count);
    if (!testResult) {
        wcout << L"\nВ GetPatientsByRak:\n" << L"Ожидалось: 1, фактически: " << count << endl;
    }
    return testResult;
}

bool TESTGetPatientsByArtrit() {
    vector <Patient> patients;
    vector <Patient> result(10);
    LoadPatientsFromFile(TESTS_PATH, patients);
    int count = GetPatientsByDiagnosis(patients, L"Артрит", result, 10);
    bool testResult = EXPECT_EQ(1, count);
    if (!testResult) {
        wcout << L"\nВ GetPatientsByArtrit:\n" << L"Ожидалось: 1, фактически: " << count << endl;
    }
    return testResult;
}

bool TESTGetPatientsByMedCard100000_150000() {
    vector <Patient> patients;
    vector <Patient> result(10);
    LoadPatientsFromFile(TESTS_PATH, patients);
    int count = GetPatientsByMedicalCardNumber(patients, 100000, 150000, result, 10);
    bool testResult = EXPECT_EQ(2, count);
    if (!testResult) {
        wcout << L"\nВ GetPatientsByMedCard100000_150000:\n" << L"Ожидалось: 2, фактически: " << count << endl;
    }
    return testResult;
}
bool TESTGetPatientsByMedCard200000_400000() {
    vector <Patient> patients;
    vector <Patient> result(10);
    LoadPatientsFromFile(TESTS_PATH, patients);
    int count = GetPatientsByMedicalCardNumber(patients, 200000, 400000, result, 10);
    bool testResult = EXPECT_EQ(2, count);
    if (!testResult) {
        wcout << L"\nВ GetPatientsByMedCard200000_400000:\n" << L"Ожидалось: 2, фактически: " << count << endl;
    }
    return testResult;
}
bool RunAllTests() {
    bool result1 = TESTGetPatientsByAstma();
    bool result2 = TESTGetPatientsByRak();
    bool result3 = TESTGetPatientsByArtrit();
    bool result4 = TESTGetPatientsByMedCard100000_150000();
    bool result5 = TESTGetPatientsByMedCard200000_400000();

    if (result1 && result2 && result3 && result4 && result5) {
        wcout << L"Тестирование прошло успешно" << endl;
        return true;
    }
    else {
        wcout << L"\nНе все тесты пройдены успешно\n\n" << endl;
        return false;
    }
}
Tests.h
#pragma once
bool TESTGetPatientsByAstma();
bool TESTGetPatientsByRak();
bool TESTGetPatientsByArtrit();
bool TESTGetPatientsByMedCard100000_150000();
bool TESTGetPatientsByMedCard200000_400000();
bool RunAllTests();
bool EXPECT_EQ(int expected, int actual);
