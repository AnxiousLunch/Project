#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_DOCTORS 100

//Structures declared here
struct Appointment {
    char doctorName[10];
    char patientName[10];
    char date[20];
    char time[20];
    char description[100];
};

struct Doctor {
	char id[10];
    char name[50];
    char practiceLocation[100];
    char specialization[50];
    char phone[15];
    char appointments[100];
};

struct Patient {
	char id[6];
    char name[50];
    int age;
    char gender[10];
    char diagnosis[50];
};

// Structure for user information
typedef struct {
    char name[50];
    char email[50];
    char phone[15];
    int age;
    char bloodGroup[5];
    char userId[10];
    char password[5];
} User;

struct Doctor doctors[100];

//Global Variables here: 
int doctorCount = 0;

//Doctor functions declartion:
void displayDoctors();
void addDoctor();
void searchDoctor();
void displayAppointments();
void saveDataToFile();
void createAppointment(struct Appointment *appointment);
void loadDataFromFile();

//Doctors functions details :
void createAppointment(struct Appointment *appointment) {
	printf("Creating Doctor Appointment\n");
	printf("Enter Doctor Name : ");
    scanf("%s", appointment->doctorName);	
	
    printf("Enter Patient Name : ");
    scanf("%s", appointment->patientName);
    
    printf("Enter date of Appointment (DD-MM-YY) : ");
    scanf("%s", appointment->date);

    printf("Enter time of Appointment(HH:MM AM/PM): ");
    scanf("%s", appointment->time);

    // Clear input buffer
    while (getchar() != '\n');

    printf("Enter appointment description: ");
    fgets(appointment->description, sizeof(appointment->description), stdin);

    // Remove the newline character if it exists
    size_t len = strlen(appointment->description);
    if (len > 0 && appointment->description[len - 1] == '\n') {
        appointment->description[len - 1] = '\0';
    }
    //saving to appointment file
	FILE *file = fopen("doctorAppointments.txt", "a");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    fprintf(file, "Doctor Name : %s\n", appointment->doctorName);
    fprintf(file, "Patient Name : %s\n", appointment->patientName);
    fprintf(file, "Date: %s\n", appointment->date);
    fprintf(file, "Time: %s\n", appointment->time);
    fprintf(file, "Description: %s\n", appointment->description);
    
    fprintf(file, "---------------------------------\n");

    fclose(file);

    printf("Appointment saved successfully.\n");
}

void displayAppointments() {
	printf("Doctor Appointment List : \n");
    FILE *file = fopen("doctorAppointments.txt", "r");

    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

void displayDoctors() {
	printf("\nDoctor's List from File");
    FILE *file = fopen("doctors.txt", "r");

    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
	
    printf("\nList of Newly Added Doctors:\n");
    for (int i = 0; i < doctorCount; ++i) {
        printf("%d. %s - %s - %s\n", i + 1, doctors[i].name, doctors[i].practiceLocation, doctors[i].specialization);
    }
}

void addDoctor() {
    if (doctorCount < MAX_DOCTORS) {
    	
    	printf("\nEnter Doctor Id (4 digits): ");
        scanf("%s", doctors[doctorCount].id);
        
        printf("Enter Doctor's Name: ");
        scanf(" %[^\n]", doctors[doctorCount].name);
        
        printf("Enter Doctor's Specialization : ");
        scanf(" %[^\n]", doctors[doctorCount].specialization);

        printf("Enter Doctor's Phone Number: ");
        scanf("%s", doctors[doctorCount].phone);
        
        printf("Enter the Practice address: ");
        // Clear input buffer
    while (getchar() != '\n');
    
    fgets(doctors[doctorCount].practiceLocation, sizeof(doctors[doctorCount].practiceLocation), stdin);
    
    // Remove the newline character if it exists
    size_t len = strlen(doctors[doctorCount].practiceLocation);
    if (len > 0 && doctors[doctorCount].practiceLocation[len - 1] == '\n') {
        doctors[doctorCount].practiceLocation[len - 1] = '\0';
    }

        printf("Doctor added successfully.\n");

        doctorCount++;
        saveDataToFile(); // Save data to file after adding a doctor
    } else {
        printf("Cannot add more doctors. Database full.\n");
    }
}

void searchDoctor() {
    if (doctorCount > 0) {
        char searchName[50];
        int found = 0;

        printf("\nEnter Dr. Name to search : ");
        scanf("%s", searchName);

        for (int i = 0; i < doctorCount; ++i) {
            if (strcmp(doctors[i].name, searchName) == 0) {
                printf("Doctor found: %s - %s - %s\n", doctors[i].name, doctors[i].practiceLocation, doctors[i].specialization);
                found = 1;
            }
        }

        if (!found) {
            printf("No doctors found treating %s.\n", searchName);
        }
    } else {
        printf("No doctors to search. Database empty.\n");
    }
}

void saveDataToFile() {
    FILE *file = fopen("doctors.txt", "a");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < doctorCount; ++i) {
        fprintf(file, "\n\nDoctor's Id : %s\nName : %s\nPractice Address : %s\nSpecialization : %s\nDoctor Phone No. : %s\n", doctors[i].id, doctors[i].name, doctors[i].practiceLocation, doctors[i].specialization, doctors[i].phone, doctors[i].appointments);
    }

    fclose(file);
}

