#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_DOCTORS 100

struct Doctor {
    char name[50];
    char practiceLocation[100];
    char treatedDisease[50];
    char phone[15];
    char appointments[50];
};
struct Doctor doctors[100];
int doctorCount = 0;
// Function to display the welcome message without color formatting
void displayDoctors();
void addDoctor();
void deleteDoctor();
void searchDoctor();
void sortDoctors();
void quickAppointmentList();
void saveDataToFile();
void loadDataFromFile();

//doctors functions :
void displayDoctors() {
    printf("\nList of Doctors:\n");
    for (int i = 0; i < doctorCount; ++i) {
        printf("%d. %s - %s - %s\n", i + 1, doctors[i].name, doctors[i].practiceLocation, doctors[i].treatedDisease);
    }
}

void addDoctor() {
    if (doctorCount < MAX_DOCTORS) {
        printf("\nEnter Doctor's Name: ");
        scanf("%s", doctors[doctorCount].name);

        printf("Enter Practice Location (St City) : ");
        scanf("%s", doctors[doctorCount].practiceLocation);

        printf("Enter Disease Treated by the Doctor: ");
        scanf("%s", doctors[doctorCount].treatedDisease);

        printf("Enter Doctor's Phone Number: ");
        scanf("%s", doctors[doctorCount].phone);

        printf("Enter Appointments (DD MM YY HH MM) : ");
        scanf("%s", doctors[doctorCount].appointments);

        printf("Doctor added successfully.\n");

        doctorCount++;
        saveDataToFile(); // Save data to file after adding a doctor
    } else {
        printf("Cannot add more doctors. Database full.\n");
    }
}

void deleteDoctor() {
    if (doctorCount > 0) {
        int index;
        printf("\nEnter the index of the doctor to delete (1-%d): ", doctorCount);
        scanf("%d", &index);

        if (index >= 1 && index <= doctorCount) {
            for (int i = index - 1; i < doctorCount - 1; ++i) {
                doctors[i] = doctors[i + 1];
            }
            doctorCount--;

            printf("Doctor deleted successfully.\n");
            saveDataToFile(); // Save data to file after deleting a doctor
        } else {
            printf("Invalid index. Deletion failed.\n");
        }
    } else {
        printf("No doctors to delete. Database empty.\n");
    }
}

void searchDoctor() {
    if (doctorCount > 0) {
        char searchDisease[50];
        int found = 0;

        printf("\nEnter Disease to search for: ");
        scanf("%s", searchDisease);

        for (int i = 0; i < doctorCount; ++i) {
            if (strcmp(doctors[i].treatedDisease, searchDisease) == 0) {
                printf("Doctor found: %s - %s - %s\n", doctors[i].name, doctors[i].practiceLocation, doctors[i].treatedDisease);
                found = 1;
            }
        }

        if (!found) {
            printf("No doctors found treating %s.\n", searchDisease);
        }
    } else {
        printf("No doctors to search. Database empty.\n");
    }
}

void sortDoctors() {
    if (doctorCount > 1) {
        // Simple bubble sort based on treatedDisease
        for (int i = 0; i < doctorCount - 1; ++i) {
            for (int j = 0; j < doctorCount - i - 1; ++j) {
                if (strcmp(doctors[j].treatedDisease, doctors[j + 1].treatedDisease) > 0) {
                    // Swap
                    struct Doctor temp = doctors[j];
                    doctors[j] = doctors[j + 1];
                    doctors[j + 1] = temp;
                }
            }
        }

        printf("Doctors sorted by Disease.\n");
        saveDataToFile(); // Save data to file after sorting doctors
    } else {
        printf("Not enough doctors to sort. Minimum 2 required.\n");
    }
}

void quickAppointmentList() {
    if (doctorCount > 0) {
        printf("\nQuick Appointment List:\n");
        for (int i = 0; i < doctorCount; ++i) {
            printf("%d. %s - Appointments: %s\n", i + 1, doctors[i].name, doctors[i].appointments);
        }
    } else {
        printf("No doctors for quick appointment list. Database empty.\n");
    }
}

