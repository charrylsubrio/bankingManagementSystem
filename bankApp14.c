#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 100
#define MAX_CONTACT_NUM 12
#define MIN_BAL 500.00

typedef struct {
	int accNum; //5 digits
	char clientName[MAX_NAME];
	char contactNum[MAX_CONTACT_NUM];
	float balance;	
} client;

void acceptClient(client *client1);
void displayMenu(int *choice);
void displayClient(client client1);
void withdrawAmount(client *client1);
void depositAmount(client *client1);

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

void acceptClient(client *client1) {
	int valid, i, inputCtr = 0;
	
	do {
		printf("Account Number (5 digits): ");
		
		if(scanf("%d", &client1->accNum) != 1 || client1->accNum < 10000 || client1->accNum > 99999) {
			fflush(stdin);
			printf("\nInvalid input! Please enter a 5-digit account number.");
			printf("\n\nPress any key to continue . . . ");
			getch();
			system("cls");		
		}
	} while(client1->accNum < 10000 || client1->accNum > 99999);
	fflush(stdin);
	
	
	//gets(client1->clientName);
	//fflush(stdin);

	
	do {
		if(inputCtr == 1) {
			printf("Account Number (5 digits): %d\n", client1->accNum);
		}
		
    printf("Client Name: ");
    gets(client1->clientName);

    // Remove trailing newline, if any
    client1->clientName[strcspn(client1->clientName, "\n")] = '\0';

    valid = 1;
    if (strlen(client1->clientName) == 0) {
        printf("\nClient name cannot be empty.\n\n");
        valid = 0;
        inputCtr = 1;
        printf("Press any key to continue . . . ");
        getch();
        system("cls");
    } else {
        for (int i = 0; client1->clientName[i] != '\0'; i++) {
            if (isdigit(client1->clientName[i]) || strlen(client1->clientName) == 0) {
                valid = 0;
                inputCtr = 1;
                printf("\nClient name cannot contain digits.\n\n");
                printf("Press any key to continue . . . ");
                getch();
                system("cls");
                break;
            }
        }
    }
	} while (!valid);
	
	inputCtr = 0;

//	printf("Contact Number: ");
//	gets(client1->contactNum);
	
	
    do {
    	if(inputCtr == 1) {
			printf("Account Number (5 digits): %d\n", client1->accNum);
			printf("Client Name: %s\n", client1->clientName);
		}
    	
    	printf("Contact Number (11 digits): ");
        scanf("%s", client1->contactNum);

        // Check if the contact number contains only digits
        
        for (i = 0; i < strlen(client1->contactNum); i++) {
            if (!isdigit(client1->contactNum[i]) || strlen(client1->contactNum) != 11) {
            	inputCtr = 1;
                printf("\nInvalid contact number. Please enter an 11-digit number without spaces or special characters.\n\n");
                printf("Press any key to continue . . . ");
                getch();
                system("cls");
                break;
            }
        }
    } while (i < strlen(client1->contactNum) || strlen(client1->contactNum) != 11);
	
	inputCtr = 0;
	
	do {
		if(inputCtr == 1) {
			printf("Account Number (5 digits): %d\n", client1->accNum);
			printf("Client Name: %s\n", client1->clientName);
			printf("Contact Number (11 digits): %s\n", client1->contactNum);
		}
		
		printf("Initial Balance: ");
		
		if(scanf("%f", &client1->balance) != 1 || client1->balance < MIN_BAL) {
			fflush(stdin);
			inputCtr = 1;
			printf("\nInvalid input! Balance must be at least %.2f.\n\n", MIN_BAL);
			printf("Press any key to continue . . . ");
            getch();
            system("cls");
		}
	} while(client1->balance < MIN_BAL);
}

void displayMenu(int *choice) {
	do {
		system("cls");
		
		printf("==== MAIN MENU ====\n");
		printf("\n [1] - DISPLAY CLIENT INFORMATION");
		printf("\n [2] - DEPOSIT");
		printf("\n [3] - WITHDRAW");
		printf("\n [0] - EXIT");
		printf("\n\nEnter choice: ");
		
		if(scanf("%d", &*choice) != 1 || *choice < 0 || *choice > 3) {
			fflush(stdin);
			printf("\nInvalid choice! Please enter a number between 0 and 3.\n");
			printf("\n\nPress any key to continue . . . ");
			getch();
			system("cls");
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
	
	printf("\n\nPress any key to continue . . . ");
	getch();
}

void withdrawAmount(client *client1) {
	float amount;
	
	system("cls");
	
	do {
		printf("==== WITHDRAW ====\n\n");
		printf("Amount to withdraw: ");
		if(scanf("%f", &amount) != 1 || amount <= 0 || client1->balance - amount < MIN_BAL) {
			fflush(stdin);
			printf("\nInvalid amount! The balance cannot drop below %.2f after withdrawal.\n", MIN_BAL);
			printf("\n\nPress any key to continue . . . ");
			getch();		
			system("cls");
		}
	} while(amount <= 0 || client1->balance - amount < MIN_BAL);
	
	if(client1->balance - amount >= MIN_BAL) {
		client1->balance -= amount;
	}
}

void depositAmount(client *client1) {
	float amount;
		
	do {
		system("cls");
		
		printf("==== DEPOSIT ====\n\n");
		printf("Amount to deposit: ");
		if(scanf("%f", &amount) != 1 || amount <= 0) {
			fflush(stdin);
			printf("\nInvalid input! Please enter a positive amount.\n\n");
			printf("Press any key to continue . . . ");
			getch();
			system("cls");
		}
	} while(amount <= 0);
	
	client1->balance += amount;
}