//Patient functions details
void addPatient(struct Patient patients[], int *patientCount) {
    struct Patient newPatient;
    printf("\nEnter patient id (5-digits): ");
    scanf("%s", &newPatient.id);
    printf("Enter patient name: ");
    scanf(" %[^\n]", newPatient.name);
    printf("Enter patient age: ");
    scanf("%d", &newPatient.age);
    printf("Enter patient gender: ");
    scanf("%s", newPatient.gender);
    printf("Enter diagnosis: ");
    scanf(" %[^\n]", newPatient.diagnosis);
    FILE *file = fopen("patients.txt", "a");
    if (file == NULL) {
        printf("Unable to open the file\n");
        return;
    }
    fprintf(file, "%s,%s,%d,%s,%s\n", newPatient.id, newPatient.name, newPatient.age, newPatient.gender, newPatient.diagnosis);
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
    char line[100], name[50], gender[10], diagnosis[50], id[50];
    int age;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%5[^,],%49[^,],%d,%9[^,],%49[^\n]\n", id, name, &age, gender, diagnosis) == 5) {
            printf("\nPateint ID: %s, Name: %s, Age: %d, Gender: %s, Diagnosis: %s\n", id, name, age, gender, diagnosis);
        } else {
            printf("\nInvalid line format: %s", line);
        }
    }

    fclose(file);
}

