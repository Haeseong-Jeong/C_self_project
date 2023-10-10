#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "access_database.h"
#include "database.h"


void add_data(char* addname, char* addPIN, char* addaccount, char* addbank, char* addbalance)
{
	if (n_people >= ATM_capa)
	{
		//printf("Capacity is Full. activate reallocate!\n");
		if (reallocate() != 0) return;
	}

	int i = n_people - 1;
	while (i >= 0 && strcmp(addname, ATM[i]->name) < 0)
	{
		*ATM[i + 1] = *ATM[i];
		/*ATM[i + 1]->name = ATM[i]->name;
		ATM[i + 1]->number = ATM[i]->number;
		ATM[i + 1]->email = ATM[i]->email;
		ATM[i + 1]->group = ATM[i]->group;*/

		i--;
	}
	ATM[i + 1]->name = strdup(addname);
	ATM[i + 1]->PIN = strdup(addPIN);
	ATM[i + 1]->account = strdup(addaccount);
	ATM[i + 1]->bank = strdup(addbank);
	ATM[i + 1]->balance = strdup(addbalance);
	n_people++;

	printf("%s add is complete\n\n", addname);
}

void print_data_All()
{
	for (int i = 0; i < ATM_capa; i++)
	{
		printf("Name : %s\n", ATM[i]->name);
		printf("PIN : %s\n", ATM[i]->PIN);
		printf("Account : %s\n", ATM[i]->account);
		printf("Bank : %s\n", ATM[i]->bank);
		printf("Balance : %s\n", ATM[i]->balance);
		printf("-------------------------------------------\n");
	}
	printf("The empty space is %d\n\n", ATM_capa - n_people);
}

int compose_name(char* realname, char* buffname, int limit)
{
	//char* realname[buffer_size];
	if (buffname == NULL)
	{
		printf("Name please\n");
		return -1;
	}
	else
	{
		int idx = 0;
		for (int i = 0; i < strlen(buffname); i++)
		{
			if (buffname[i] != ' ')
			{
				realname[idx] = buffname[i];
				idx++;
			}
		}
		realname[idx] = '\0';
	}
	return 0;
}

void handdle_add(char* addname)
{
	char addPIN[buffer_size] = " "; char addbank[buffer_size] = " "; char addbalance[buffer_size] = " "; char addaccount[buffer_size] = " ";
	printf("PIN : ");
	read_line(stdin, addPIN, buffer_size);

	printf("Account : ");
	read_line(stdin, addaccount, buffer_size);

	printf("Bank : ");
	read_line(stdin, addbank, buffer_size);

	printf("Balance : ");
	read_line(stdin, addbalance, buffer_size);

	add_data(addname, addPIN, addaccount, addbank, addbalance);
	return;
}


int search(char* buf)
{
	int i = 0;
	//char* findtokken = NULL;
	//find pin or name
	if (buf[0] >= '0' && buf[0] <= '9') {
		while (i < n_people)
		{
			if (strcmp(buf, ATM[i]->PIN) == 0)
			{
				return i;
			}
			i++;
		}
	}
	else {
		while (i < n_people)
		{
			if (strcmp(buf, ATM[i]->name) == 0)
			{
				return i;
			}
			i++;
		}
	}

	printf("%s does not exist, Add your information please!\n\n", buf);
	return -1;
}

void print_data(int idx)
{
	if (idx != -1)
	{
		printf("Name : %s\n", ATM[idx]->name);
		printf("PIN : %s\n", ATM[idx]->PIN);
		printf("Bank : %s\n", ATM[idx]->bank);
		printf("Account : %s\n", ATM[idx]->account);
		printf("Balance : %s\n", ATM[idx]->balance);
		return;
	}
}

void remove_data(char* delname)
{
	int idx = search(delname);
	if (idx != -1)
	{
		while (idx + 1 < n_people)
		{
			*ATM[idx] = *ATM[idx + 1];
			idx++;
		}
		memset(ATM[idx], NULL, sizeof(person));
		n_people--;
		printf("%s delete  success\n\n", delname);
		return;
	}
	printf("%s does not exist\n\n", delname);
}

void status()
{
	if (n_people == 0)
	{
		printf("No data\n\n");
		return;
	}
	else
	{
		for (int i = 0; i < n_people; i++)
		{
			printf("Name : %s\n", ATM[i]->name);
			printf("PIN : %s\n", ATM[i]->PIN);
			printf("Bank : %s\n", ATM[i]->bank);
			printf("Account : %s\n", ATM[i]->account);
			printf("Balance : %s\n", ATM[i]->balance);
			printf("-------------------------------------------\n");
		}
		printf("Total %d people\n\n", n_people);
		return;
	}
}