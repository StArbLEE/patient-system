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