void prescribeMedicine() {
    char patientName[50];
    char medicine[50];
    char diagnosis[50];
    char id[10];

	printf("Enter patient id: ");
	scanf(" %s", id);
    printf("Enter patient name: ");
    scanf(" %[^\n]", patientName);
    printf("Enter prescribed medicine: ");
    scanf(" %[^\n]", medicine);

    FILE *file;
    file = fopen("patients.txt", "r");

    if (file == NULL) {
        printf("\nCould not open file.\n");
        return;
    }

    char newLine[256];
    while (fgets(newLine, sizeof(newLine), file)) {
        struct Patient patient;
        sscanf(newLine, "%5[^,],%49[^,],%d,%9[^,],%49[^\n]\n", &patient.id, patient.name, &patient.age, patient.gender, diagnosis);

        if (strcmp(patient.id, id) == 0) {
            snprintf(newLine, sizeof(newLine), "%s, %s, %d, %s\n", patient.id, patient.name, patient.age, medicine);
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
    printf("\nMedicine Prescribed Successfully!\n");
}

void prescribeTest() {
    char patientName[50];
    char test[50];
    char diagnosis[50];
    char id[10];
    
    printf("\nEnter patient id: ");
    scanf(" %s", id);
    printf("Enter patient name: ");
    scanf(" %[^\n]", patientName);
    printf("Enter test name: ");
    scanf(" %[^\n]", test);

    FILE *file;
    file = fopen("patients.txt", "r");

    if (file == NULL) {
        printf("\nCould not open file.\n");
        return;
    }

    char newLine[256];
    while (fgets(newLine, sizeof(newLine), file)) {
        struct Patient patient;
        sscanf(newLine, "%5[^,],%49[^,],%d,%9[^,],%49[^\n]\n", patient.id, patient.name, &patient.age, patient.gender, diagnosis);

        if (strcmp(patient.id, id) == 0) {
            snprintf(newLine, sizeof(newLine), "%s, %s, %d, %s\n", patient.id, patient.name, patient.age, test);
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
    printf("\nTest Prescribed Successfully\n");
}



void viewMedicine() {
    FILE *file;
    file = fopen("PrescribedMedicine.txt", "r");
    if (file == NULL) {
        printf("\nCould not open file.\n");
        return;
    }
    printf("\nPrescribed Medicine: \n");
    char line[100], name[50], gender[10], prescription[50], id[10];
    int age;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (sscanf(line, "%5[^,],%49[^,],%d,%49[^,]", id, name, &age, prescription) == 4) {
        	printf("\n-------------------------------\n");
            printf("\nID: %s, Name: %s, Age: %d\n", id, name, age);
            printf("Medicine: %s\n", prescription);
            printf("\n-------------------------------\n");
        } else {
            printf("\nInvalid line format: %s", line);
        }
    }
}

void viewTest() {
    FILE *file;
    file = fopen("PrescribedTest.txt", "r");
    if (file == NULL) {
        printf("\nCould not open file.\n");
        return;
    }
    printf("\nPrescribed Tests:\n");
    char line[100], name[50], gender[10], prescription[50], id[10];
    int age;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (sscanf(line, "%5[^,], %49[^,],%d,%49[^\n]", id, name, &age, prescription) == 4) {
        	printf("\n-------------------------------\n");
            printf("\nID: %s, Name: %s, Age: %d\n", id, name, age);
            printf("Test: %s\n", prescription);
            printf("\n-------------------------------\n");
        } else {
            printf("\nInvalid line format: %s", line);
        }
    }
}

void searchPatients() {
	char id[6], newLine[256], name[50], gender[10], diagnosis[50];
	int age;
	printf("\nEnter patient id (5-digits): ");
	scanf(" %[^\n]", id);
	FILE* file = fopen("patients.txt", "r");
	if (file == NULL) {
        printf("\nCould not open file.\n");
        return;
    }
    while(fgets(newLine, sizeof(newLine), file)) {
    	struct Patient patient;
        sscanf(newLine, "%5[^,],%49[^,],%d,%9[^,],%49[^\n]\n", patient.id, patient.name, &patient.age, patient.gender, diagnosis);
        printf("\n%s\n%s", id, patient.id);
        if (strcmp(patient.id, id) == 0) {
        	printf("\n-------------------------------\n");
            printf("\nID: %s\nName: %s\nAge: %d\nGender: %s\nDiagnosis: %s", id, patient.name, patient.age, patient.gender, diagnosis);
            printf("\n-------------------------------\n");
			break;
        }
	}
    
}

//UI functions
void displayWelcomeMessage() {
    printf("\n");
    printf("                 WELCOME TO SWIFT HEALTH SYSTEM\n");
    printf("                 ==============================\n\n");
}

// Function to display the SHS logo using hashtags
void displaySHSLogo() {
	int p=4;
    printf("\n");
    printf("                              #############################\n");
    printf("                             ###                         ###\n");
    printf("                            ##                             ##\n");
    printf("                           #       %c%c%c%c%c  %c   %c   %c%c%c%c%c      #\n",p,p,p,p,p,p,p,p,p,p,p,p);
    printf("                          ##      %c       %c   %c  %c           ##\n",p,p,p,p,p,p,p);
    printf("                         ###        %c%c%c%c  %c %c %c    %c%c%c%c      ###\n",p,p,p,p,p,p,p,p,p);
    printf("                        ####            %c %c   %c        %c     ####\n",p,p,p,p);
    printf("                         ###       %c%c%c%c%c  %c   %c   %c%c%c%c%c      ###\n",p,p,p,p,p,p,p,p,p);
    printf("                          ##                                 ##\n");
    printf("                           #    **Swift Health System**    #\n");
    printf("                            ##                             ##\n");
    printf("                             ###                         ###\n");
    printf("                              #############################\n\n");
}

// Function to generate a unique user ID
// Second version
void generateUserId(User* user) {
    int randomDigit = rand() % 10;  // Generate a random digit (0-9)
    sprintf(user->userId, "%c%c%c%c%d%04d",
            tolower(user->name[0]), tolower(user->name[1]), tolower(user->name[2]), tolower(user->name[3]),
            randomDigit, user->age % 10000);
}


// Function to handle sign-up process

int isValidEmail(const char* email) {
    // Simple email validation, you can use a more complex one if needed
    return (strstr(email, "@") != NULL && strstr(email, ".") != NULL);
}

int isValidPhoneNumber(const char* phone) {
    // Simple phone number validation, checks if it contains only digits
    for (int i = 0; i < strlen(phone); i++) {
        if (!isdigit(phone[i])) {
            return 0;
        }
    }
    return 1;
}

int isValidName(const char* name) {
    // Name validation, checks if it contains only alphabetical characters and spaces
    for (int i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i]) && !isspace(name[i])) {
            return 0;
        }
    }
    return 1;
}

