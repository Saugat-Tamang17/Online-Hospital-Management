#include<iostream> // for input and output operations
#include<fstream> // for file handling and operations
#include<string> //for string manipulations
#include<vector> // for using dynamically sized arrays
using namespace std; 

class person {   //person class to store basic information ( is also the base class)
  protected:
  string name;
  int age;
  int gender;


  //constructor to initialize the person object and store the basic information ( default and parameterized)
  public:    
  person( string n=" ", int a=0, int g=0){
    age=a;
    name=n;
    gender=g;
    
  }


  /*virtual constructor to allow derived classes to override the display function
  ( polymorphism) */
    virtual void display() const {
        cout << "Name: " << name << "\nAge: " << age << "\nGender: " << gender <<endl;
    }
};


//patient class inherits from " person" class ( meaning its a derived class)
class patient : public person {  
  private: 
  int patient_ID;
  int room_number;
  string disease;


  // constructor to initialize the patient object and store the patient specific information ( default and parameterized) and it also calls the base constructor ( person )
  public:  
  patient(string n=" ", int a=0, int g=0, int p_id=0, int r_num=0, string d="") : person(n, a, g) {
      patient_ID = p_id;
      room_number = r_num;
      disease = d;
  }
   void display() const override {
        cout << "\n--- Patient Info ---\n";
        person::display();
        cout << "Patient ID: " << patient_ID << "\nDisease: " << disease << endl;
    }

    int getID() { // function to get the patient ID
         if (patient_ID == 0) {
            cout << "Patient ID is not set." << endl;

            // return -1 if patient ID is not set
            return -1;       
            
        }
         cout << "Patient ID: " << patient_ID << endl;
      return patient_ID;
     }

   
};


class Doctor : public person {
  private : 
  int doctor_ID;
  string specialization;
  vector <string> available_times;  //vector array to store available times of the doctor
  
  public: 
  Doctor(string n="", int a=0, int g=0, int d_id=0, string spec="") : person(n, a, g) {
    doctor_ID = d_id;
    specialization = spec;
    available_times = {"10:00", "11:00", "12:00", "14:00", "15:00", "16:00"};  
    // initializing available times
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

  
};


int main(){
vector <patient> patients_list; // vector array to store the list of patients
 vector<Doctor> doctors = {
        Doctor("Dr. Maharjan", 45, 1, 101, "Cardiology"),
        Doctor("Dr. Giri", 50, 1, 102, "Neurology"),
        Doctor("Dr. Koirala", 40, 0, 103, "Pediatrics"),
        Doctor("Dr. Rai", 42, 1, 104, "Orthopedics"),
        Doctor("Dr. Lama", 38, 0, 105, "Dermatology"),
        Doctor("Dr. Thapa", 48, 1, 106, "Cardiology"),
        Doctor("Dr. Sthapit", 44, 0, 107, "Neurology"),
        Doctor("Dr. Adhikari", 41, 1, 108, "Pediatrics"),
        Doctor("Dr. Gurung", 39, 0, 109, "Orthopedics"),
        Doctor("Dr. Khadka", 46, 1, 110, "Dermatology"),
        Doctor("Dr. Shrestha", 43, 0, 111, "Cardiology"),
        Doctor("Dr. Magar", 37, 1, 112, "Neurology"),
        Doctor("Dr. Pokharel", 49, 0, 113, "Pediatrics"),
        Doctor("Dr. Tamang", 35, 1, 114, "Orthopedics"),
        Doctor("Dr. Basnet", 52, 0, 115, "Dermatology")
    };


    int choice ;
    cout << " WELCOME TO ONLINE HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "-----------------------------------------------------\n";
    do {
        cout << "1. Add Patient\n2. Create Appointment\n3. Generate Bill\n4. Show Reports\n5. List Doctors\n6.View Appointments\n   7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
    //loops until the user decides to exit with choice 7


    switch (choice) {
        case 1: { // Add Patient
            string name, disease;
            int age, gender, patient_ID, room_number;

            cout << "Enter patient details:\n";
            cout << "Name: ";
            cin >> name;
            cout << "Age: ";
            cin >> age;
            cout << "Gender (0-Male, 1-Female, 2-Others): ";
            cin >> gender;
            cout << "Patient ID: ";
            cin >> patient_ID;
            cout << "Room Number: ";
            cin >> room_number;
            cout << "Disease: ";
            cin >> disease;

            // Create a new patient object and add it to the patients list
            patients_list.push_back(patient(name, age, gender, patient_ID, room_number, disease));
            cout << "Patient added successfully!\n";
            break;
        }

          case 5: { // List Doctors
            cout << "\n--- List of Doctors ---\n";
        
            for (const auto& doctor : doctors) {
                doctor.display();
            }
            cout << "do you want to add more doctors? (1 for yes, 0 for no): ";
            int add_more;
            cin >> add_more;
            if (add_more == 1) {  
                string name, specialization;
                int age, gender, doctor_ID;

                cout << "Enter doctor details:\n";
                cout << "Name: ";
                cin >> name;
                cout << "Age: ";
                cin >> age;
                cout << "Gender (0-Male, 1-Female, 2-Others): ";
                cin >> gender;
                cout << "Doctor ID: ";
                cin >> doctor_ID;
                cout << "Specialization: ";
                cin >> specialization;

                // Create a new doctor object and add it to the doctors list
                doctors.push_back(Doctor(name, age, gender, doctor_ID, specialization));
                cout << "Doctor added successfully!\n";
            }
            break;
        }
        // Add other cases as needed
      }
    } while (choice != 7);
    cout << "Thank you for using the Online Hospital Management System!\n";
    
  }




