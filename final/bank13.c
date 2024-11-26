#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_CLIENTS 100
#define MAX_ADMINS 10
#define MAX_TRANSACTIONS 1000
#define MAX_NAME_LEN 50
#define MAX_CONTACT_LEN 15
#define MAX_PASSWORD_LEN 20
#define MAX_TYPE_LEN 10

// Structs
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

// Function Implementations
void loadData() {
    FILE *file;

    // Load clients
    file = fopen("clients.txt", "rb");
    if (file) {
        fread(&clientCount, sizeof(int), 1, file);
        fread(clients, sizeof(Client), clientCount, file);
        fclose(file);
    }

    // Load admins
    file = fopen("admins.txt", "rb");
    if (file) {
        fread(&adminCount, sizeof(int), 1, file);
        fread(admins, sizeof(Admin), adminCount, file);
        fclose(file);
    }

    // Load transactions
    file = fopen("transactions.txt", "rb");
    if (file) {
        fread(&transactionCount, sizeof(int), 1, file);
        fread(transactions, sizeof(Transaction), transactionCount, file);
        fclose(file);
    }
}

//void saveData() {
//    FILE *file;
//
//    // Save clients
//    file = fopen("clients.txt", "wb");
//    if (file) {
//        fwrite(&clientCount, sizeof(int), 1, file);
//        fwrite(clients, sizeof(Client), clientCount, file);
//        fclose(file);
//    }
//
//    // Save admins
//    file = fopen("admins.txt", "wb");
//    if (file) {
//        fwrite(&adminCount, sizeof(int), 1, file);
//        fwrite(admins, sizeof(Admin), adminCount, file);
//        fclose(file);
//    }
//
//    // Save transactions
//    file = fopen("transactions.txt", "wb");
//    if (file) {
//        fwrite(&transactionCount, sizeof(int), 1, file);
//        fwrite(transactions, sizeof(Transaction), transactionCount, file);
//        fclose(file);
//    }
//}

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
    printf("1. REGISTER\n");
    printf("2. LOGIN\n");
    printf("0. EXIT\n");
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
    printf("1. REGISTER\n");
    printf("2. LOGIN\n");
    printf("0. EXIT\n");
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
    newClient.id = clientCount + 1;

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
            printf("Invalid contact number. Please try again.\n");
        }
    } while (!validateContactNumber(newClient.contact));

    // Add balance
    printf("Enter initial deposit: ");
    scanf("%lf", &newClient.balance);

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

    printf("Enter Client ID: ");
    scanf("%d", &id);
    printf("Enter Password: ");
    scanf("%s", password);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id && strcmp(clients[i].password, password) == 0) {
            printf("Login successful. Welcome, %s!\n", clients[i].name);
            displayClientAction(&clients[i]);
            return;
        }
    }
    printf("Invalid ID or password. Try again.\n");
}

void displayClientAction(Client *loggedClient) {
    int choice;
    do {
        printf("\n--- CLIENT ACTION MENU ---\n\n");
        printf("1. Deposit Amount\n");
        printf("2. Withdraw Amount\n");
        printf("3. View Account Info\n");
        printf("0. Logout\n");
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

    if (deposit <= 0) {
        printf("Invalid deposit amount. Please enter a positive value.\n");
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
    printf("Name: %s\n", loggedClient->name);
    printf("Contact: %s\n", loggedClient->contact);
    printf("Balance: %.2lf\n", loggedClient->balance);
}

// Admin functions (admin registration, login, etc.) will go here similarly.



// Implement other admin-related functionalities similarly...
void registerAdmin() {
    if (adminCount >= MAX_ADMINS) {
        printf("Admin limit reached. Cannot register more admins.\n");
        return;
    }

    Admin newAdmin;
    newAdmin.id = adminCount + 1;

    // Validate unique admin name
    int isUnique;
    do {
        isUnique = 1; // Assume unique
        printf("Enter admin name: ");
        scanf(" %[^\n]", newAdmin.name);

        // Check if name already exists
        for (int i = 0; i < adminCount; i++) {
            if (strcmp(admins[i].name, newAdmin.name) == 0) {
                printf("Admin name already exists. Please choose a different name.\n");
                isUnique = 0; // Name is not unique
                break;
            }
        }
    } while (!isUnique);

    printf("Enter password: ");
    scanf("%s", newAdmin.password);

    // Add new admin to the list
    admins[adminCount++] = newAdmin;
    printf("Admin registered successfully! Your ID is %d.\n", newAdmin.id);
}


void loginAdmin() {
    int id;
    char password[20];
    printf("Enter admin ID: ");
    scanf("%d", &id);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < adminCount; i++) {
        if (admins[i].id == id && strcmp(admins[i].password, password) == 0) {
            printf("Login successful! Welcome, Admin %s.\n", admins[i].name);
            displayAdminAction();
            return;
        }
    }
    printf("Invalid ID or password. Try again.\n");
}

void displayAdminAction() {
    int choice;
    while (1) {
        printf("\n--- Admin Actions ---\n");
        printf("1. View All Clients\n");
        printf("2. Modify Client Details\n");
        printf("3. Remove Client\n");
        printf("4. Search Client\n");
        printf("5. Sort Clients\n");
        printf("6. View Transaction History\n");
        printf("7. Display Admin Info\n");
        printf("0. Logout\n");
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
    printf("\n--- List of All Clients ---\n");
    for (int i = 0; i < clientCount; i++) {
        printf("ID: %d, Name: %s, Contact: %s, Balance: %.2lf\n", 
               clients[i].id, clients[i].name, clients[i].contact, clients[i].balance);
    }
}

void modifyClientDetails() {
    int id;
    printf("Enter client ID to modify: ");
    scanf("%d", &id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            printf("Enter new name: ");
            scanf(" %[^\n]", clients[i].name);
            printf("Enter new contact: ");
            scanf("%s", clients[i].contact);
            printf("Enter new password: ");
            scanf("%s", clients[i].password);
            printf("Client details updated successfully!\n");
            return;
        }
    }
    printf("Client with ID %d not found.\n", id);
}

void removeClient() {
    int id, i;
    printf("Enter client ID to remove: ");
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
    printf("Enter client ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id) {
            printf("Client Found!\n");
            printf("ID: %d, Name: %s, Contact: %s, Balance: %.2lf\n", 
                   clients[i].id, clients[i].name, clients[i].contact, clients[i].balance);
            return;
        }
    }
    printf("Client with ID %d not found.\n", id);
}

void sortClients() {
    int choice;
    printf("\n--- Sort Clients ---\n");
    printf("1. By Name\n");
    printf("2. By Balance\n");
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
    printf("\n--- List of Admins ---\n");
    for (int i = 0; i < adminCount; i++) {
        printf("ID: %d, Name: %s\n", admins[i].id, admins[i].name);
    }
}