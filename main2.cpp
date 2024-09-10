#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Doctor {
    string name;
    string specialization;
    double consultationFee;
    bool isAvailable;

public:
    Doctor(string name = "", string specialization = "", double fee = 0.0, bool availability = true)
        : name(name), specialization(specialization), consultationFee(fee), isAvailable(availability) {}

    // Function to display doctor's details
    void displayDoctorInfo() {
        cout << "Name: " << name << "\nSpecialization: " << specialization
             << "\nConsultation Fee: " << consultationFee 
             << "\nAvailable: " << (isAvailable ? "Yes" : "No") << endl;
    }

    // Function to write doctor info to a file
    void saveToFile(ofstream &outFile) {
        outFile << name << "\n" << specialization << "\n" 
                << consultationFee << "\n" << isAvailable << endl;
    }

    // Function to read doctor info from a file
    void loadFromFile(ifstream &inFile) {
        inFile >> ws; // To ignore any leading whitespace
        getline(inFile, name);
        getline(inFile, specialization);
        inFile >> consultationFee;
        inFile >> isAvailable;
    }

    string getSpecialization() { return specialization; }
    bool isDoctorAvailable() { return isAvailable; }
};

class Hospital {
    string name;
    vector<string> facilities;
    string location;

public:
    Hospital(string name = "", vector<string> facilities = {}, string location = "")
        : name(name), facilities(facilities), location(location) {}

    // Function to display hospital's details
    void displayHospitalInfo() {
        cout << "Hospital: " << name << "\nLocation: " << location << "\nFacilities: ";
        for (const auto& facility : facilities) {
            cout << facility << " ";
        }
        cout << endl;
    }

    // Function to save hospital info to a file
    void saveToFile(ofstream &outFile) {
        outFile << name << "\n" << location << "\n";
        outFile << facilities.size() << endl;
        for (const auto& facility : facilities) {
            outFile << facility << endl;
        }
    }

    // Function to load hospital info from a file
    void loadFromFile(ifstream &inFile) {
        inFile >> ws;
        getline(inFile, name);
        getline(inFile, location);
        int facilityCount;
        inFile >> facilityCount;
        facilities.resize(facilityCount);
        inFile >> ws;
        for (int i = 0; i < facilityCount; ++i) {
            getline(inFile, facilities[i]);
        }
    }
};

void addDoctor(vector<Doctor>& doctors) {
    string name, specialization;
    double fee;
    bool available;

    cout << "Enter doctor's name: ";
    cin >> ws;
    getline(cin, name);
    cout << "Enter specialization: ";
    getline(cin, specialization);
    cout << "Enter consultation fee: ";
    cin >> fee;
    cout << "Is the doctor available? (1 for Yes, 0 for No): ";
    cin >> available;

    doctors.push_back(Doctor(name, specialization, fee, available));

    ofstream outFile("doctors.txt", ios::app);
    doctors.back().saveToFile(outFile);
    outFile.close();

    cout << "Doctor added successfully!" << endl;
}

void addHospital(vector<Hospital>& hospitals) {
    string name, location;
    int facilityCount;
    vector<string> facilities;

    cout << "Enter hospital name: ";
    cin >> ws;
    getline(cin, name);
    cout << "Enter location: ";
    getline(cin, location);
    cout << "Enter number of facilities: ";
    cin >> facilityCount;

    facilities.resize(facilityCount);
    cout << "Enter facilities: " << endl;
    for (int i = 0; i < facilityCount; ++i) {
        cin >> ws;
        getline(cin, facilities[i]);
    }

    hospitals.push_back(Hospital(name, facilities, location));

    ofstream outFile("hospitals.txt", ios::app);
    hospitals.back().saveToFile(outFile);
    outFile.close();

    cout << "Hospital added successfully!" << endl;
}

void loadDoctors(vector<Doctor>& doctors) {
    ifstream inFile("doctors.txt");
    if (!inFile) {
        cout << "No doctor records found." << endl;
        return;
    }

    while (!inFile.eof()) {
        Doctor doc;
        doc.loadFromFile(inFile);
        if (inFile) { // To avoid loading empty records at the end
            doctors.push_back(doc);
        }
    }
    inFile.close();
}

void loadHospitals(vector<Hospital>& hospitals) {
    ifstream inFile("hospitals.txt");
    if (!inFile) {
        cout << "No hospital records found." << endl;
        return;
    }

    while (!inFile.eof()) {
        Hospital hosp;
        hosp.loadFromFile(inFile);
        if (inFile) { // To avoid loading empty records at the end
            hospitals.push_back(hosp);
        }
    }
    inFile.close();
}

void displayMainMenu(vector<Doctor>& doctors, vector<Hospital>& hospitals) {
    int choice;
    while (true) {
        cout << "\n--- Healthcare Consulting System ---\n";
        cout << "1. View Doctors\n";
        cout << "2. View Hospitals\n";
        cout << "3. Add Doctor\n";
        cout << "4. Add Hospital\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                for (auto& doc : doctors) doc.displayDoctorInfo();
                break;
            case 2:
                for (auto& hosp : hospitals) hosp.displayHospitalInfo();
                break;
            case 3:
                addDoctor(doctors);
                break;
            case 4:
                addHospital(hospitals);
                break;
            case 5:
                cout << "Exiting system..." << endl;
                return;
            default:
                cout << "Invalid choice, try again." << endl;
        }
    }
}

int main() {
    vector<Doctor> doctors;
    vector<Hospital> hospitals;

    // Load doctors and hospitals from files
    loadDoctors(doctors);
    loadHospitals(hospitals);

    // Start the main menu
    displayMainMenu(doctors, hospitals);

    return 0;
}
