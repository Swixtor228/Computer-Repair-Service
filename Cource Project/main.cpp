#include <iostream>
#include <iomanip>
#include <stdio.h>
#include "Structs.h"

using std::cout;
using std::cin;
using std::endl;

#define FILE_ADMIN_PATH		"admin.txt"
#define FILE_MANAGERS_PATH	"managers.txt"
#define FILE_RECORDS_PATH	"records.txt"
#define FILE_TEMP_PATH		"temp_records.txt"

#define FORMAT_DATA			"%s %s"
#define FORMAT_RECORDS		"%u %s %s %c %c %u/%u/%u %u:%u %u %u"
#define FORMAT_RECORDS_END	"%u %s %s %c %c %u/%u/%u %u:%u %u %u\n"

/*=-=-=-=v1.0=-=-=-=*/

// Функция, которая позволяет ВОЙТИ В СИСТЕМУ или ВОЙТИ КАК ПОЛЬЗОВАТЕЛЬ
void Login(User& user);
// Панели для разных пользователей
void AdminPanel(User& user);
void ManagerPanel(User& user);
void UserPanel(User& user);
// Основные функции из списка
// * Записи *
Record AddRecord(const char* _FileName = FILE_RECORDS_PATH, const char* _Mode = "a");
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
void WriteRecordToFile(FILE* _FileObj, Record& record, bool _CloseFile);
FILE* OpenFile(const char* _FileName, const char* _Mode);
void PrintHeader();
void PrintRecord(Record& record);

