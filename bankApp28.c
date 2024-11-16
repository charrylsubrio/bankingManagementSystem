#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 100
#define MAX_CONTACT_NUM 12
#define MIN_BAL 500.00

typedef struct {
	int accNum;
	char clientName[MAX_NAME];
	char contactNum[MAX_CONTACT_NUM];
	float balance;	
} client;

void acceptClient(client *client1);
void displayMenu(int *choice);
void displayClient(client client1);
void depositAmount(client *client1);
void withdrawAmount(client *client1);
void clearScreen();

int main() {
	client client1;
	int choice;
	
	acceptClient(&client1);
	
	do {
		displayMenu(&choice);
	
		switch(choice) {
			case 1: 
				displayClient(client1);
				break;
			case 2:
				depositAmount(&client1);
				printf("\nUpdated Balance: %.2f", client1.balance);
				printf("\n\nPress any key to continue . . . ");
				getch();
				break;
			case 3:
				if(client1.balance <= 500) {
					printf("\nInsufficient balance to withdraw! Minimum balance requirement is %.2f.\n", MIN_BAL);
					printf("\n\nPress any key to continue . . . ");
					getch();
					break;
				}
				withdrawAmount(&client1);
				printf("\nUpdated Balance: %.2f", client1.balance);
				getch();
				break;
		}
		 
	} while(choice != 0);
	
	printf("\n\nPROGRAMMERS: \n");
	printf(" LOMARDA, ISMAEL MARLON\n");	
	printf(" SUBRIO, CHARRYL\n");
	
	return 0;
}

// Accepts client information and validates input
void acceptClient(client *client1) {
	int i, valid, inputCtr = 0;
	
	// Get and validate account number
	do {
		printf("Enter a 5-digit Account Number: ");
		
		if(scanf("%d", &client1->accNum) != 1 || client1->accNum < 10000 || client1->accNum > 99999) {
			fflush(stdin);
			printf("\nError: Please enter a valid 5-digit account number.");
			clearScreen();		
		}
		
		fflush(stdin);
	} while(client1->accNum < 10000 || client1->accNum > 99999);
	
	// Get and validate client name
	do {
		if(inputCtr == 1) {
			printf("Enter a 5-digit Account Number: %d\n", client1->accNum);
		}
		
    	printf("Enter Client Name: ");
    	gets(client1->clientName);

	    client1->clientName[strcspn(client1->clientName, "\n")] = '\0';
		
		valid = 1;
	    for (i = 0; client1->clientName[i] != '\0' && valid; i++) {
		    if (isdigit(client1->clientName[i])) {
		        valid = 0;
		        printf("\nError: Client name cannot contain digits.");
		        clearScreen();
		        break;
		    }
		}
		
		if (valid && strlen(client1->clientName) == 0) {
		    valid = 0;
		    printf("\nError: Client name cannot be empty.");
		    clearScreen();
		}
		
		inputCtr = valid ? 0 : 1;
	} while (!valid);
	
	// Get and validate contact number
    do {
    	if(inputCtr == 1) {
			printf("Enter a 5-digit Account Number: %d\n", client1->accNum);
			printf("Enter Client Name: %s\n", client1->clientName);
		}
    	
    	printf("Enter 11-digit Contact Number: ");
        scanf("%s", client1->contactNum);

        for (i = 0; i < strlen(client1->contactNum); i++) {
            if (!isdigit(client1->contactNum[i]) || strlen(client1->contactNum) != 11) {
            	inputCtr = 1;
                printf("\nError: Please enter a valid 11-digit number without spaces or special characters.");
                clearScreen();
                break;
            }
        }
    } while (strlen(client1->contactNum) != 11);
	
	inputCtr = 0;
	
	// Get and validate outstanding balance
	do {
		if(inputCtr == 1) {
			printf("Enter a 5-digit Account Number: %d\n", client1->accNum);
			printf("Enter Client Name: %s\n", client1->clientName);
			printf("Enter 11-digit Contact Number: %s\n", client1->contactNum);
		}
		
		printf("Enter Outstanding Balance (minimum %.2f): ", MIN_BAL);
		
		if(scanf("%f", &client1->balance) != 1 || client1->balance < MIN_BAL) {
			fflush(stdin);
			inputCtr = 1;
			printf("\nError: Outstanding balance must be at least %.2f.", MIN_BAL);
			clearScreen();
		}
	} while(client1->balance < MIN_BAL);
	
	system("cls");
}

// Display, get and validate menu choice
void displayMenu(int *choice) {
	do {
		printf("==== MAIN MENU ====\n");
		printf("\n [1] - DISPLAY CLIENT INFORMATION");
		printf("\n [2] - DEPOSIT");
		printf("\n [3] - WITHDRAW");
		printf("\n [0] - EXIT");
		printf("\n\nEnter choice: ");
		
		if(scanf("%d", &*choice) != 1 || *choice < 0 || *choice > 3) {
			fflush(stdin);
			printf("\nError: Please enter a number between 0 and 3.\n");
			clearScreen();
		}	
	} while(*choice < 0 || *choice > 3);
}

void displayClient(client client1) {
	system("cls");
	
	printf("==== CLIENT INFORMATION ====");
	printf("\n\nAccount Number: %d", client1.accNum);
	printf("\nClient Name: %s", client1.clientName);
	printf("\nClient Contact Number: %s", client1.contactNum);
	printf("\nOutstanding Balance: %.2f\n", client1.balance);
	
	clearScreen();
}

void depositAmount(client *client1) {
	float amount;
		
	do {
		system("cls");
		
		printf("==== DEPOSIT ====\n\n");
		printf("Amount to deposit: ");
		if(scanf("%f", &amount) != 1 || amount <= 0) {
			fflush(stdin);
			printf("\nError: Please enter a positive amount.");
			clearScreen();
		}
	} while(amount <= 0);
	
	client1->balance += amount;
}

void withdrawAmount(client *client1) {
	float amount;
	
	system("cls");
	
	do {
		printf("==== WITHDRAW ====\n\n");
		printf("Amount to withdraw: ");
		if(scanf("%f", &amount) != 1 || amount <= 0 || client1->balance - amount < MIN_BAL) {
			fflush(stdin);
			printf("\nError: The balance cannot drop below %.2f after withdrawal.\n", MIN_BAL);
			clearScreen();
		}
	} while(amount <= 0 || client1->balance - amount < MIN_BAL);
	
	if(client1->balance - amount >= MIN_BAL) {
		client1->balance -= amount;
	}
}

void clearScreen() {
	printf("\n\nPress any key to continue . . . ");
	getch();		
	system("cls");
}