#pragma once

/*
* ЗАПИСИ *
Данные для пользователя:
1) Номер услуги
2) ФИО мастера (Фамилия И.О.)
4) Дата (дд/мм/гггг)
5) Время (чч:мм)
6) Время ремонта (в днях)
3) Цена (BYN)

* ПРИМЕР ЗАПИСИ *
1 Петров А.В. 21/02/2004 12:54 14 25
*/

struct FIO;
struct Date;
struct Time;
struct User;
struct Record;

struct User
{
	char login[32]		= {};
	char password[32]	= {};
};

struct FIO
{
	// Имя 
	char first_name[32]		= {};
	// Фамилия
	char second_name[32]	= {};
	// Отчество
	char middle_name[32]	= {};
};

struct Date
{
	unsigned day	= 0;
	unsigned month	= 0;
	unsigned year	= 0;
};

struct Time
{
	unsigned hour	= 0;
	unsigned minute	= 0;
};

struct Record
{
	static unsigned number_of_service;
	FIO fio;
	Date date;
	Time time;
	unsigned repair_time = 0;
	unsigned price = 0;
};

unsigned Record::number_of_service = 0;