int isValidBloodGroup(const char* bloodGroup) {
    // Blood group validation, checks if it follows the format 'X+' or 'X-'
    if (strlen(bloodGroup) != 2 || !isalpha(bloodGroup[0]) || (bloodGroup[1] != '+' && bloodGroup[1] != '-')) {
        return 0;
    }
    return 1;
}

void signUp(User* user) {
    printf("Enter your name: ");
    do {
        scanf("%s", user->name);
        if (!isValidName(user->name)) {
            printf("Invalid name. Please enter a valid name containing only alphabetical characters and spaces.\n");
        }
    } while (!isValidName(user->name));

    // Validate and ask for a valid email
    do {
        printf("Enter your email: ");
        scanf("%s", user->email);
        if (!isValidEmail(user->email)) {
            printf("Invalid email. Please enter a valid email address.\n");
        }
    } while (!isValidEmail(user->email));

    // Validate and ask for a valid 10-digit phone number
    do {
        printf("Enter your 10-digit phone number: ");
        scanf("%s", user->phone);
        while (strlen(user->phone) < 10) {
            // Add leading zeros if the number is less than 10 digits
            memmove(user->phone + 1, user->phone, strlen(user->phone) + 1);
            user->phone[0] = '0';
        }
        if (!isValidPhoneNumber(user->phone)) {
            printf("Invalid phone number. Please enter a 10-digit number.\n");
        }
    } while (!isValidPhoneNumber(user->phone));

    // Validate and ask for a valid age
    do {
        printf("Enter your age: ");
        if (scanf("%d", &user->age) != 1 || user->age < 1 || user->age > 150) {
            printf("Invalid age. Please enter a valid age between 1 and 150.\n");
            while (getchar() != '\n');  // Clear the input buffer
        }
    } while (user->age < 1 || user->age > 150);

    // Validate and ask for a valid blood group
    do {
        printf("Enter your blood group: ");
        scanf("%s", user->bloodGroup);
        if (!isValidBloodGroup(user->bloodGroup)) {
            printf("Invalid blood group. Please enter a valid blood group in the format 'X+' or 'X-'.\n");
        }
    } while (!isValidBloodGroup(user->bloodGroup));

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
    
    system("COLOR F1");// Change Apha to change background color and number to change text color 
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 12;  // Change this to change size
    fontInfo.dwFontSize.Y = 18.5;  // Change this to change size
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy(fontInfo.FaceName, L"Elephant");
    SetCurrentConsoleFontEx(console, FALSE, &fontInfo);
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
                        int choice;
	struct Appointment doctorAppointment;
    do {
    	printf("\nInteracting with Doctor DB...\n");
        printf("\n1. Display Doctors\n");
        printf("2. Add Doctor\n");
        printf("3. Search Doctor by Name\n");
        printf("4. Create Appointment\n");
        printf("5. Display Appointments\n");
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
                searchDoctor();
                break;
            case 4:
                createAppointment(&doctorAppointment);
                break;
            case 5:
                displayAppointments();
                break;
            case 0:
                saveDataToFile(); // Save data to file on program exit
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
                    } else if (interactionChoice == 2) {
                        // Interaction as a patient
                        // Add your code for patient interaction here
                        do { 
                        printf("\nInteracting with Patient DB...\n");
                        printf("1. Add Patient\n");
                        printf("2. Display Patients\n");
                        printf("3. Prescribe Medicine\n");
                        printf("4. View Medication\n");
                        printf("5. Prescribe Test\n");
                        printf("6. View Test\n");
                        printf("7. Search by patients ID\n");
                        printf("0. Exit\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice1);
                        switch (choice1) {
                            case 1:
                                addPatient(patients, &patientCount);
                                break;
                            case 2:
                             displayPatients();
                             break;

                            case 3:
                                prescribeMedicine();
                                break;
                            case 4:
                                viewMedicine();
                                break;
                            case 5:
                                prescribeTest();
                                break;
                            case 6:
                            	viewTest();
                            	break;
                            case 7:
                            	searchPatients();
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
