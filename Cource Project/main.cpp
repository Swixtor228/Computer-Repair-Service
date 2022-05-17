#include <iostream>
#include <iomanip>
#include <stdio.h>
#include "Structs.h"

using std::cout;
using std::cin;
using std::endl;

#define ADMIN_FILE_PATH "admin.txt"
#define MANAGERS_FILE_PATH "managers.txt"
#define RECORDS_FILE_PATH "records.txt"

/*=-=-=-=v0.8.1=-=-=-=*/

/*
* ЗАПИСИ *
Записи представляют из себя информацию о возможных услугах, которые добавляют менеджеры и админ.

* Список всех функций *
1) Открыть файл											+
2) Добавить запись										+
3) Редактировать запись									+-
4) Удалить записи										+-
5) Сортировать файл										
6) Просмотр данных										+
7) Настройка отображения (поиск, фильтр, сортировка)	+-
8) Изменение логина и пароля для админа					+
9) Добавить менеджера									+

* РАБОТА С ЗАПИСЯМИ *
Все настройки будут находиться в функции просмотра двнных. Сначала все данные выводятся на консоль, и ниже будут настройки (Поиск, Фильтр, Сортировка)
*/

// Функция, которая позволяет ВОЙТИ В СИСТЕМУ или ВОЙТИ КАК ПОЛЬЗОВАТЕЛЬ
void Login(User& user);
// Панели для разных пользователей
void AdminPanel(User& user);
void ManagerPanel(User& user);
void UserPanel(User& user);
// Основные функции из списка
// * Записи *
void AddRecord();
void EditRecord();
void DeleteRecord();
// * Работа с данными * 
void Search();
void Filter();
void Sort();
// * Отображение данных *
void PrintAllData();	// Выводит содержимое файла
void Menu();
// * Админ функции *
void AddNewManager();
void ChangeAdminDatas(User& user);
// Доп. ф-ции
bool CheckInputData(User& user, int mode);

int main()
{
	setlocale(LC_ALL, "ru");

	FILE* file = fopen(ADMIN_FILE_PATH, "r");

	if (file == NULL)
	{
		file = fopen(ADMIN_FILE_PATH, "w");
		fprintf(file, "%s %s", "admin", "admin");
		fclose(file);
	}
	
	file = fopen(MANAGERS_FILE_PATH, "r");

	if (file == NULL)
	{
		file = fopen(MANAGERS_FILE_PATH, "w");
		fclose(file);
	}

	User user;
	Login(user);

	_fcloseall();
	return 0;
}

void Login(User& user)
{
	int choice = 0;

	do
	{
		system("cls");

		cout << "1. Вход - Администратор" << endl;
		cout << "2. Вход - Менеджер" << endl;
		cout << "3. Вход - Пользователь" << endl;
		cout << endl;
		cout << "0. Выход" << endl;
		cout << "Ваш выбор: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			AdminPanel(user);
			break;
		case 2:
			ManagerPanel(user);
			break;
		case 3:
			UserPanel(user);
			break;
		}
	} while (choice != 0);
}

void AdminPanel(User& user)
{
	if (CheckInputData(user, 1)) {
		// Основная панель
		int choice = 0;

		do
		{
			system("cls");

			cout << "1. Добавить запись" << endl;
			cout << "2. Редактировать запись" << endl;
			cout << "3. Удалить запись" << endl;
			cout << "4. Просмотреть данные" << endl;
			cout << "5. Добавить менеджера" << endl;
			cout << "6. Изменить учетную запись" << endl;
			cout << endl;
			cout << "0. Выйти" << endl;
			cout << "Ваш выбор: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				AddRecord();
				break;
			case 2:
				EditRecord();
				break;
			case 3:
				DeleteRecord();
				break;
			case 4:
				Menu();
				break;
			case 5:
				AddNewManager();
				break;
			case 6:
				ChangeAdminDatas(user);
				break;
			}
		} while (choice != 0);
	}
}

void ManagerPanel(User& user)
{
	if (CheckInputData(user, 0)) {
		// Основная панель
		int choice = 0;

		do
		{
			system("cls");

			cout << "1. Добавить запись" << endl;
			cout << "2. Редактировать запись" << endl;
			cout << "3. Удалить запись" << endl;
			cout << "4. Просмотреть данные" << endl;
			cout << endl;
			cout << "0. Выйти" << endl;
			cout << "Ваш выбор: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				AddRecord();
				break;
			case 2:
				EditRecord();
				break;
			case 3:
				DeleteRecord();
				break;
			case 4:
				Menu();
				break;
			}
		} while (choice != 0);
	}
}

void UserPanel(User& user)
{
	Menu();
}