void saveDataToFile() {
    FILE *file = fopen("doctors.txt", "w");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < doctorCount; ++i) {
        fprintf(file, "%s,%s,%s,%s,%s\n", doctors[i].name, doctors[i].practiceLocation, doctors[i].treatedDisease, doctors[i].phone, doctors[i].appointments);
    }

    fclose(file);
}

void loadDataFromFile() {
    FILE *file = fopen("doctors.txt", "r");

    if (file == NULL) {
        printf("No previous data found.\n");
        return;
    }

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", doctors[doctorCount].name, doctors[doctorCount].practiceLocation, doctors[doctorCount].treatedDisease, doctors[doctorCount].phone, doctors[doctorCount].appointments) != EOF) {
        doctorCount++;
        if (doctorCount >= MAX_DOCTORS) {
            printf("Maximum number of doctors reached. Loading stopped.\n");
            break;
        }
    }

    fclose(file);
    printf("Data loaded successfully.\n");
}

struct Patient {
    char name[50];
    int age;
    char gender[10];
};

void addPatient(struct Patient patients[], int *patientCount) {
    struct Patient newPatient;
    printf("Enter patient name: ");
    scanf("%s", newPatient.name);
    printf("Enter patient age: ");
    scanf("%d", &newPatient.age);
    printf("Enter patient gender: ");
    scanf("%s", newPatient.gender);
    FILE *file = fopen("patients.txt", "a");
    if (file == NULL) {
        printf("Unable to open the file\n");
        return;
    }
    fprintf(file, "%s,%d,%s\n", newPatient.name, newPatient.age, newPatient.gender);
    fclose(file);
    printf("\nPatient added successfully!\n");
}

void displayPatients() {
    FILE *file;
    file = fopen("patients.txt", "r");

    if (file == NULL) {
        printf("\nCould not open file.\n");
        return;
    }

    printf("\nPatients:\n");
    char line[100];
    char name[50], gender[10];
    int age;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%49[^,],%d,%9[^\n]", name, &age, gender) == 3) {
            printf("\n%s, Age: %d, Gender: %s\n", name, age, gender);
        } else {
            printf("\nInvalid line format: %s", line);
        }
    }

    fclose(file);
}

void prescribeMedicine() {
    char patientName[50];
    char medicine[50];

    printf("\nEnter patient name to prescribe medicine: ");
    scanf("%s", patientName);

    printf("Enter prescribed medicine: ");
    scanf("%s", medicine);

    FILE *file;
    file = fopen("patients.txt", "r");

    if (file == NULL) {
        printf("\nCould not open file.\n");
        return;
    }

    char newLine[256];
    while (fgets(newLine, sizeof(newLine), file)) {
        struct Patient patient;
        sscanf(newLine, "%49[^,],%d,%9[^\1n]\n", patient.name, &patient.age, patient.gender);

        if (strcmp(patient.name, patientName) == 0) {
            snprintf(newLine, sizeof(newLine), "%s, %d, %s\n", patient.name, patient.age, medicine);
            break;
        }
    }

    fclose(file);

    file = fopen("PrescribedMedicine.txt", "a");
    if (file == NULL) {
        printf("\nCould not open file.\n");
        return;
    }

    fputs(newLine, file);
    fclose(file);
}

