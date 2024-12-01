#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>

#define MAX_CLIENTS 100
#define MAX_ADMINS 10
#define MAX_TRANSACTIONS 1000
#define MAX_NAME_LEN 50
#define MAX_CONTACT_LEN 15
#define MAX_PASSWORD_LEN 20
#define MAX_TYPE_LEN 10
#define MIN_BAL 500
#define MIN_DEPOSIT 100

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
void displayMenu(int *choice);
void displayClientMenu(int *choice);
void displayAdminMenu(int *choice);
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
void displayHeader();
void clearScreen();
void displayCredits();

// Main Function
int main() {
	srand(time(0)); // Seed for random number generation
    loadData();
    int choice;
	
    do {
        displayMenu(&choice);

        switch(choice) {
            case 1:
                displayClientMenu(&choice);
                break;
            case 2:
                displayAdminMenu(&choice);
                break;
        }
    } while(choice != 0);
    
    saveData();
    displayCredits();
	
    return 0;
}

void displayCredits() {	
    displayHeader();
    
    printf("\t\t\t\t\t\t\t============= CREDITS =============");
    printf("\n\n\n\t\t\t\t\t\t\tDeveloped by: \n");
    printf("\t\t\t\t\t\t\t * Bit Builders\n");
	printf("\n\t\t\t\t\t\t\tProgrammers: \n");
	printf("\t\t\t\t\t\t\t * Lomarda, Ismael Marlon\n");	
	printf("\t\t\t\t\t\t\t * Subrio, Charryl\n\n\n");
	printf("\t\t\t\t\t\t\t===================================\n\n\n\n");
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

void displayHeader() {
	system("cls");
	
	printf("\n\n\n\n\t\t\t\t\t\t\t* * * * * * * * * * * * * * * * * *");
	printf("\n\t\t\t\t\t\t\t*\t\t\t\t  *");
    printf("\n\t\t\t\t\t\t\t*    BANKING MANAGEMENT SYSTEM    *");
    printf("\n\t\t\t\t\t\t\t*\t\t\t\t  *");
	printf("\n\t\t\t\t\t\t\t* * * * * * * * * * * * * * * * * *\n\n\n");
}

void displayMenu(int *choice) {
	do {
		displayHeader();
	
		printf("\t\t\t\t\t\t\t============ MAIN MENU ============\n\n");
    	printf("\t\t\t\t\t\t\t[1] - Client\n");
    	printf("\t\t\t\t\t\t\t[2] - Admin\n");
    	printf("\t\t\t\t\t\t\t[0] - Exit\n\n");
    	printf("\t\t\t\t\t\t\tPlease enter your choice: ");
    	
    	if(scanf("%d", &*choice) != 1 || *choice < 0 || *choice > 2) {
			fflush(stdin);
			printf("\n\t\t\t\t\t\t\tError: Please enter a number between 0 and 2.\n");
			clearScreen();
		}
	} while(*choice < 0 || *choice > 2);
}

void displayClientMenu(int *choice) {
    do {
	    displayHeader();
	    
	    printf("\t\t\t\t\t\t\t=========== CLIENT MENU ===========\n\n");
	    printf("\t\t\t\t\t\t\t[1] - Register\n");
	    printf("\t\t\t\t\t\t\t[2] - Login\n");
	    printf("\t\t\t\t\t\t\t[0] - Exit\n\n");
	    printf("\t\t\t\t\t\t\tPlease Enter your choice: ");
	    
		if(scanf("%d", &*choice) != 1 || *choice < 0 || *choice > 2) {
			fflush(stdin);
			printf("\n\t\t\t\t\t\t\tError: Please enter a number between 0 and 2.\n");
			clearScreen();
		}
	} while(*choice < 0 || *choice > 2);
	
    switch (*choice) {
        case 1:
            registerClient();
            displayClientMenu(choice);
            break;
        case 2:
            loginClient();
            displayClientMenu(choice);
            break;
        case 0:
        	displayMenu(choice);
    }
}

void displayAdminMenu(int *choice) {
    do {
	    displayHeader();
	    
	    printf("\t\t\t\t\t\t\t=========== ADMIN MENU ===========\n\n");
	    printf("\t\t\t\t\t\t\t[1] - Register\n");
	    printf("\t\t\t\t\t\t\t[2] - Login\n");
	    printf("\t\t\t\t\t\t\t[0] - Exit\n\n");
	    printf("\t\t\t\t\t\t\tPlease Enter your choice: ");
	    
		if(scanf("%d", &*choice) != 1 || *choice < 0 || *choice > 2) {
			fflush(stdin);
			printf("\n\t\t\t\t\t\t\tError: Please enter a number between 0 and 2.\n");
			clearScreen();
		}
	} while(*choice < 0 || *choice > 2);
	
    switch (*choice) {
        case 1:
            registerAdmin();
            displayAdminMenu(choice);
            break;
        case 2:
            loginAdmin();
            displayAdminMenu(choice);
            break;
        case 0:
        	displayMenu(choice);
    }
}

void registerClient() {
	int inputCtr = 0;
	
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
    	system("cls");
		displayHeader();
		
		printf("\t\t\t\t\t\t\t========= REGISTER CLIENT =========\n\n");
        printf("\t\t\t\t\t\t\tEnter name: ");
        scanf(" %[^\n]", newClient.name);
        if (!validateClientName(newClient.name)) {
            printf("\n\t\t\t\t\t\t\tInvalid name. Name must not contain digits. Please try again.\n");
            clearScreen();
        }
    } while (!validateClientName(newClient.name));

    // Validate password
    int validPassword = 0;
    do {
    	if(inputCtr == 1) {
			displayHeader();
			
			printf("\t\t\t\t\t\t\t========= REGISTER CLIENT =========\n\n");
        	printf("\t\t\t\t\t\t\tEnter name: %s\n", newClient.name);
		}
    	
        printf("\t\t\t\t\t\t\tEnter password: ");
        scanf("%s", newClient.password);

        // Check password validity
        if (strlen(newClient.password) < 8 || !validatePassword(newClient.password)) {
            printf("\n\t\t\t\t\t\t\tPassword must be at least 8 characters long with at least 1 uppercase letter.");
            inputCtr = 1;
			clearScreen();
//        } else if (!validatePassword(newClient.password)) {
//            printf("\n\t\t\t\t\t\t\tPassword must contain at least one uppercase letter.");
        } else {
            validPassword = 1; // Password is valid
        }
    } while (!validPassword);
	
	inputCtr = 0;
	
    // Validate contact number
    do {
    	if(inputCtr == 1) {
			displayHeader();
			
			printf("\t\t\t\t\t\t\t========= REGISTER CLIENT =========\n\n");
        	printf("\t\t\t\t\t\t\tEnter name: %s\n", newClient.name);
        	printf("\t\t\t\t\t\t\tEnter password: %s\n", newClient.password);
		}
    	
        printf("\t\t\t\t\t\t\tEnter 11-digit Contact Number: ");
        scanf("%s", newClient.contact);
        if (!validateContactNumber(newClient.contact)) {
            printf("\n\t\t\t\t\t\t\tError: Please enter a valid 11-digit number without spaces or special characters.\n");
            inputCtr = 1;
			clearScreen();
        }
    } while (!validateContactNumber(newClient.contact));
	
	inputCtr = 0;
	
    // Validate balance
    do {
    	if(inputCtr == 1) {
			displayHeader();
			
			printf("\t\t\t\t\t\t\t========= REGISTER CLIENT =========\n\n");
        	printf("\t\t\t\t\t\t\tEnter name: %s\n", newClient.name);
        	printf("\t\t\t\t\t\t\tEnter password: %s\n", newClient.password);
        	printf("\t\t\t\t\t\t\tEnter 11-digit Contact Number: %s\n", newClient.contact);
		}
		
        printf("\t\t\t\t\t\t\tEnter initial deposit (minimum 500): ");
        
        if (scanf("%lf", &newClient.balance) != 1 || newClient.balance < 500) {
            printf("\n\t\t\t\t\t\t\tInitial deposit must be at least 500. Please try again.\n\n");
            inputCtr = 1;
			clearScreen();
        }
    } while (newClient.balance < 500);
	
	inputCtr = 0;
	
    // Add the new client to the list
    clients[clientCount++] = newClient;
    printf("\n\n\t\t\t\t\t\t\tClient registered successfully! Your ID is %d.\n\n", newClient.id);
    printf("\t\t\t\t\t\t\t===================================\n");
	clearScreen();
	
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
	
	do {
		displayHeader();
		
		printf("\t\t\t\t\t\t\t========== LOGIN CLIENT ==========\n\n");
	    printf("\t\t\t\t\t\t\tEnter Client ID: ");
	    scanf("%d", &id);
	
	    for (int i = 0; i < clientCount; i++) {
	        if (clients[i].id == id) {
	            idFound = 1; // ID exists
	            printf("\t\t\t\t\t\t\tEnter Password: ");
	            scanf("%s", password);
	
	            if (strcmp(clients[i].password, password) == 0) {
	                printf("\n\n\t\t\t\t\t\t\tLogin successful. Welcome, %s!\n\n", clients[i].name);
	                printf("\t\t\t\t\t\t\t===================================\n");
					clearScreen();
	                displayClientAction(&clients[i]);
	                return; // Exit after successful login
	            } else {
	                printf("\t\t\t\t\t\t\tInvalid password. Please try again.\n");
	                return; // Exit after invalid password
	            }
	        }
	        
			
	    }
	
	    if (!idFound) {
	        printf("\t\t\t\t\t\t\tInvalid ID. Please try again.\n");
	    }
	} while(!idFound);
}

