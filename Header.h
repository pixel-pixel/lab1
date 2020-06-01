#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

enum Status { ADMIN, USER };

struct User
{
    char login[20] = {};
    char password[12] = {};
    Status status;
    int id = {};
};

struct Transport
{
    int code;
    char type[15];  
};

struct Station
{
    int code;
    char name[30];
};

void registration();
void enter();
void adminactions();
void admintransport();
void adminstation();
void useractions();