int main()
{
	setlocale(LC_ALL, "ru");

	FILE* file = fopen(FILE_ADMIN_PATH, "r");

	if (file == NULL)
	{
		file = fopen(FILE_ADMIN_PATH, "w");
		fprintf(file, FORMAT_DATA, "admin", "admin");
		fclose(file);
	}
	
	file = fopen(FILE_MANAGERS_PATH, "r");

	if (file == NULL)
	{
		file = fopen(FILE_MANAGERS_PATH, "w");
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

Record AddRecord(const char* _FileName, const char* _Mode)
{
	system("cls");
	Record record;
	
	cout << "Номер услуги: ";
	cin >> record.number_of_service;

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

	if (_FileName != nullptr) {
		FILE* file = OpenFile(_FileName, _Mode);
		WriteRecordToFile(file, record, false);
	} 
	
	return record;
}

void EditRecord()
{
	FILE* file_records = OpenFile(FILE_RECORDS_PATH, "r");

	system("cls");

	Record record;
	Record temp_record;

	unsigned required_line = 0;
	unsigned line_counter = 0;

	PrintAllData();

	cout << endl;
	cout << "Введите номер строки: ";
	cin >> required_line;

	if (required_line == 0)
		return;

	FILE* file_temp_records = OpenFile(FILE_TEMP_PATH, "w");

	while (!feof(file_records))
	{
		if (fscanf(file_records, FORMAT_RECORDS,
			&record.number_of_service, &record.service_name,
			&record.fio.second_name, &record.fio.first_name[0], &record.fio.middle_name[0],
			&record.date.day, &record.date.month, &record.date.year,
			&record.time.hour, &record.time.minute,
			&record.repair_time, &record.price) > 0) 
		{
			line_counter++;

			if (line_counter == required_line) {
				temp_record = AddRecord(nullptr);
				WriteRecordToFile(file_temp_records, temp_record, false);
			}

			if (line_counter != required_line) {
				WriteRecordToFile(file_temp_records, record, false);
			}
		}
	}

	fclose(file_temp_records);
	fclose(file_records);

	// Перезаписываем основной файл records.txt файлом temp_records.txt
	file_records = OpenFile(FILE_RECORDS_PATH, "w");
	file_temp_records = OpenFile(FILE_TEMP_PATH, "r");

	char buf[128] = {};
	char* row = nullptr;

	while (row = fgets(buf, sizeof(buf), file_temp_records)) {
		fputs(row, file_records);
	}

	fclose(file_temp_records);
	fclose(file_records);
	remove(FILE_TEMP_PATH);
}

void DeleteRecord()
{
	system("cls");
	// Открываем файл
	FILE* file_records = OpenFile(FILE_RECORDS_PATH, "r");
	FILE* file_temp_records = OpenFile(FILE_TEMP_PATH, "w");

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
	if ((file_temp_records = fopen(FILE_TEMP_PATH, "w")) != NULL) {
		while ((row = fgets(buf, sizeof(buf), file_records)) && ++row_counter) 
			if (row_counter != delete_row) 
				fputs(row, file_temp_records);
		
		fclose(file_temp_records);
		fclose(file_records);
	}

	// Перезаписываем основной файл records.txt файлом temp_records.txt
	file_records = fopen(FILE_RECORDS_PATH, "w");
	file_temp_records = fopen(FILE_TEMP_PATH, "r");

	while (row = fgets(buf, sizeof(buf), file_temp_records)) {
		fputs(row, file_records);
	}

	fclose(file_temp_records);
	fclose(file_records);
	remove(FILE_TEMP_PATH);
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
	FILE* file = OpenFile(FILE_RECORDS_PATH, "r");

	Record record;

	system("cls");
	cout << "Результат: " << endl;
	PrintHeader();

	while (!feof(file))
	{
		if (fscanf(file, FORMAT_RECORDS,
			&record.number_of_service, &record.service_name,
			&record.fio.second_name, &record.fio.first_name[0], &record.fio.middle_name[0],
			&record.date.day, &record.date.month, &record.date.year,
			&record.time.hour, &record.time.minute,
			&record.repair_time, &record.price) > 0)
		{
			if ((strcmp(search_word, record.fio.second_name) == 0) || (strcmp(search_word, record.service_name) == 0)) {
				PrintRecord(record);
			}
		}
	}
	fclose(file);
	system("pause");
}

void Filter()
{
	// Считываем кол-во строчек
	FILE* file_records = OpenFile(FILE_RECORDS_PATH, "r");
	Record record;

	system("cls");

	int price = 0;

	PrintAllData();

	cout << endl;
	cout << "Введите сумму: ";
	cin >> price;

	system("cls");

	cout << "Результат: " << endl;
	PrintHeader();

	while (!feof(file_records))
	{
		if (fscanf(file_records, FORMAT_RECORDS,
			&record.number_of_service, &record.service_name,
			&record.fio.second_name, &record.fio.first_name[0], &record.fio.middle_name[0],
			&record.date.day, &record.date.month, &record.date.year,
			&record.time.hour, &record.time.minute,
			&record.repair_time, &record.price) > 0)
		{
			if (price >= record.price) {
				PrintRecord(record);
			}
		}
	}

	fclose(file_records);
	cout << endl;
	system("pause");
}

void Sort()
{
	// Считываем кол-во строчек
	FILE* file_records = OpenFile(FILE_RECORDS_PATH, "r");

	char buf[128] = {};
	char* row = nullptr;

	unsigned row_counter = 0;

	while (row = fgets(buf, sizeof(buf), file_records))
		row_counter++;
	fclose(file_records);

	// Записываем массив records
	file_records = OpenFile(FILE_RECORDS_PATH, "r");

	Record* records = new Record[row_counter];
	Record record;

	for (unsigned i = 0; i < row_counter; i++)
	{
		if (fscanf(file_records, FORMAT_RECORDS,
			&record.number_of_service, &record.service_name,
			&record.fio.second_name, &record.fio.first_name[0], &record.fio.middle_name[0],
			&record.date.day, &record.date.month, &record.date.year,
			&record.time.hour, &record.time.minute,
			&record.repair_time, &record.price) > 0)
		{
			records[i] = record;
		}
	}

	// Сортируем массив
	Record temp_record;

	for (int i = 0; i < row_counter - 1; i++)
	{
		for (int j = 0; j < row_counter - 1; j++)
		{
			if (records[j + 1].price < records[j].price) {
				temp_record = records[j + 1];
				records[j + 1] = records[j];
				records[j] = temp_record;
			}
		}
	}

	FILE* file_temp_sorted_records = OpenFile(FILE_RECORDS_PATH, "w");
	// Перезапиисываем основной файл
	for (unsigned i = 0; i < row_counter; i++)
	{
		WriteRecordToFile(file_temp_sorted_records, records[i], false);
	}

	fclose(file_records);
	fclose(file_temp_sorted_records);

	system("cls");

	cout << "Файл успешно сортирован!" << endl;
	system("pause");
}

void PrintAllData()
{
	// Получаем данные из файла
	FILE* file = OpenFile(FILE_RECORDS_PATH, "r");

	Record record;

	PrintHeader();
	while (!feof(file))
	{
		if (fscanf(file, FORMAT_RECORDS,
			&record.number_of_service, &record.service_name,
			&record.fio.second_name, &record.fio.first_name[0], &record.fio.middle_name[0],
			&record.date.day, &record.date.month, &record.date.year,
			&record.time.hour, &record.time.minute,
			&record.repair_time, &record.price) > 0)
		{
			PrintRecord(record);
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

	if ((file = fopen(FILE_MANAGERS_PATH, "a")) != NULL)
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

	if ((file = fopen(FILE_ADMIN_PATH, "w")) != NULL)
	{
		fprintf(file, FORMAT_DATA, login, password);
		fclose(file);
	}
}

bool CheckInputData(User& user, int mode)
{
	// Проверяем наличиие файла
	FILE* file;

	if ((file = fopen((mode == 1) ? FILE_ADMIN_PATH : FILE_MANAGERS_PATH, "r")) == NULL) {
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
			if (fscanf(file, FORMAT_DATA, file_login, file_password) > 0) {
				if (strcmp(user.login, file_login) == 0 && strcmp(user.password, file_password) == 0) {
					fclose(file);
					return true;
				}
			}
		}
	} while (true);
}

void WriteRecordToFile(FILE* _FileObj, Record& record, bool _CloseFile)
{
	fprintf(_FileObj, FORMAT_RECORDS_END,
		record.number_of_service, record.service_name,
		record.fio.second_name, record.fio.first_name[0], record.fio.middle_name[0],
		record.date.day, record.date.month, record.date.year,
		record.time.hour, record.time.minute,
		record.repair_time, record.price);

	if (_CloseFile)
		fclose(_FileObj);
}

FILE* OpenFile(const char* _FileName, const char* _Mode)
{
	FILE* _FileObj;

	if ((_FileObj = fopen(_FileName, _Mode)) == NULL) {
		cout << "Ошибка: не удалось прочитать файл!" << endl;
		system("pause");
		return nullptr;
	}

	return _FileObj;
}

void PrintHeader()
{
	printf("%s %*s %*s %*s %*s %*s %*s\n", "Услуга", 13, "Описание", 17, "ФИО", 17, "Дата", 12, "Время", 11, "Ремонт", 12, "Сумма");
}

void PrintRecord(Record& record)
{	
	printf("%03u", record.number_of_service);
	printf("%*s", 20, record.service_name);
	printf("%*s %c. %c.     ", 15, record.fio.second_name, record.fio.first_name[0], record.fio.middle_name[0]);
	printf("%02u/%02u/%04u     ", record.date.day, record.date.month, record.date.year);
	printf("%02u:%02u", record.time.hour, record.time.minute);
	printf("%*u", 10, record.repair_time);
	printf("%*u", 15, record.price);
	printf("\n");
}