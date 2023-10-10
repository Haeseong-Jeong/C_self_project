#include "access_database.h"
#include "banking.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void line_command();

void line_command()
{
	char inputline[buffer_size];//명령입력줄
	char namestr[buffer_size];//이름받아쓰기
	char PIN[buffer_size];
	char* command; char* buf1; char* buf2;

	while (1)
	{
		memset(inputline, NULL, buffer_size);
		memset(namestr, NULL, buffer_size);
		memset(PIN, NULL, buffer_size);

		//command string input
		printf("$  ");
		if (read_line(stdin, inputline, buffer_size) <= 0) continue;

		//command slice
		command = strtok(inputline, " ");
		if (command == NULL) continue;

		// command가 정상적으로 입력 시작

		if (strcmp(command, "Insert") == 0)	// Insert person 000000000
		{
			buf1 = strtok(NULL, " "); //person
			buf2 = strtok(NULL, "\n"); // get 000000000
			if (buf1 == NULL)
			{
				printf("Please type 'Insert person'\n\n");
				continue;
			}

			else if (buf2 == NULL)
			{
				printf("Check your PIN number please!\n\n");
				continue;
			}

			else
			{
				int findPINi = search(buf2);
				if (findPINi != -1) {
					//PIN is exist ---
					select_account(findPINi);
				}
				continue;
			}
		}

		if (strcmp(command, "add") == 0)	// add name
		{
			buf1 = strtok(NULL, "\n");
			if (compose_name(namestr,buf1, buffer_size) == 0)
			{
				handdle_add(namestr); continue;
			}
			else continue;
		}

		else if (strcmp(command, "find") == 0)	// find name
		{
			buf1 = strtok(NULL, "\n");
			if (compose_name(namestr, buf1, buffer_size) == 0)
			{
				int findnamei = search(namestr);
				if (findnamei != -1)
				{
					print_data(findnamei);
				};
				//find(namestr); continue;
			}
			else continue;
		}

		else if (strcmp(command, "delete") == 0)	// delete name
		{
			buf1 = strtok(NULL, "\n");
			if (compose_name(namestr, buf1, buffer_size) == 0)
			{
				remove_data(namestr); continue;
			}
			else continue;
		}

		else if (strcmp(command, "status") == 0)	// status
		{
			status(); continue;
		}

		else if (strcmp(command, "printATM") == 0)	// status
		{
			print_data_All(); continue;
		}

		else if (strcmp(command, "load") == 0)	// load filename
		{
			buf1 = strtok(NULL, " ");
			if (buf1 == NULL)
			{
				printf("Need file name\n");
				continue;
			}
			load(buf1); continue;
		}

		else if (strcmp(command, "save") == 0)	// save filename
		{
			save(); continue;//save(filename)
		}

		else if (strcmp(command, "exit") == 0)	// exit
		{
			free(ATM);
			printf("\nProgram is terminated\n"); return;
		}
		else
		{
			printf("----------Invaild command, Check your input----------\n");
			printf("  Insert person\n  add name\n  find name\n  delete name\n  status\n  load finename\n  save\n  exit\n\n");
			printf("----------Invaild command, Check your input----------\n");
		}
	}
}

person** ATM;
int n_people = 0;
int ATM_capa = CAPACITY;

int main()
{
	init_ATM();

	line_command();
	return 0;
}