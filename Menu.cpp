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