void displayClientAction(Client *loggedClient) {
    int choice;
    do {
    	displayHeader();
		
		printf("\t\t\t\t\t\t\t======== CLIENT ACTION MENU ========\n\n");
        printf("\t\t\t\t\t\t\t[1] - View Account Info\n");
        printf("\t\t\t\t\t\t\t[2] - Deposit\n");
        printf("\t\t\t\t\t\t\t[3] - Withdraw\n");
        printf("\t\t\t\t\t\t\t[0] - Logout\n");
        printf("\n\t\t\t\t\t\t\tPlease enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            	displayClientInfo(loggedClient);
                break;
            case 2:
                depositAmount(loggedClient);
                break;
            case 3:
            	if(loggedClient->balance <= MIN_BAL) {
					printf("\nError: Your current balance (%.2lf) is the minimum required balance.", loggedClient->balance);
					clearScreen();
					break;
				}
				
                withdrawAmount(loggedClient);
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
		
	do {
		displayHeader();
		
		printf("\t\t\t\t\t\t\t============ DEPOSIT ============\n\n");
		printf("\t\t\t\t\t\t\tEnter the amount to deposit: ");
		if(scanf("%lf", &deposit) != 1 || deposit < MIN_DEPOSIT) {
			fflush(stdin);
			printf("\n\t\t\t\t\t\t\tError: Please enter a positive amount.");
			clearScreen();
		}
	} while(deposit < MIN_DEPOSIT);
	
	loggedClient->balance += deposit;

    // Record transaction
    transactions[transactionCount].clientId = loggedClient->id;
    strcpy(transactions[transactionCount].type, "Deposit");
    transactions[transactionCount].amount = deposit;
    transactionCount++;
    
	printf("\n\n\t\t\t\t\t\t\tYour funds have been safely deposited!");
	printf("\n\n\t\t\t\t\t\t\tUpdated Balance: %.2lf", loggedClient->balance);
    printf("\n\n\t\t\t\t\t\t\t==================================\n");
	clearScreen();
}

void withdrawAmount(Client *loggedClient) {
    double withdrawal;
    
    do {
		printf("\t\t\t\t\t\t\t============ WITHDRAW ============\n\n");
		printf("\t\t\t\t\t\t\tEnter the amount you want to withdraw: ");
		if(scanf("%lf", &withdrawal) != 1 || withdrawal <= 0 || loggedClient->balance - withdrawal < MIN_BAL) {
			fflush(stdin);
			printf("\n\t\t\t\t\t\t\tError: The balance cannot drop below %.2f after withdrawal.", MIN_BAL);
			clearScreen();
		}
	} while(withdrawal <= 0 || loggedClient->balance - withdrawal < MIN_BAL);
	
	client1->balance -= withdrawal;
	
	// Record transaction
    transactions[transactionCount].clientId = loggedClient->id;
    strcpy(transactions[transactionCount].type, "Withdraw");
    transactions[transactionCount].amount = withdrawal;
    transactionCount++;
	
	printf("\n\n\t\t\t\t\t\t\tYour funds have been withdrawn successfully!");
	printf("\n\n\t\t\t\t\t\t\tUpdated Balance: %.l2f", client1->balance);
	printf("\n\n\t\t\t\t\t\t\t==================================\n");
	clearScreen();
    
}

void displayClientInfo(Client *loggedClient) {
	displayHeader();
		
	printf("\t\t\t\t\t\t\t======= CLIENT ACCOUNT INFO =======\n\n");
    printf("\t\t\t\t\t\t\tCLIENT ID: %d\n", loggedClient->id);
    printf("\t\t\t\t\t\t\tPASSWORD: %s\n\n", loggedClient->password);
    printf("\t\t\t\t\t\t\tNAME: %s\n", loggedClient->name);
    printf("\t\t\t\t\t\t\tCONTACT: %s\n", loggedClient->contact);
    printf("\t\t\t\t\t\t\tBALANCE: %.2lf\n", loggedClient->balance);
    
    printf("\n\t\t\t\t\t\t\t===================================\n");
    clearScreen();
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

// Pauses the program and clears the screen after user input
void clearScreen() {
	printf("\n\n\t\t\t\t\t\t\tPress any key to continue . . . ");
	getch();		
	system("cls");
}