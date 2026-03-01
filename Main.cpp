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