void prescribeTest() {
    char patientName[50];
    char test[50];

    printf("\nEnter patient name to prescribe test: ");
    scanf("%s", patientName);

    printf("Enter prescribed medicine: ");
    scanf("%s", test);

    FILE *file;
    file = fopen("patients.txt", "r");

    if (file == NULL) {
        printf("\nCould not open file.\n");
        return;
    }

    char newLine[256];
    while (fgets(newLine, sizeof(newLine), file)) {
        struct Patient patient;
        sscanf(newLine, "%49[^,],%d,%9[^\1n]\n", patient.name, &patient.age, patient.gender);

        if (strcmp(patient.name, patientName) == 0) {
            snprintf(newLine, sizeof(newLine), "%s, %d, %s\n", patient.name, patient.age, test);
            break;
        }
    }

    fclose(file);

    file = fopen("Prescribedtest.txt", "a");
    if (file == NULL) {
        printf("\nCould not open file.\n");
        return;
    }

    fputs(newLine, file);
    fclose(file);
}



void viewPrescriptions() {
    FILE *file;
    file = fopen("PrescribedMedicine.txt", "r");
    if (file == NULL) {
        printf("\nCould not open file.\n");
        return;
    }
    printf("\nPrescriptions\n");
    char line[100], name[50], gender[10], prescription[50];
    int age;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (sscanf(line, "%49[^,],%d,%9[^\n],%49[^,]", name, &age, gender, prescription) == 4) {
            printf("\n%s, Age: %d, Gender: %s\n", name, age, gender);
            printf("Prescription: %s\n", prescription);
        } else {
            printf("\nInvalid line format: %s", line);
        }
    }
}


