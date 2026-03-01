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
