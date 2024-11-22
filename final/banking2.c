#include <stdio.h>

// Define constants for field lengths and limits
#define NAME_LENGTH 50            // Maximum length for names
#define CONTACT_NUMBER_LENGTH 12  // Maximum length for contact number (e.g., "+639123456789")
#define PASSWORD_LENGTH 20        // Maximum length for passwords
#define TRANSACTION_TYPE_LENGTH 10 // Maximum length for transaction types (e.g., "Deposit")
#define DATE_LENGTH 11            // Length for date strings (e.g., "YYYY-MM-DD")
#define TIME_LENGTH 6             // Length for time strings (e.g., "HH:MM")

// Define structures
typedef struct {
    int clientID;                        // Unique identifier for the client
    char name[NAME_LENGTH];              // Client's full name
    char contactNumber[CONTACT_NUMBER_LENGTH]; // Client's contact number
    char password[PASSWORD_LENGTH];      // Password for account access
    float balance;                       // Current account balance
} Client;

typedef struct {
    int adminID;                         // Unique identifier for the administrator
    char name[NAME_LENGTH];              // Administrator's full name
    char password[PASSWORD_LENGTH];      // Password for admin account access
} Admin;

typedef struct {
    int clientID;                        // Client ID associated with the transaction
    char transactionType[TRANSACTION_TYPE_LENGTH]; // Type of transaction
    float amount;                        // Amount for the transaction
    char date[DATE_LENGTH];              // Date of transaction (e.g., "YYYY-MM-DD")
    char time[TIME_LENGTH];              // Time of transaction (e.g., "HH:MM")
} Transaction;

void load_data();
void displayMenu();

int main() {
    load_data();
    int choice;
    
    displayMenu();
    scanf("%d", &choice);
    getchar(); 
	
    switch(choice) {
        case 1:
            printf("\nClient menu selected, Press any key to continue. . .\n");
            break;
        case 2:
            printf("\nAdmin menu selected, Press any key to continue. . .\n");
            break;
        case 3:
            printf("\nExiting the program.\n");
            break;
        default:
            printf("\nInvalid choice, please try again.\n");
            break;
    }

    return 0; 
}

void load_data() {

}

void displayMenu() {
	printf("BANKING MANAGEMENT SYSTEM\n\n");
    printf("MAIN MENU\n\n");
    printf("[1] - CLIENT\n");
    printf("[2] - ADMIN\n");
    printf("[3] - EXIT\n\n");
    printf("Enter your choice: ");
}