// Function to display the welcome message without color formatting
void displayWelcomeMessage() {
	 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Change text color to red
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	
    printf("\n");
    printf("   WELCOME TO SWIFT HEALTH SYSTEM\n\n");
      SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// Function to display the SHS logo using hashtags
void displaySHSLogo() {
	 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Change text color to red
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    
    printf("                                ###################\n");
    printf("                                #                 #\n");
    printf("                                #       SHS       #\n");
    printf("                                #                 #\n");
    printf("                                ###################\n\n");
     SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// Structure for user information
typedef struct {
    char name[50];
    char email[50];
    char phone[15];
    int age;
    char bloodGroup[5];
    char userId[10];  // Limited to 4 digits
    char password[5];  // Limited to 4 digits
} User;

// Function to generate a unique user ID
// Second version
void generateUserId(User* user) {
    int randomDigit = rand() % 10;  // Generate a random digit (0-9)
    sprintf(user->userId, "%c%c%c%c%d%04d",
            tolower(user->name[0]), tolower(user->name[1]), tolower(user->name[2]), tolower(user->name[3]),
            randomDigit, user->age % 10000);
}


// Function to handle sign-up process
void signUp(User* user) {
    printf("Enter your name: ");
    scanf("%s", user->name);

    printf("Enter your email: ");
    scanf("%s", user->email);

    // Validate and ask for a valid 10-digit phone number
    do {
        printf("Enter your 10-digit phone number: ");
        scanf("%s", user->phone);
        while (strlen(user->phone) < 10) {
            // Add leading zeros if the number is less than 10 digits
            memmove(user->phone + 1, user->phone, strlen(user->phone) + 1);
            user->phone[0] = '0';
        }
        if (strlen(user->phone) != 10) {
            printf("Invalid phone number. Please enter a 10-digit number.\n");
        }
    } while (strlen(user->phone) != 10);

    printf("Enter your age: ");
    scanf("%d", &user->age);

    printf("Enter your blood group: ");
    scanf("%s", user->bloodGroup);

    // Generate a unique user ID
    generateUserId(user);

    // Generate a simple password (for simplicity)
    sprintf(user->password, "%04d", user->age % 10000);

    // Display User ID and password after sign-up
    printf("\nUser ID: %s\n", user->userId);
    printf("Password: %s\n\n", user->password);

    // Store user information in a file
    FILE* storeFile = fopen("user_data.txt", "w");
    if (storeFile != NULL) {
        fprintf(storeFile, "%s %s %s %d %s %s %s\n", user->name, user->email, user->phone,
                user->age, user->bloodGroup, user->userId, user->password);
        fclose(storeFile);
    } else {
        printf("Error: Unable to store user information.\n");
    }
}

// Function to handle sign-in process
int signIn(User* user) {
    char enteredUserId[5];  // Limited to 4 digits
    char enteredPassword[5];  // Limited to 4 digits

    printf("Enter your User ID: ");
    scanf("%s", enteredUserId);

    printf("Enter your password: ");
    scanf("%s", enteredPassword);

    // Check if the entered User ID and password match
    return (strcmp(enteredUserId, user->userId) == 0 && strcmp(enteredPassword, user->password) == 0);
}

int main() {
    // Display welcome message and logo
    
    displayWelcomeMessage();
    displaySHSLogo();

    int choice;
    User currentUser;

    struct Patient patients[50];
    int patientCount = 0;
    int doctorCount = 0;
    int choice1;

    do {
        // Sign-up or sign-in
        printf("1. Sign Up\n2. Sign In\nEnter your choice (0 to exit): ");
        scanf("%d", &choice);

        if (choice == 1) {
            signUp(&currentUser);
            printf("Sign Up Successful!\n");
        } else if (choice == 2) {
            // Sign in using stored user information
            FILE* file = fopen("user_data.txt", "r");
            if (file != NULL) {
                fscanf(file, "%s %s %s %d %s %s %s", currentUser.name, currentUser.email, currentUser.phone,
       &currentUser.age, currentUser.bloodGroup, currentUser.userId, currentUser.password);
 fclose(file);

                if (signIn(&currentUser)) {
                    printf("Sign In Successful!\n");

                    // Interaction options
                    int interactionChoice;
                    printf("Choose how you want to interact:\n");
                    printf("1. Doctor\n2. Patient\nEnter your choice (0 to exit): ");
                    scanf("%d", &interactionChoice);

                    if (interactionChoice == 0) {
                        printf("Exiting...\n");
                        break;
                    } else if (interactionChoice == 1) {
                        // Interaction as a doctor
                        // Add your code for doctor interaction here
			    int choice;
    do {
        printf("1. Display Doctors\n");
        printf("2. Add Doctor\n");
        printf("3. Delete Doctor\n");
        printf("4. Search Doctor\n");
        printf("5. Sort Doctors by Disease\n");
        printf("6. Quick Appointment List\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayDoctors();
                break;
            case 2:
                addDoctor();
                break;
            case 3:
                deleteDoctor();
                break;
            case 4:
                searchDoctor();
                break;
            case 5:
                sortDoctors();
                break;
            case 6:
                quickAppointmentList();
                break;
            case 0:
                saveDataToFile(); // Save data to file on program exit
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
                        printf("\nInteracting as a doctor...\n");
                    } else if (interactionChoice == 2) {
                        // Interaction as a patient
                        // Add your code for patient interaction here
                        do { 
                        printf("\nInteracting as a patient...\n");
                        printf("1. Add Patient\n");
                        printf("2. Display Patients\n");
                        printf("3. Prescribe Medicine\n");
                        printf("4. View Prescriptions\n");
                        printf("5. Prescribe Test\n");
                        printf("0. Exit\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice1);
                        switch (choice1) {
                            case 1:
                                addPatient(patients, &patientCount);
                                break;
                            case 2:
                             displayPatients(patients, patientCount);
                             break;

                            case 3:
                                prescribeMedicine();
                                break;
                            case 4:
                                viewPrescriptions();
                                break;
                            case 5:
                                prescribeTest();
                                break;
                            case 0:
                                printf("Exiting...\n");
                                break;
                            default:
                                printf("Invalid choice. Please try again.\n");
                        }
                    } while (choice1 != 0);
                    }  
                    else {
                        printf("Invalid choice. Exiting...\n");
                        break;
                    }
                } else {
                    printf("Sign In Failed. Try again.\n");
                }
            } else {
                printf("No user data found. Sign Up first.\n");
            }
        } else if (choice != 0) {
            printf("Invalid choice. Please enter 1, 2, or 0 to exit.\n");
        }
    } while (choice != 0);

    return 0;
}
