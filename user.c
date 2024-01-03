#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
    char userId[5];  // Limited to 4 digits
    char password[5];  // Limited to 4 digits
} User;

// Function to generate a unique user ID
void generateUserId(User* user) {
    // Generate a simple unique ID based on user information (for simplicity)
    sprintf(user->userId, "%04d", user->age % 10000);
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
                        printf("Interacting as a doctor...\n");
                    } else if (interactionChoice == 2) {
                        // Interaction as a patient
                        // Add your code for patient interaction here
                        printf("Interacting as a patient...\n");
                    } else {
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