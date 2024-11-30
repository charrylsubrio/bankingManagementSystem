#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_CLIENTS 100
#define MAX_ADMINS 10
#define MAX_TRANSACTIONS 1000
#define MAX_NAME_LEN 50
#define MAX_CONTACT_LEN 15
#define MAX_PASSWORD_LEN 20
#define MAX_TYPE_LEN 10

// Structures Definitions
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char contact[MAX_CONTACT_LEN];
    char password[MAX_PASSWORD_LEN];
    double balance;
} Client;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char password[MAX_PASSWORD_LEN];
} Admin;

typedef struct {
    int clientId;
    char type[MAX_TYPE_LEN]; // Deposit or Withdraw
    double amount;
} Transaction;

// Global Variables
Client clients[MAX_CLIENTS];
Admin admins[MAX_ADMINS];
Transaction transactions[MAX_TRANSACTIONS];
int clientCount = 0, adminCount = 0, transactionCount = 0;

// Function Prototypes
void loadData();
void saveData();
void displayMenu();
void displayClientMenu();
void displayAdminMenu();
void registerClient();
void loginClient();
void displayClientAction(Client *loggedClient);
void depositAmount(Client *loggedClient);
void withdrawAmount(Client *loggedClient);
void displayClientInfo(Client *loggedClient);
void registerAdmin();
void loginAdmin();
void displayAdminAction();
void viewAllClients();
void modifyClientDetails();
void removeClient();
void searchClient();
void sortClients();
void viewTransacHist();
void displayAdminCred();
int validateContactNumber(char contact[]);
int validateClientName(char name[]);
int validatePassword(char password[]);

