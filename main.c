#include <stdio.h>
#include <string.h>

// Define structures for Patient and Doctor
struct Patient {
    char name[50];
    int age;
    char gender[10];
};

struct Doctor {
    char name[50];
    char specialization[50];
};

// Function to add a patient to the system
void addPatient(struct Patient patients[], int *patientCount) {
    struct Patient newPatient;
    
    printf("Enter patient name: ");
    scanf("%s", newPatient.name);
    
    printf("Enter patient age: ");
    scanf("%d", &newPatient.age);
    
    printf("Enter patient gender: ");
    scanf("%s", newPatient.gender);
    
    patients[*patientCount] = newPatient;
    (*patientCount)++;
    
    printf("Patient added successfully!\n");
}

// Function to add a doctor to the system
void addDoctor(struct Doctor doctors[], int *doctorCount) {
    struct Doctor newDoctor;
    
    printf("Enter doctor name: ");
    scanf("%s", newDoctor.name);
    
    printf("Enter doctor specialization: ");
    scanf("%s", newDoctor.specialization);
    
    doctors[*doctorCount] = newDoctor;
    (*doctorCount)++;
    
    printf("Doctor added successfully!\n");
}

// Function to display all patients
void displayPatients(struct Patient patients[], int patientCount) {
    printf("Patients:\n");
    for (int i = 0; i < patientCount; i++) {
        printf("%s, Age: %d, Gender: %s\n", patients[i].name, patients[i].age, patients[i].gender);
    }
}

// Function to display all doctors
void displayDoctors(struct Doctor doctors[], int doctorCount) {
    printf("Doctors:\n");
    for (int i = 0; i < doctorCount; i++) {
        printf("%s, Specialization: %s\n", doctors[i].name, doctors[i].specialization);
    }
}

int main() {
    struct Patient patients[50];
    struct Doctor doctors[50];
    int patientCount = 0;
    int doctorCount = 0;

    int choice;

    do {
        printf("\nHospital Management System\n");
        printf("1. Add Patient\n");
        printf("2. Add Doctor\n");
        printf("3. Display Patients\n");
        printf("4. Display Doctors\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient(patients, &patientCount);
                break;
            case 2:
                addDoctor(doctors, &doctorCount);
                break;
            case 3:
                displayPatients(patients, patientCount);
                break;
            case 4:
                displayDoctors(doctors, doctorCount);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}