void AddRecord()
{
	system("cls");
	Record record;
	
	cout << "Номер услуги: ";
	cin >> record.number_of_service;

	if (record.number_of_service == 0)
		return;

	cout << "Поле ФИО" << endl;
	cout << "Фамилия: ";
	cin >> record.fio.second_name;
	cout << "Имя: ";
	cin >> record.fio.first_name;
	cout << "Отчество: ";
	cin >> record.fio.middle_name;

	cout << endl;

	cout << "Поле ДАТА" << endl;
	cout << "День: ";
	cin >> record.date.day;
	cout << "Месяц: ";
	cin >> record.date.month;
	cout << "Год: ";
	cin >> record.date.year;

	cout << endl;

	cout << "Поле ВРЕМЯ" << endl;
	cout << "Час: ";
	cin >> record.time.hour;
	cout << "Минуты: ";
	cin >> record.time.minute;

	cout << endl;

	cout << "Время ремонта: ";
	cin >> record.repair_time;
	cout << "Цена (BYN): ";
	cin >> record.price;

	// Записываем в файл
	FILE* file;

	if ((file = fopen(RECORDS_FILE_PATH, "a")) != NULL)
	{
		fprintf(file, "%u %s %c %c %u/%u/%u %u:%u %u %u\n", 
			record.number_of_service, 
			record.fio.second_name, record.fio.first_name[0], record.fio.middle_name[0],
			record.date.day, record.date.month, record.date.year,
			record.time.hour, record.time.minute,
			record.repair_time, record.price);
		fclose(file);
	}
}

void EditRecord()
{
}

void DeleteRecord()
{
	system("cls");
	// Открываем файл
	FILE* file_records;
	FILE* file_temp_records;

	if ((file_records = fopen(RECORDS_FILE_PATH, "r")) == NULL) {
		cout << "Ошибка: не удалось прочитать файл!" << endl;
		system("pause");
		return;
	}

	char buf[128] = {};
	char* row = nullptr;

	unsigned row_counter = 0;
	unsigned delete_row = 0;

	PrintAllData();

	cout << endl;

	cout << "Введите строчку: ";
	cin >> delete_row;

	if (delete_row == 0)
		return;

	// Копируем данные в буферный файл без нужной строки
	if ((file_temp_records = fopen("temp_records.txt", "w")) != NULL) {
		while ((row = fgets(buf, sizeof(buf), file_records)) && ++row_counter) 
			if (row_counter != delete_row) 
				fputs(row, file_temp_records);
		
		fclose(file_temp_records);
		fclose(file_records);
	}

	// Перезаписываем основной файл records.txt файлом temp_records.txt
	file_records = fopen(RECORDS_FILE_PATH, "w");
	file_temp_records = fopen("temp_records.txt", "r");

	while (row = fgets(buf, sizeof(buf), file_temp_records)) {
		fputs(row, file_records);
	}

	fclose(file_temp_records);
	fclose(file_records);
	remove("temp_records.txt");
}

void Search()
{
	system("cls");

	char search_word[32] = {};

	PrintAllData();
	
	cout << endl;
	cout << "Поиск: ";
	cin >> search_word;

	// Получаем данные из файла
	FILE* file;

	if ((file = fopen(RECORDS_FILE_PATH, "r")) == NULL)
	{
		cout << "Ошибка: файл с записями отсутствует!" << endl;
		system("pause");
		return;
	}

	Record record;

	file = fopen(RECORDS_FILE_PATH, "r");

	system("cls");
	cout << "Результат: " << endl;
	cout << "Номер услуги"
		<< std::setw(15) << "ФИО"
		<< std::setw(23) << "Дата"
		<< std::setw(11) << "Время"
		<< std::setw(20) << "Время ремонта"
		<< std::setw(10) << "Цена" << endl;
	while (!feof(file))
	{
		if (fscanf(file, "%u %s %c %c %u/%u/%u %u:%u %u %u",
			&record.number_of_service,
			&record.fio.second_name, &record.fio.first_name[0], &record.fio.middle_name[0],
			&record.date.day, &record.date.month, &record.date.year,
			&record.time.hour, &record.time.minute,
			&record.repair_time, &record.price) > 0)
		{
			if (strcmp(search_word, record.fio.second_name) == 0) {
				cout << std::setw(5) << record.number_of_service
					<< std::setw(24) << record.fio.second_name << std::setw(2) << record.fio.first_name[0] << ". " << record.fio.middle_name[0] << ". "
					<< std::setw(9) << record.date.day << "/" << record.date.month << "/" << record.date.year
					<< std::setw(5) << record.time.hour << ":" << record.time.minute
					<< std::setw(14) << record.repair_time
					<< std::setw(16) << record.price << endl;
			}
		}
	}
	fclose(file);
	system("pause");
}

void Filter()
{
	system("cls");
	PrintAllData();
	cout << endl;
	cout << "Filter() => :)" << endl;
	system("pause");
}