// Main Function
int main() {
	srand(time(0)); // Seed for random number generation
    loadData();
    int choice;

    while (1) {
        displayMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayClientMenu();
                break;
            case 2:
                displayAdminMenu();
                break;
            case 0:
                saveData();
                printf("Exiting the system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Functions Definitions
void loadData() {
    FILE *file;

    // Load clients
    file = fopen("clients.txt", "r"); // Open as text file
    if (file) {
        fscanf(file, "%d\n", &clientCount); // Read client count
        for (int i = 0; i < clientCount; i++) {
            fscanf(file, "%d,%49[^,],%14[^,],%19[^,],%lf\n", 
                   &clients[i].id, 
                   clients[i].name, 
                   clients[i].contact, 
                   clients[i].password, 
                   &clients[i].balance);
        }
        fclose(file);
    } else {
        printf("Error loading clients data.\n");
    }

    // Load admins
    file = fopen("admins.txt", "r"); // Open as text file
    if (file) {
        fscanf(file, "%d\n", &adminCount); // Read admin count
        for (int i = 0; i < adminCount; i++) {
            fscanf(file, "%d,%49[^,],", 
                   &admins[i].id, 
                   admins[i].name);

            // Read password using fgets to handle newline characters
            fgets(admins[i].password, sizeof(admins[i].password), file);

            // Remove trailing newline character (if any)
            admins[i].password[strcspn(admins[i].password, "\n")] = '\0'; 
        }
        fclose(file);
    } else {
        printf("Error loading admin data.\n");
    }

    // Load transactions
    file = fopen("transactions.txt", "r"); // Open as text file
    if (file) {
        fscanf(file, "%d\n", &transactionCount); // Read transaction count
        for (int i = 0; i < transactionCount; i++) {
            fscanf(file, "%d,%9[^,],%lf\n", 
                   &transactions[i].clientId, 
                   transactions[i].type, 
                   &transactions[i].amount);
        }
        fclose(file);
    } else {
        printf("Error loading transaction data.\n");
    }
}

void saveData() {
    FILE *file;

    // Save clients
    file = fopen("clients.txt", "w"); // Open as text file
    if (file) {
        fprintf(file, "%d\n", clientCount); // Save client count first
        for (int i = 0; i < clientCount; i++) {
            fprintf(file, "%d,%s,%s,%s,%.2f\n", 
                    clients[i].id, 
                    clients[i].name, 
                    clients[i].contact, 
                    clients[i].password, 
                    clients[i].balance);
        }
        fclose(file);
    }

    // Save admins
    file = fopen("admins.txt", "w"); // Open as text file
    if (file) {
        fprintf(file, "%d\n", adminCount); // Save admin count first
        for (int i = 0; i < adminCount; i++) {
            fprintf(file, "%d,%s,%s\n", 
                    admins[i].id, 
                    admins[i].name, 
                    admins[i].password);
        }
        fclose(file);
    }

    // Save transactions
    file = fopen("transactions.txt", "w"); // Open as text file
    if (file) {
        fprintf(file, "%d\n", transactionCount); // Save transaction count first
        for (int i = 0; i < transactionCount; i++) {
            fprintf(file, "%d,%s,%.2f\n", 
                    transactions[i].clientId, 
                    transactions[i].type, 
                    transactions[i].amount);
        }
        fclose(file);
    }
}

void displayMenu() {
    printf("\n--- BANKING MANAGEMENT SYSTEM ---\n\n");
    printf("[1] - CLIENT\n");
    printf("[2] - ADMIN\n");
    printf("[0] - EXIT\n");
}

void displayClientMenu() {
    int choice;
    printf("\n--- CLIENT MENU ---\n\n");
    printf("[1] - REGISTER\n");
    printf("[2] - LOGIN\n");
    printf("[0] - EXIT\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            registerClient();
            break;
        case 2:
            loginClient();
            break;
        case 0:
            break;
        default:
            printf("Invalid choice. Try again.\n");
    }
}

void displayAdminMenu() {
    int choice;
    printf("\n--- ADMIN MENU ---\n\n");
    printf("[1] - REGISTER\n");
    printf("[2] - LOGIN\n");
    printf("[0] - EXIT\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            registerAdmin();
            break;
        case 2:
            loginAdmin();
            break;
        case 0:
            break;
        default:
            printf("Invalid choice. Try again.\n");
    }
}

void registerClient() {
    if (clientCount >= MAX_CLIENTS) {
        printf("Client limit reached. Cannot register more clients.\n");
        return;
    }

    Client newClient;

    // Generate a unique 4-digit Client ID
    int uniqueId;
    int isUnique;
    do {
        uniqueId = (rand() % 9000) + 1000; // Generate random number between 1000 and 9999
        isUnique = 1; // Assume it's unique

        // Check if the ID already exists
        for (int i = 0; i < clientCount; i++) {
            if (clients[i].id == uniqueId) {
                isUnique = 0; // Not unique, regenerate
                break;
            }
        }
    } while (!isUnique);
    newClient.id = uniqueId;

    // Validate name
    do {
        printf("Enter name: ");
        scanf(" %[^\n]", newClient.name);
        if (!validateClientName(newClient.name)) {
            printf("Invalid name. Name must not contain digits. Please try again.\n");
        }
    } while (!validateClientName(newClient.name));

    // Validate password
    int validPassword = 0;
    do {
        printf("Enter password: ");
        scanf("%s", newClient.password);

        // Check password validity
        if (strlen(newClient.password) < 8) {
            printf("Password must be at least 8 characters long.\n");
        } else if (!validatePassword(newClient.password)) {
            printf("Password must contain at least one uppercase letter.\n");
        } else {
            validPassword = 1; // Password is valid
        }
    } while (!validPassword);

    // Validate contact number
    do {
        printf("Enter 11-digit Contact Number: ");
        scanf("%s", newClient.contact);
        if (!validateContactNumber(newClient.contact)) {
            printf("\nError: Please enter a valid 11-digit number without spaces or special characters.\n");
        }
    } while (!validateContactNumber(newClient.contact));

    // Validate balance
    do {
        printf("Enter initial deposit (minimum 500): ");
        scanf("%lf", &newClient.balance);
        if (newClient.balance < 500) {
            printf("Initial deposit must be at least 500. Please try again.\n\n");
        }
    } while (newClient.balance < 500);

    // Add the new client to the list
    clients[clientCount++] = newClient;
    printf("Client registered successfully! Your ID is %d.\n", newClient.id);

    // Record transaction
    transactions[transactionCount].clientId = newClient.id;
    strcpy(transactions[transactionCount].type, "Deposit");
    transactions[transactionCount].amount = newClient.balance;
    transactionCount++;
}

int validateClientName(char name[]) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (isdigit(name[i])) {
            return 0; // Name contains a digit
        }
    }
    return 1; // Valid name
}

int validatePassword(char password[]) {
    int hasUpper = 0, hasMinLength = 0;

    if (strlen(password) >= 8) {
        hasMinLength = 1;
    }

    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) {
            hasUpper = 1;
        }
    }

    return hasUpper && hasMinLength; // Valid if both conditions are met
}

int validateContactNumber(char contact[]) {
    if (strlen(contact) != 11) {
        return 0; // Contact number must be exactly 11 digits
    }
    for (int i = 0; i < 11; i++) {
        if (!isdigit(contact[i])) {
            return 0; // Contains non-numeric characters
        }
    }
    return 1; // Valid contact number
}

