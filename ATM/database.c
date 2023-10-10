#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

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
		add_data(name, PIN, account, bank, balance);
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
