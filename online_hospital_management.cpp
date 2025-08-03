#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<cstdlib>
#include<ctime>   

using namespace std;



class person {
protected:
    string name;
    int age;
    int gender;

public:
    person(string n = " ", int a = 0, int g = 0) {
        age = a;
        name = n;
        gender = g;
    }

    virtual void display() const {
        cout << "Name: " << name << "\nAge: " << age << "\nGender: " << gender << endl;
    }

    string getName() const { 
      return name; 
    }
    int getAge() const { 
      return age; 
    }
    int getGender() const { 
      return gender; 
    }
};

class patient : public person {
private:
    int patient_ID;
    int room_number;
    string disease;

public:
    patient(string n = " ", int a = 0, int g = 0, int p_id = 0, int r_num = 0, string d = "") : person(n, a, g) {
        patient_ID = p_id;
        room_number = r_num;
        disease = d;
    }

    void display() const override {
        cout << "\n--- Patient Info ---\n";
        person::display();
        cout << "Patient ID: " << patient_ID << "\nDisease: " << disease << endl;
    }

    int getID() const {
       return patient_ID; 
      }
    string getDisease() const { 
      return disease; 
    }
};

class Doctor : public person {
private:
    int doctor_ID;
    string specialization;
    vector<string> available_times;

public:
    Doctor(string n = "", int a = 0, int g = 0, int d_id = 0, string spec = "") : person(n, a, g) {
        doctor_ID = d_id;
        specialization = spec;
        available_times = {"10:00", "11:00", "12:00", "14:00", "15:00", "16:00"};
    }

    void display() const override {
        cout << "\n--- Doctor Info ---\n";
        person::display();
        cout << "Doctor ID: " << doctor_ID << "\nSpecialization: " << specialization << endl;
        cout << "Available Times: ";
        for (const auto& time : available_times) {
            cout << time << " ";
        }
        cout << endl;
    }

    int getID() const {
         return doctor_ID;
         }
    string getSpecialization() const {
        
        return specialization;
     }
};

struct Appointment {
    int patient_ID;
    int doctor_ID;
    string time_slot;
    bool completed = false;
};

void savePatientToFile(const patient& p) {
    ofstream file("patients.txt", ios ::app);
    file << p.getID() << "," << p.getName() << "," << p.getDisease() << endl;
    file.close();
}

void saveAppointmentToFile(const Appointment& appt) {
    ofstream file("appointments.txt", ios::app);
    file << appt.patient_ID << "," << appt.doctor_ID << "," << appt.time_slot << "," << appt.completed << endl;
    file.close();
}

void saveReportsToFile(const vector<patient>& patients_list) {
    ofstream file("patient_reports.txt");
    for (const auto& p : patients_list) {
        file << "Patient ID: " << p.getID() << ", Name: " << p.getName()
             << ", Disease: " << p.getDisease() << endl;
    }
    file.close();
    cout << "Reports saved to 'patient_reports.txt'.\n";
}


void generateBill(const vector<patient>& patients_list) {
    int id;
    cout << "Enter patient ID for billing: ";
    cin >> id;

    for (const auto& p : patients_list) {
        if (p.getID() == id) {
            cout << "Generating bill...\n";
            int bill = 500 + (rand() % 500);  // random bill amount between 500 and 999 ( for any disease ) 
            cout << "Total Bill Amount: Rs. " << bill << endl;
            return;
        }
    }
    cout << "Patient not found.\n";
}

void showReports(const vector<patient>& patients_list) {
    cout << "\n--- Patient Reports ---\n";
    for (const auto& p : patients_list) p.display();
}

void showAppointments(const vector<Appointment>& appointments) {
    cout << "\n--- Appointments List ---\n";
    for (const auto& a : appointments) {
        cout << "Patient ID: " << a.patient_ID << ", Doctor ID: " << a.doctor_ID << ", Time: " << a.time_slot
             << ", Status: " << (a.completed ? "Completed" : "Pending") << endl;
    }
}

void markAppointmentComplete(vector<Appointment>& appointments, int doctorID) {
    for (auto& a : appointments) {
        if (a.doctor_ID == doctorID && !a.completed) {
            cout << "Appointment with Patient ID: " << a.patient_ID << " at " << a.time_slot << " [Pending]\n";
            cout << "Mark this appointment as completed? (1 = Yes, 0 = No): ";
            int mark;
            cin >> mark;
            if (mark == 1) {
                a.completed = true;
                cout << "Marked as completed.\n";
            }
        }
    }
}

void searchPatient(const vector<patient>& patients_list) {
    int id;
    cout << "Enter Patient ID to search: ";
    cin >> id;
    for (const auto& p : patients_list) {
        if (p.getID() == id) {
            p.display();
            return;
        }
    }
    cout << "Patient not found.\n";
}

void updatePatient(vector<patient>& patients_list) {
    int id;
    cout << "Enter Patient ID to update: ";
    cin >> id;
    for (auto& p : patients_list) {
        if (p.getID() == id) {
            string name, disease;
            int age, gender, room;
            cout << "New Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "New Age: ";
            cin >> age;
            cout << "New Gender (0/1/2): ";
            cin >> gender;
            cout << "New Room No: ";
            cin >> room;
            cout << "New Disease: ";
            cin >> disease;
            p = patient(name, age, gender, id, room, disease);
            cout << "Patient updated.\n";
            return;
        }
    }
    cout << "Patient not found.\n";
}