void loginClient() {
    int id;
    char password[20];
    int idFound = 0;

    printf("Enter Client ID: ");
    scanf("%d", &id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            idFound = 1; // ID exists
            printf("Enter Password: ");
            scanf("%s", password);

            if (strcmp(clients[i].password, password) == 0) {
                printf("Login successful. Welcome, %s!\n", clients[i].name);
                displayClientAction(&clients[i]);
                return; // Exit after successful login
            } else {
                printf("Invalid password. Please try again.\n");
                return; // Exit after invalid password
            }
        }
    }

    if (!idFound) {
        printf("Invalid ID. Please try again.\n");
    }
}

void displayClientAction(Client *loggedClient) {
    int choice;
    do {
        printf("\n--- CLIENT ACTION MENU ---\n\n");
        printf("[1] - DEPOSIT AMOUNT\n");
        printf("[2] - WITHDRAW AMOUNT\n");
        printf("[3] - VIEW ACCOUNT INFO\n");
        printf("[0] - LOGOUT\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                depositAmount(loggedClient);
                break;
            case 2:
                withdrawAmount(loggedClient);
                break;
            case 3:
                displayClientInfo(loggedClient);
                break;
            case 0:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
}

void depositAmount(Client *loggedClient) {
    double deposit;
    printf("Enter deposit amount: ");
    scanf("%lf", &deposit);

    // Check if the deposit amount is valid
    if (deposit < 100) {
        printf("Deposit amount must be at least 100. Please try again.\n");
        return;
    }

    loggedClient->balance += deposit;
    printf("Deposit successful. New balance: %.2lf\n", loggedClient->balance);

    // Record transaction
    transactions[transactionCount].clientId = loggedClient->id;
    strcpy(transactions[transactionCount].type, "Deposit");
    transactions[transactionCount].amount = deposit;
    transactionCount++;
}


void withdrawAmount(Client *loggedClient) {
    double withdrawal;
    printf("Enter withdrawal amount: ");
    scanf("%lf", &withdrawal);

    if (withdrawal <= 0) {
        printf("Invalid withdrawal amount. Please enter a positive value.\n");
        return;
    }

    if (withdrawal > loggedClient->balance) {
        printf("Insufficient balance.\n");
        return;
    }

    if (loggedClient->balance - withdrawal < 500) {
        printf("Withdrawal denied. Balance cannot drop below 500.\n");
        return;
    }

    loggedClient->balance -= withdrawal;
    printf("Withdrawal successful. New balance: %.2lf\n", loggedClient->balance);

    // Record transaction
    transactions[transactionCount].clientId = loggedClient->id;
    strcpy(transactions[transactionCount].type, "Withdraw");
    transactions[transactionCount].amount = withdrawal;
    transactionCount++;
}

void displayClientInfo(Client *loggedClient) {
    printf("\n--- CLIENT ACCOUNT INFO ---\n");
    printf("ID: %d\n", loggedClient->id);
    printf("NAME: %s\n", loggedClient->name);
    printf("CONTACT: %s\n", loggedClient->contact);
    printf("BALANCE: %.2lf\n", loggedClient->balance);
}

void registerAdmin() {
    if (adminCount >= MAX_ADMINS) {
        printf("Admin limit reached. Cannot register more admins.\n");
        return;
    }

    Admin newAdmin;

    // Generate a unique 4-digit Admin ID
    int uniqueId;
    int isUnique;
    do {
        uniqueId = (rand() % 9000) + 1000; // Generate random number between 1000 and 9999
        isUnique = 1; // Assume it's unique

        // Check if the ID already exists
        for (int i = 0; i < adminCount; i++) {
            if (admins[i].id == uniqueId) {
                isUnique = 0; // Not unique, regenerate
                break;
            }
        }
    } while (!isUnique);
    newAdmin.id = uniqueId;

    // Input admin name
    printf("Enter admin name: ");
    scanf(" %[^\n]", newAdmin.name);

    // Input admin password
    printf("Enter admin password: ");
    scanf("%s", newAdmin.password);

    // Add the new admin to the list
    admins[adminCount++] = newAdmin;

    printf("Admin registered successfully! Your Admin ID is %d.\n", newAdmin.id);
}

void loginAdmin() {
    int id;
    char password[MAX_PASSWORD_LEN];
    int idFound = 0; // Flag to check if ID exists

    printf("Enter Admin ID: ");
    scanf("%d", &id);

    // Loop through admins to check for the entered ID
    for (int i = 0; i < adminCount; i++) {
        if (admins[i].id == id) {
            idFound = 1; // ID exists
            printf("Enter Password: ");
            scanf("%s", password);

            // Check if the entered password matches the admin's password
            if (strcmp(admins[i].password, password) == 0) {
                printf("Login successful. Welcome, %s!\n", admins[i].name);
                displayAdminAction();
                return; // Exit function after successful login
            } else {
                printf("Invalid password. Please try again.\n");
                return; // Exit function after invalid password
            }
        }
    }

    // If no matching ID is found
    if (!idFound) {
        printf("Invalid ID. Please try again.\n");
    }
}

void displayAdminAction() {
    int choice;
    while (1) {
        printf("\n--- ADMIN ACTIONS ---\n");
        printf("[1] - VIEW ALL CLIENTS\n");
        printf("[2] - MODIFY CLIENT DETAILS\n");
        printf("[3] - REMOVE CLIENT\n");
        printf("[4] - SEARCH CLIENT\n");
        printf("[5] - SORT CLIENTS\n");
        printf("[6] - VIEW TRANSACTION HISTORY\n");
        printf("[7] - DISPLAY ADMIN INFO\n");
        printf("[0] - LOGOUT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAllClients();
                break;
            case 2:
                modifyClientDetails();
                break;
            case 3:
                removeClient();
                break;
            case 4:
                searchClient();
                break;
            case 5:
                sortClients();
                break;
            case 6:
                viewTransacHist();
                break;
            case 7:
                displayAdminCred();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void viewAllClients() {
    printf("\n--- LIST OF ALL CLIENTS ---\n");
    for (int i = 0; i < clientCount; i++) {
        printf("ID: %d, Name: %s, Contact: %s, Balance: %.2lf\n", 
               clients[i].id, clients[i].name, clients[i].contact, clients[i].balance);
    }
}

void modifyClientDetails() {
    int id;
    printf("ENTER CLIENT ID TO MODIFY: ");
    scanf("%d", &id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            printf("ENTER NEW NAME: ");
            scanf(" %[^\n]", clients[i].name);
            printf("ENTER NEW CONTACT: ");
            scanf("%s", clients[i].contact);
            printf("ENTER NEW PASSWORD: ");
            scanf("%s", clients[i].password);
            printf("Client details updated successfully!\n");
            return;
        }
    }
    printf("Client with ID %d not found.\n", id);
}

void removeClient() {
    int id, i;
    printf("ENTER CLIENT ID TO REMOVE: ");
    scanf("%d", &id);

    for (i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            for (int j = i; j < clientCount - 1; j++) {
                clients[j] = clients[j + 1];
            }
            clientCount--;
            printf("Client removed successfully!\n");
            return;
        }
    }
    printf("Client with ID %d not found.\n", id);
}

void searchClient() {
    int id;
    printf("ENTER CLIENT ID TO SEARCH: ");
    scanf("%d", &id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            printf("Client found!\n");
            printf("ID: %d, Name: %s, Contact: %s, Balance: %.2lf\n", 
                   clients[i].id, clients[i].name, clients[i].contact, clients[i].balance);
            return;
        }
    }
    printf("Client with ID %d not found.\n", id);
}

void sortClients() {
    int choice;
    printf("\n--- SORT CLIENTS ---\n");
    printf("[1] - BY NAME\n");
    printf("[2] - BY BALANCE\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    for (int i = 0; i < clientCount - 1; i++) {
        for (int j = i + 1; j < clientCount; j++) {
            if ((choice == 1 && strcmp(clients[i].name, clients[j].name) > 0) ||
                (choice == 2 && clients[i].balance > clients[j].balance)) {
                Client temp = clients[i];
                clients[i] = clients[j];
                clients[j] = temp;
            }
        }
    }
    printf("Clients sorted successfully!\n");
    viewAllClients();
}

void viewTransacHist() {
    int clientId, found = 0;

    printf("Enter client ID to view transaction history: ");
    scanf("%d", &clientId);

    printf("\n--- Transaction History for Client ID %d ---\n", clientId);

    // Iterate over the transactions to find those that belong to the specified client ID
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].clientId == clientId) {
            printf("Type: %s, Amount: %.2lf\n", transactions[i].type, transactions[i].amount);
            found = 1; // Mark that at least one transaction was found
        }
    }

    if (!found) {
        printf("No transactions found for Client ID %d.\n", clientId);
    }
}

void displayAdminCred() {
    printf("\n--- LIST OF ADMINS ---\n");
    for (int i = 0; i < adminCount; i++) {
        printf("ID: %d, Name: %s\n", admins[i].id, admins[i].name);
    }
}