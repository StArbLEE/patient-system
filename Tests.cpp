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
