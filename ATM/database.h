#pragma once

#include <stdio.h>
#define CAPACITY 3
#define buffer_size 50

typedef struct _person
{
	char* name;
	char* PIN;
	char* account;
	char* bank;
	char* balance;
}person;

//person** ATM;//struct point array
//int n_people = 0;
//int ATM_capa = CAPACITY;

extern person** ATM;
extern int n_people;
extern int ATM_capa;

void init_ATM();
int reallocate();
void load(char* filename);
void save();
int read_line(FILE* fp, char* str, int limitlen);