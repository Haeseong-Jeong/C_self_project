#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banking.h"
#include "database.h"

void deposit(int PINI) {
	int money;
	int balance = atoi(ATM[PINI]->balance);
	char* buff[buffer_size];

	printf("How much? ");
	scanf("%d", &money);
	getchar();

	balance = balance + money;
	sprintf(buff, "%d", balance);
	ATM[PINI]->balance = strdup(buff);

	printf("Deposit is complete!\n\n");
	printf("Now your balance is : %s\n\n", buff);
	printf("---------- Thank you ----------\n\n");
}

void withdraw(int PINI) {
	int money;
	int balance = atoi(ATM[PINI]->balance);
	char* buff[buffer_size];
	printf("How much?  ");
	scanf("%d", &money);
	getchar();

	if (balance < money) {
		printf("Your balance is %s, You can't withdraw\n\n", ATM[PINI]->balance);
		return;
		//return -1;
	}
	else {
		balance = balance - money;
		sprintf(buff, "%d", balance);
		ATM[PINI]->balance = strdup(buff);
		printf("Withdraw is complete!\n\n");
		printf("Now your balance is : %s\n\n", buff);
		printf("---------- Thank you ----------\n\n");
		return;
		//return 0;
	}
}

void banking(int PINi)
{
	char* order[buffer_size];

	printf("Now your balance is : %s\n", ATM[PINi]->balance);

	printf("Please type what you want (deposit/withdraw)\n\n");

	while (1) {
		memset(order, NULL, buffer_size);
		read_line(stdin, order, buffer_size);

		if (strcmp(order, "deposit") == 0) {
			deposit(PINi);
			return;
		}
		else if (strcmp(order, "withdraw") == 0) {
			withdraw(PINi);
			return;
		}
		else {
			printf("Please check your typing\n\n");
		}
	}
}

void select_account(int PINi) {

	printf("Is yours?\n");
	printf("[ %s bank : account]  (Y/N)\n\n", ATM[PINi]->bank, ATM[PINi]->account);

	char check = NULL;
	while (1) {
		scanf("%c", &check);
		getchar();
		if (check == 'Y') {
			banking(PINi);
			return;
		}
		else if (check == 'N') {
			printf("Thank you for your visit\n\n");
			return;
		}
		else {
			printf("Please type 'Y' or 'N'\n\n");
			continue;
		}
	}
}