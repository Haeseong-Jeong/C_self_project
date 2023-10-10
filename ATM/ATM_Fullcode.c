//verson5 구조체 포인터변수로 배열을 동적으로 할당받아 크기 늘릴 수있게 구현 
// 배열 동적할당하고 배열요소는 구조체 포인터이다. 함수를 옮겨다닐때 포인터로 값을 복사하기때문에 메모리 최적화 좋음
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 3
#define buffer_size 50
#define PIN_size 9
#define Acc_size 7

typedef struct _person
{
	char* name;
	char* PIN;
	char* account;
	char* bank;
	char* balance;
}person;

person** ATM;//struct point array
int n_people = 0;
int ATM_capa = CAPACITY;
char* delim = " ";

//database
void init_ATM();
int reallocate();
void load(char* filename);
void save();
int read_line(FILE* fp, char* str, int limitlen);

//access_database
void add(char* addname, char* addPIN, char* addaccount, char* addbank, char* addbalance);
int compose_name(char* namestr, int limit);
void handdle_add(char* addname);
void print_data(int idx);
void print_data_All();
int search(char* buf);
void remove_data(char* delname);
void status();

//banking
void select_account(int PINi);
void banking(int PINi);
void deposit(int PINi);
void withdraw(int PINi);

//main
void line_command();

void init_ATM()
{
	ATM = (person**)malloc(sizeof(person*) * ATM_capa);
	for (int i = 0; i < ATM_capa; i++)
	{
		ATM[i] = (person*)malloc(sizeof(person));
		memset(ATM[i], NULL, sizeof(person));
	}
}

int reallocate()
{
	ATM_capa = ATM_capa * 2;
	person** newATM;
	newATM = (person**)malloc(sizeof(person*) * ATM_capa);
	
	for (int i = 0; i < ATM_capa; i++)
	{
		newATM[i] = (person*)malloc(sizeof(person));
		memset(newATM[i], NULL, sizeof(person));
	}

	if (newATM != NULL)
	{
		for (int i = 0; i < n_people; i++)
		{
			*newATM[i] = *ATM[i];
		}
		free(ATM);
		ATM = newATM;
		return 0;
	}
	free(newATM);
	printf("Realloc Failed!\n");
	return -1;
}

void load(char* filename)
{
	char buff[buffer_size];
	char* name; char* PIN; char* account; char* bank; char* balance;

	FILE* fp = fopen(filename, "r");//파일이 없으면 null ?
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}
	//fscanf(파일포인터, 서식, 변수의 주소1, 변수의주소 2,....)
	while (1)
	{
		if (read_line(fp, buff, buffer_size) <= 0) break;
		name = strtok(buff, "#");
		PIN = strtok(NULL, "#");
		account = strtok(NULL, "#");
		bank = strtok(NULL, "#");
		balance = strtok(NULL, "#");
		add(name, PIN, account, bank, balance);
	}
	fclose(fp);
	printf("Load completed\n\n");
}

void save()
{
	char filename[buffer_size];
	printf("File name : ");
	read_line(stdin, filename, buffer_size);
	//scanf("%s", filename); -> enter buffer is exist -> have to remove '\n' 
	int i = 0;

	FILE* fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Open failed\n");
	}
	for (int i = 0; i < n_people; i++)
	{
		fprintf(fp, "%s#%s#%s#%s#%s\n", ATM[i]->name, ATM[i]->PIN, ATM[i]->account, ATM[i]->bank, ATM[i]->balance);
	}
	fclose(fp);
	printf("Save completed\n\n");
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

int compose_name(char* realname, int limit)
{
	char* buff = strtok(NULL, "\n");
	if (buff == NULL)
	{
		printf("Name please\n");
		return -1;
	}
	else
	{
		int idx = 0;
		for (int i = 0; i < strlen(buff); i++)
		{
			if (buff[i] != ' ')
			{
				realname[idx] = buff[i];
				idx++;
			}
		}
		realname[idx] = '\0';
	}
	return 0;
}

int read_line(FILE* fp, char* str, int limitlen)
{
	int ch = 0, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
	{
		if (i < limitlen)
		{
			str[i++] = ch;
		}
	}

	str[i] = '\0';
	return i;
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

	add(addname, addPIN, addaccount, addbank, addbalance);
	return;
}

void add(char* addname, char* addPIN, char* addaccount, char* addbank, char* addbalance)
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
		while (idx + 1 < n)
		{
			*ATM[idx] = *ATM[idx + 1];
			idx++;
		}
		memset(ATM[idx], NULL, sizeof(person));
		n--;
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




void deposit(int PINI) {
	int money;
	int balance = atoi(ATM[PINI]->balance);
	char* buff[buffer_size];

	printf("  How much? ");
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
	printf("  How much?  ");
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
		command = strtok(inputline, delim);
		if (command == NULL) continue;

		// command가 정상적으로 입력 시작

		if (strcmp(command, "Insert") == 0)	// Insert person 000000000
		{
			buf1 = strtok(NULL, delim); //person
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
			//compose_name(namestr, buffer_size);
			if (compose_name(namestr, buffer_size) == 0)
			{
				handdle_add(namestr); continue;
			}
			else continue;
		}

		else if (strcmp(command, "find") == 0)	// find name
		{
			if (compose_name(namestr, buffer_size) == 0)
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
			if (compose_name(namestr, buffer_size) == 0)
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
			buf1 = strtok(NULL, delim);
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

int main()
{
	init_ATM();

	line_command();
	return 0;
}