#include <iostream>
#include "Structs.h"

using std::cout;
using std::cin;
using std::endl;

#define ADMIN_FILE_PATH "admin.txt"
#define MANAGERS_FILE_PATH "managers.txt"

/*=-=-=-=v0.6=-=-=-=*/

/*
* ЗАПИСИ *
Записи представляют из себя информацию о возможных услугах, которые добавляют менеджеры и админ.

* Список всех функций *
1) Открыть файл											
2) Добавить запись										+-
3) Редактировать запись									+-
4) Удалить записи										+-
5) Сортировать файл										
6) Просмотр данных										+-
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
// * Записи
void AddRecord(User& user);
void EditRecord(User& user);
void DeleteRecord(User& user);
// * Отображение данных
void ViewSettings(User& user);
void PrintAllData(User& user);
// * Админ функции
void AddNewManager();
void ChangeAdminDatas(User& user);

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
	// Проверяем наличиие файла
	FILE* file;

	if ((file = fopen(ADMIN_FILE_PATH, "r")) == NULL)
	{
		cout << "Ошибка: файл не найден!" << endl;
		return;
	}

	do
	{
		system("cls");
		// Запрашиваем логин и пароль
		cout << "Чтобы выйти, введите 0" << endl;

		cout << "Логин: ";
		cin >> user.login;

		if (strcmp(user.login, "0") == 0)
			return;

		cout << "Пароль: ";
		cin >> user.password;

		if (strcmp(user.password, "0") == 0)
			return;

		// Проверяем данные в файле
		char file_login[32]		= {};
		char file_password[32]	= {};

		while (!feof(file))
		{
			if (fscanf(file, "%s%s", file_login, file_password) > 0)
			{
				if (strcmp(user.login, file_login) == 0 && strcmp(user.password, file_password) == 0)
				{
					fclose(file);
					// Основная панель
					int choice = 0;

					do
					{
						system("cls");

						cout << "1. Открыть файл" << endl;
						cout << "2. Добавить запись" << endl;
						cout << "3. Редактировать запись" << endl;
						cout << "4. Удалить запись" << endl;
						cout << "5. Сортировать файл" << endl;
						cout << "6. Просмотреть данные" << endl;
						cout << "7. Настройки отображения" << endl;
						cout << "8. Добавить менеджера" << endl;
						cout << "9. Изменить учетную запись" << endl;
						cout << endl;
						cout << "0. Выйти" << endl;
						cout << "Ваш выбор: ";
						cin >> choice;

						switch (choice)
						{
						case 1:

							break;
						case 2:

							break;
						case 3:

							break;
						case 4:

							break;
						case 5:

							break;
						case 6:

							break;
						case 7:

							break;
						case 8:
							AddNewManager();
							break;
						case 9:
							ChangeAdminDatas(user);
							break;
						}

					} while (choice != 0);
					return;
				}
			}
		}	
	} while (true);
}

void ManagerPanel(User& user)
{
	// Проверяем наличиие файла
	FILE* file;

	if ((file = fopen(MANAGERS_FILE_PATH, "r")) == NULL)
	{
		cout << "Ошибка: файл не найден!" << endl;
		return;
	}

	do
	{
		system("cls");
		// Запрашиваем логин и пароль
		cout << "Чтобы выйти, введите 0" << endl;

		cout << "Логин: ";
		cin >> user.login;

		if (strcmp(user.login, "0") == 0)
			return;

		cout << "Пароль: ";
		cin >> user.password;

		if (strcmp(user.password, "0") == 0)
			return;

		// Проверяем данные в файле
		char file_login[32] = {};
		char file_password[32] = {};

		while (!feof(file))
		{
			if (fscanf(file, "%s%s", file_login, file_password) > 0)
			{
				if (strcmp(user.login, file_login) == 0 && strcmp(user.password, file_password) == 0)
				{
					fclose(file);
					// Основная панель
					int choice = 0;

					do
					{
						system("cls");

						cout << "1. Открыть файл" << endl;
						cout << "2. Добавить запись" << endl;
						cout << "3. Редактировать запись" << endl;
						cout << "4. Удалить запись" << endl;
						cout << "5. Сортировать файл" << endl;
						cout << "6. Просмотреть данные" << endl;
						cout << "7. Настройки отображения" << endl;
						cout << endl;
						cout << "0. Выйти" << endl;
						cout << "Ваш выбор: ";
						cin >> choice;

						switch (choice)
						{
						case 1:

							break;
						case 2:

							break;
						case 3:

							break;
						case 4:

							break;
						case 5:

							break;
						case 6:

							break;
						case 7:

							break;
						}
					} while (choice != 0);	
					return;
				}
			}
		}
	} while (true);	
}

void UserPanel(User& user)
{
	int choice;

	do
	{
		system("cls");

		cout << "1. Открыть файл с данными" << endl;
		cout << "2. Просмотреть все данные" << endl;
		cout << "3. Настройка отображения" << endl;
		cout << endl;
		cout << "0. Выход" << endl;
		cout << "Ваш выбор: ";
		cin >> choice;

		switch (choice)
		{
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		}
	} while (choice != 0);
}

void AddRecord(User& user)
{
	
}

void EditRecord(User& user)
{
}

void DeleteRecord(User& user)
{
}

void ViewSettings(User& user)
{
}

void PrintAllData(User& user)
{
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
