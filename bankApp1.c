#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_NAME 100
#define MIN_BAL 500.00

typedef struct {
	int accNum; //5 digits
	char clientName[MAX_NAME];
	char contactNum[12];
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
				printf("After: %.2f", client1.balance);
				printf("\n\nPress any key to continue ... ");
				getch();
				break;
			case 3:
				if(client1.balance <= 500) {
					printf("\n\nInvalid!");
					printf("\n\nPress any key to continue ... ");
					getch();
					break;
				}
				withdrawAmount(&client1);
				printf("After: %.2f", client1.balance);
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
	printf("Account Number: ");
	scanf("%d", &client1->accNum);
	fflush(stdin);
	
	printf("Client Name: ");
	gets(client1->clientName);
	fflush(stdin);

	printf("Contact Number: ");
	gets(client1->contactNum);
	
	do {
		printf("Initial Balance: ");
		
		if(scanf("%f", &client1->balance) != 1 || client1->balance < MIN_BAL) {
			fflush(stdin);
			printf("\nInvalid input! Please enter a number greater than or equal to %.2f.\n\n", MIN_BAL);
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
			printf("\nInvalid input!");
			printf("\n\nPress any key to continue ... ");
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
	
	printf("\n\nPress any key to continue ... ");
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
			printf("\nInvalid input!");
			printf("\n\nPress any key to continue");
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
			printf("\nInvalid input!\n\n");
			printf("Press any key to continue ... ");
			getch();
			system("cls");
		}
	} while(amount <= 0);
	
	client1->balance += amount;
}