void Sort()
{
	system("cls");

	FILE* file_records;
	FILE* file_temporary_records;

	char chr;

	file_records = fopen(RECORDS_FILE_PATH, "r");
	file_temporary_records = fopen("temporary.txt", "w");

	chr = fgetc(file_records);
	while (!feof(file_records))
	{
		fputc(chr, file_temporary_records);
		chr = fgetc(file_records);
	}

	fclose(file_records);
	fclose(file_temporary_records);
}

void PrintAllData()
{
	// Получаем данные из файла
	FILE* file;

	if ((file = fopen(RECORDS_FILE_PATH, "r")) == NULL)
	{
		cout << "Ошибка: файл с записями отсутствует!" << endl;
		return;
	}

	Record record;

	file = fopen(RECORDS_FILE_PATH, "r");

	cout << "Номер услуги"
		<< std::setw(15) << "ФИО"
		<< std::setw(23) << "Дата"
		<< std::setw(11) << "Время"
		<< std::setw(20) << "Время ремонта"
		<< std::setw(10) << "Цена" << endl;
	while (!feof(file))
	{
		if (fscanf(file, "%u %s %c %c %u/%u/%u %u:%u %u %u",
			&record.number_of_service,
			&record.fio.second_name, &record.fio.first_name[0], &record.fio.middle_name[0],
			&record.date.day, &record.date.month, &record.date.year,
			&record.time.hour, &record.time.minute,
			&record.repair_time, &record.price) > 0)
		{
			cout << std::setw(5) << record.number_of_service
				<< std::setw(24) << record.fio.second_name << std::setw(2) << record.fio.first_name[0] << ". " << record.fio.middle_name[0] << ". "
				<< std::setw(9) << record.date.day << "/" << record.date.month << "/" << record.date.year
				<< std::setw(5) << record.time.hour << ":" << record.time.minute
				<< std::setw(14) << record.repair_time
				<< std::setw(16) << record.price << endl;
		}
	}
	fclose(file);
}

void Menu()
{
	int choice = 0;

	do
	{
		system("cls");

		PrintAllData();

		cout << endl;
		cout << "1. Поиск" << endl;
		cout << "2. Фильтр" << endl;
		cout << "3. Сортировка" << endl;
		cout << endl;
		cout << "0. Выход" << endl;
		cout << "Ваш выбор: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			Search();
			break;
		case 2:
			Filter();
			break;
		case 3:
			Sort();
			break;
		}
	} while (choice != 0);
}

void AddNewManager()
{
	char login[32];
	char password[32];

	system("cls");
	// Вводим данные для проверки
	cout << "Чтобы выйти, введите 0" << endl;
	cout << "Логин: ";
	cin >> login;

	if (!strcmp(login, "0"))
		return;

	cout << "Пароль: ";
	cin >> password;

	if (!strcmp(password, "0"))
		return;

	// Добавляем эти данные в файл
	FILE* file;

	if ((file = fopen(MANAGERS_FILE_PATH, "a")) != NULL)
	{
		fprintf(file, "%s %s\n", login, password);
		fclose(file);
	}	
}

void ChangeAdminDatas(User& user)
{
	char login[32];
	char password[32];

	system("cls");
	// Вводим данные для проверки
	cout << "Чтобы выйти, введите 0" << endl;
	cout << "Логин: ";
	cin >> login;

	if (!strcmp(login, "0"))
		return;

	cout << "Пароль: ";
	cin >> password;

	if (!strcmp(password, "0"))
		return;

	// Добавляем эти данные в файл
	FILE* file;

	if ((file = fopen(ADMIN_FILE_PATH, "w")) != NULL)
	{
		fprintf(file, "%s %s", login, password);
		fclose(file);
	}
}

bool CheckInputData(User& user, int mode)
{
	// Проверяем наличиие файла
	FILE* file;

	if ((file = fopen((mode == 1) ? ADMIN_FILE_PATH : MANAGERS_FILE_PATH, "r")) == NULL) {
		cout << "Ошибка: файл не найден!" << endl;
		return false;
	}

	do
	{
		system("cls");
		// Запрашиваем логин и пароль
		cout << "Чтобы выйти, введите 0" << endl;

		cout << "Логин: ";
		cin >> user.login;

		if (strcmp(user.login, "0") == 0)
			return false;

		cout << "Пароль: ";
		cin >> user.password;

		if (strcmp(user.password, "0") == 0)
			return false;

		// Проверяем данные в файле
		char file_login[32] = {};
		char file_password[32] = {};

		while (!feof(file)) {
			if (fscanf(file, "%s%s", file_login, file_password) > 0) {
				if (strcmp(user.login, file_login) == 0 && strcmp(user.password, file_password) == 0) {
					fclose(file);
					return true;
				}
			}
		}
	} while (true);
}
