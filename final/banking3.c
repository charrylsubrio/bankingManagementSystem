#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 100
#define MAX_ADMINS 10
#define MAX_TRANSACTIONS 1000

// Structs
typedef struct {
    int id;
    char name[50];
    char contact[15];
    char password[20];
    double balance;
} Client;

typedef struct {
    int id;
    char name[50];
    char password[20];
} Admin;

typedef struct {
    int clientId;
    char type[10]; // Deposit or Withdraw
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

// Main Function
int main() {
    loadData();
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
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
    file = fopen("clients.dat", "rb");
    if (file) {
        fread(&clientCount, sizeof(int), 1, file);
        fread(clients, sizeof(Client), clientCount, file);
        fclose(file);
    }

    // Load admins
    file = fopen("admins.dat", "rb");
    if (file) {
        fread(&adminCount, sizeof(int), 1, file);
        fread(admins, sizeof(Admin), adminCount, file);
        fclose(file);
    }

    // Load transactions
    file = fopen("transactions.dat", "rb");
    if (file) {
        fread(&transactionCount, sizeof(int), 1, file);
        fread(transactions, sizeof(Transaction), transactionCount, file);
        fclose(file);
    }
}

void saveData() {
    FILE *file;

    // Save clients
    file = fopen("clients.dat", "wb");
    if (file) {
        fwrite(&clientCount, sizeof(int), 1, file);
        fwrite(clients, sizeof(Client), clientCount, file);
        fclose(file);
    }

    // Save admins
    file = fopen("admins.dat", "wb");
    if (file) {
        fwrite(&adminCount, sizeof(int), 1, file);
        fwrite(admins, sizeof(Admin), adminCount, file);
        fclose(file);
    }

    // Save transactions
    file = fopen("transactions.dat", "wb");
    if (file) {
        fwrite(&transactionCount, sizeof(int), 1, file);
        fwrite(transactions, sizeof(Transaction), transactionCount, file);
        fclose(file);
    }
}

void displayMenu() {
    printf("\n--- Banking Management System ---\n");
    printf("1. Client\n");
    printf("2. Admin\n");
    printf("0. Exit\n");
}

void displayClientMenu() {
    int choice;
    printf("\n--- Client Menu ---\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
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
    printf("\n--- Admin Menu ---\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
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

    printf("Enter name: ");
    scanf(" %[^\n]", newClient.name);
    printf("Enter contact number: ");
    scanf("%s", newClient.contact);
    printf("Enter password: ");
    scanf("%s", newClient.password);
    printf("Enter initial deposit: ");
    scanf("%lf", &newClient.balance);

    clients[clientCount++] = newClient;
    printf("Client registered successfully! Your ID is %d.\n", newClient.id);
}

void loginClient() {
    int id;
    char password[20];
    printf("Enter client ID: ");
    scanf("%d", &id);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == id && strcmp(clients[i].password, password) == 0) {
            printf("Login successful! Welcome %s.\n", clients[i].name);
            displayClientAction(&clients[i]);
            return;
        }
    }
    printf("Invalid ID or password. Try again.\n");
}

void displayClientAction(Client *loggedClient) {
    int choice;
    while (1) {
        printf("\n--- Client Actions ---\n");
        printf("1. Display Client Info\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("0. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayClientInfo(loggedClient);
                break;
            case 2:
                depositAmount(loggedClient);
                break;
            case 3:
                withdrawAmount(loggedClient);
                break;
            case 0:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void depositAmount(Client *loggedClient) {
    double amount;
    printf("Enter deposit amount: ");
    scanf("%lf", &amount);
    if (amount <= 0) {
        printf("Invalid amount. Try again.\n");
        return;
    }
    loggedClient->balance += amount;

    Transaction newTransaction = {loggedClient->id, "Deposit", amount};
    transactions[transactionCount++] = newTransaction;

    printf("Deposit successful! New balance: %.2lf\n", loggedClient->balance);
}

void withdrawAmount(Client *loggedClient) {
    double amount;
    printf("Enter withdrawal amount: ");
    scanf("%lf", &amount);
    if (amount <= 0 || amount > loggedClient->balance) {
        printf("Invalid amount. Try again.\n");
        return;
    }
    loggedClient->balance -= amount;

    Transaction newTransaction = {loggedClient->id, "Withdraw", amount};
    transactions[transactionCount++] = newTransaction;

    printf("Withdrawal successful! New balance: %.2lf\n", loggedClient->balance);
}

void displayClientInfo(Client *loggedClient) {
    printf("\n--- Client Information ---\n");
    printf("ID: %d\n", loggedClient->id);
    printf("Name: %s\n", loggedClient->name);
    printf("Contact: %s\n", loggedClient->contact);
    printf("Balance: %.2lf\n", loggedClient->balance);
}

// Implement other admin-related functionalities similarly...

void registerAdmin() {
    if (adminCount >= MAX_ADMINS) {
        printf("Admin limit reached. Cannot register more admins.\n");
        return;
    }

    Admin newAdmin;
    newAdmin.id = adminCount + 1;

    printf("Enter admin name: ");
    scanf(" %[^\n]", newAdmin.name);
    printf("Enter password: ");
    scanf("%s", newAdmin.password);

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
    int id;
    printf("Enter client ID to view transaction history: ");
    scanf("%d", &id);

    printf("\n--- Transaction History for Client ID %d ---\n", id);
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].clientId == id) {
            printf("Type: %s, Amount: %.2lf\n", transactions[i].type, transactions[i].amount);
        }
    }
}

void displayAdminCred() {
    printf("\n--- List of Admins ---\n");
    for (int i = 0; i < adminCount; i++) {
        printf("ID: %d, Name: %s\n", admins[i].id, admins[i].name);
    }
}