#pragma once

/*
* ������ *
������ ��� ������������:
1) ����� ������
2) ��� ������� (������� �.�.)
4) ���� (��/��/����)
5) ����� (��:��)
6) ����� ������� (� ����)
3) ���� (BYN)

* ������ ������ *
1 ������ �.�. 21/02/2004 12:54 14 25
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
	// ���
	char first_name[32]		= {};
	// �������
	char second_name[32]	= {};
	// ��������
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