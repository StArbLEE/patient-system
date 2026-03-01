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
