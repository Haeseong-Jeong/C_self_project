#pragma once

void add_data(char* addname, char* addPIN, char* addaccount, char* addbank, char* addbalance);
int compose_name(char* realname,char* buffname, int limit);
void handdle_add(char* addname);
void print_data(int idx);
void print_data_All();
int search(char* buf);
void remove_data(char* delname);
void status();