void deletePatient(vector<patient>& patients_list) {
    int id;
    cout << "Enter Patient ID to delete: ";
    cin >> id;
    for (auto it = patients_list.begin(); it != patients_list.end(); ++it) {
        if (it->getID() == id) {
            patients_list.erase(it);
            cout << "Patient deleted.\n";
            return;
        }
    }
    cout << "Patient not found.\n";
}



int main() {
    vector<patient> patients_list;
    vector<Doctor> doctors = {
        Doctor("Dr. Maharjan", 45, 1, 500, "Cardiology"),
        Doctor("Dr. Giri", 50, 1, 501, "Neurology"),
        Doctor("Dr. Tamang", 40, 0, 502, "Pediatrics"),
        Doctor("Dr. Rai", 42, 1, 503, "Orthopedics"),
    };
    vector<Appointment> appointments;

    // Map diseases to doctor specializations
    map<string, string> diagnosis_map = {
        {"heart", "Cardiology"},
        {"brain", "Neurology"},
        {"child", "Pediatrics"},
        {"bone", "Orthopedics"},
        {"skin", "Dermatology"}
    };

    srand(time(0));  // initialize random seed for billing

    

    cout << "Welcome to Hospital Management System\n";
    cout << "Select Role:\n 1. Admin\n 2. Doctor\n 3. Patient\nRole: ";
    int role;
    cin >> role;

    if (role == 1) { // Admin menu
        int choice;
        do {
            cout << "\n[ADMIN MENU]\n"
                 << "1. Add Patient\n"
                 << "2. Add Doctor\n"
                 << "3. Create Appointment\n"
                 << "4. Generate Bill\n"
                 << "5. Show Reports\n"
                 << "6. View Appointments\n"
                 << "7. Search Patient\n"
                 << "8. Update Patient\n"
                 << "9. Delete Patient\n"
                 << "10. Save Data to File\n"
                 << "0. Exit\n"
                 << "Choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    string name, disease;
                    int age, gender, patient_ID, room_number;
                    cout << "Enter patient's name: ";
                    cin.ignore(); 
                    getline(cin, name);
                    cout << "Enter patient's age: ";
                    cin >> age;
                    cout << "Enter patient's gender (0: male/1: female/2: other ): ";
                    cin >> gender;
                    cout << "Enter patient's ID: ";
                    cin >> patient_ID;
                    cout << "Enter patient's room number: ";
                    cin >> room_number;
                    cout << "Enter patient's disease: ";
                    cin >> disease;
                    patients_list.push_back(patient(name, age, gender, patient_ID, room_number, disease));
                    cout << "Patient added successfully!\n";
                    break;
                }
                case 2: {
                    string name, specialization;
                    int age, gender, doctor_ID;
                    cout << "Enter doctor's name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter doctor's age: ";
                    cin >> age;
                    cout << "Enter doctor's gender (0/1/2): ";
                    cin >> gender;
                    cout << "Enter doctor's ID: ";
                    cin >> doctor_ID;
                    cout << "Enter doctor's specialization: ";
                    cin >> specialization;
                    doctors.push_back(Doctor(name, age, gender, doctor_ID, specialization));
                    cout << "Doctor added successfully!\n";
                    break;
                }
                case 3: {
                    int patient_ID;
                    string disease;
                    cout << "Enter Patient ID: ";
                    cin >> patient_ID;
                    cout << "Enter Disease: ";
                    cin >> disease;
                    if (diagnosis_map.find(disease) == diagnosis_map.end()) {
                        cout << "Unknown disease.\n";
                        break;
                    }
                    string spec = diagnosis_map[disease];
                    vector<Doctor*> matched;
                    for (auto& d : doctors)
                        if (d.getSpecialization() == spec)
                            matched.push_back(&d);
                    if (matched.empty()) {
                        cout << "No available doctor.\n";
                        break;
                    }
                    for (const auto& d : matched)
                        d->display();
                    int doc_id;
                    string time;
                    cout << "Enter Doctor ID and Time: ";
                    cin >> doc_id >> time;
                    appointments.push_back({patient_ID, doc_id, time});
                    cout << "Appointment booked!\n";
                    break;
                }
                case 4: generateBill(patients_list); break;
                case 5: showReports(patients_list); break;
                case 6: showAppointments(appointments); break;
                case 7: searchPatient(patients_list); break;
                case 8: updatePatient(patients_list); break;
                case 9: deletePatient(patients_list); break;
                case 10: {
                    for (const auto& p : patients_list)
                        savePatientToFile(p);
                    for (const auto& a : appointments)
                        saveAppointmentToFile(a);
                    saveReportsToFile(patients_list);
                    cout << "All patient, appointment, and report data saved to file.\n";
                    break;
                }
            }
        } while (choice != 0);
    } else if (role == 2) { // Doctor menu
        int doc_id;
        cout << "Enter your Doctor ID: ";
        cin >> doc_id;
        int option;
        do {
            cout << "\n[DOCTOR MENU]\n"
                 << "1. View Appointments\n"
                 << "2. Mark Completed\n"
                 << "0. Exit\n"
                 << "Choice: ";
            cin >> option;
            if (option == 1)
                showAppointments(appointments);
            else if (option == 2)
                markAppointmentComplete(appointments, doc_id);
        } while (option != 0);
    } else if (role == 3) { // Patient menu (view own appointments)
        int pid;
        cout << "Enter your Patient ID: ";
        cin >> pid;
        cout << "\n--- Your Appointments ---\n";
        for (const auto& a : appointments)
            if (a.patient_ID == pid)
                cout << "Doctor ID: " << a.doctor_ID << ", Time: " << a.time_slot << ", Status: " << (a.completed ? "Completed" : "Pending") << endl;
    }

    return 0;
}
