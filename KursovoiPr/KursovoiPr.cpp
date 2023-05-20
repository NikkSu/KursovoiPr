#include <iostream>
#include <fstream>
#include <string>
#include<Windows.h>
#include <sstream>
#include <iomanip>
#include <locale>
#include <cctype>
using namespace std;
const int MAX_ATTEMPTS = 3;  // Максимальное количество попыток
struct User
{
	string login;
	string password;
	bool isAdmin;
	bool isBanned;
	float money;
};
struct shoes {
	string name;
	float price;
	string manufacturer;
	int quantity;
	int size;


};
void DeleteConsole() {
	cout << "\n\n\nНажмите enter чтобы продолжить..." << endl;
	cin.get();
	system("cls");// 

}
void unblockUser() {

	string username;
	cout << "Введите пользователя которого хотите разблокировать: ";
	cin >> username;
	// Открытие файла для чтения и записи
	fstream file("users.txt");

	// Поиск пользователя в файле
	string fileUsername, filePassword;
	bool userFound = false;
	while (file >> fileUsername >> filePassword) {
		if (fileUsername == username) {
			userFound = true;
			break;
		}
	}

	if (userFound) {
		// Изменение значения поля isBanned
		User user;
		user.login = fileUsername;
		user.password = filePassword;
		user.isAdmin = false;
		user.isBanned = false;

		// Переход на позицию в файле, соответствующую найденному пользователю
		file.seekp(file.tellg());

		// Запись обновленной информации в файл
		file << " " << user.isAdmin << " " << user.isBanned << endl;

		cout << "Аккаунт \"" << user.login << "\" разблокирован." << endl;
	}
	else {
		cout << "Пользователь с логином \"" << username << "\" не найден." << endl;
	}

	// Закрытие файла
	file.close();

	DeleteConsole();
}
void viewUsers() {
	ifstream inputFile("users.txt");
	if (!inputFile) {
		cout << "Ошибка открытия файла." << endl;
		return;
	}

	cout << left << setw(30) << "| Имя пользователя" << " | " << setw(30) << "Пароль"
		<< " | " << setw(15) << "Администратор" << " | " << setw(15) << "Заблокирован"
		<< " | " << setw(15) << "Баланс" << " |" << endl;
	cout << setfill('-') << setw(119) << "-" << setfill(' ') << endl;

	string username, password;
	bool isAdmin, isBanned;
	double balance;

	while (inputFile >> username >> password >> isAdmin >> isBanned >> balance) {
		cout << left << setw(30) << "| " + username << " | " << setw(30) << password
			<< " | " << setw(15) << (isAdmin ? "Да" : "Нет") << " | " << setw(15)
			<< (isBanned ? "Да" : "Нет") << " | " << setw(15) << fixed << setprecision(2)
			<< balance << " |" << endl;
		cout << setfill('-') << setw(119) << "-" << setfill(' ') << endl;
	}

	inputFile.close(); string a;
	getline(cin, a);
	DeleteConsole();
}
void deleteUser() {
	string username;

	cout << "Введите пользователя которого хотите удалить: ";
	cin >> username;
	ifstream inputFile("users.txt");
	ofstream outputFile("temp.txt", ios::app);
	string fileUsername, filePassword;
	bool fileIsAdmin, fileIsBanned;
	float fileMoney;
	bool userFound = false;
	User person;
	// Копирование всех записей кроме той, которую необходимо удалить, в новый временный файл
	while (inputFile >> fileUsername >> filePassword >> fileIsAdmin >> fileIsBanned >> fileMoney) {
		if (fileUsername != username) {
			outputFile << fileUsername << " " << filePassword << " " << fileIsAdmin << " " << fileIsBanned << " " << fileMoney << endl;
		}
		else {
			userFound = true;
		}
	}

	inputFile.close();
	outputFile.close();

	// Перезапись исходного файла новым файлом с удаленной записью, если запись найдена
	if (userFound) {
		remove("users.txt");
		rename("temp.txt", "users.txt");
		cout << "Пользователь успешно удален." << endl;
		DeleteConsole();
	}
	else {
		remove("temp.txt");
		cout << "Пользователь не найден." << endl;
		DeleteConsole();
	}
}
void banUser() {
	string username;
	cout << "Введите пользователя которого хотите заблокировать: ";
	cin >> username;
	User user;
	fstream file("users.txt");
	string fileUsername, filePassword;
	bool fileIsAdmin, fileIsBanned;
	float fileMoney;
	bool userFound = false;

	// Поиск пользователя и установка флага isBanned в true
	while (file >> fileUsername >> filePassword >> fileIsAdmin >> fileIsBanned >> fileMoney) {
		if (fileUsername == username) {
			userFound = true;

			user.login = fileUsername;
			user.password = filePassword;
			user.isAdmin = false;
			user.isBanned = true;
			user.money = fileMoney;

			// Запись измененных данных в файл



			break;
		}

	}



	file.close();
	if (userFound) {
		fstream file1("users.txt");


		while (file1 >> fileUsername >> filePassword) {
			if (fileUsername == username) {




				// Запись измененных данных в файл
				file.seekg(file.tellg());
				file << " " << user.isAdmin << " " << 1 << " " << user.money << endl;


				break;
			}

		}
		file1.close();
	}




	// Вывод сообщения об ошибке, если пользователь не найден
	if (!userFound) {
		cout << "Пользователь не найден." << endl;
		DeleteConsole();
	}
	else {
		cout << "Пользователь " << username << " заблокирован." << endl;
		getchar();
		DeleteConsole();
	}
}

shoes* readShoesFromFile(string fileName, int& numToys) {
	ifstream inFile(fileName);
	if (!inFile.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return nullptr;
	}

	// Получаем количество игрушек в файле
	string line;
	numToys = 0;
	while (getline(inFile, line)) {
		if (!line.empty()) {
			numToys++;
		}
	}

	// Выделяем память под массив структур
	shoes* toys = new shoes[numToys];

	// Считываем информацию об обуви из файла в массив структур
	inFile.clear();
	inFile.seekg(0, ios::beg); // переходим в начало файла
	int i = 0;
	for (int i = 0; i < numToys; ++i) {

		getline(inFile, toys[i].name, '|');
		inFile >> toys[i].price;
		inFile.ignore();
		getline(inFile, toys[i].manufacturer, '|');
		inFile >> toys[i].quantity;
		inFile.ignore();
		inFile >> toys[i].size;

	}

	inFile.close();
	return toys;
}



void displayshoes(shoes* shoes, int num_shoes) {
	cout << left << setw(40) << "Название" << '|'
		<< setw(10) << "Цена" << '|'
		<< setw(15) << "Производитель" << '|'
		<< setw(10) << "Количество" << '|'
		<< setw(19) << "размер обуви" << '|' << endl;
	cout << setfill('-') << setw(98) << '-' << setfill(' ') << endl;

	for (int i = 0; i < num_shoes; i++) {
		cout << left << setw(40) << shoes[i].name << '|'
			<< setw(10) << shoes[i].price << '|'
			<< setw(15) << shoes[i].manufacturer << '|'
			<< setw(10) << shoes[i].quantity << '|'
			<< setw(19) << shoes[i].size << '|' << endl;
		cout << setfill('-') << setw(98) << '-' << setfill(' ');
	}
	DeleteConsole();
}



void sortShoesByName(shoes* toys, int num_toys) {
	for (int i = 0; i < num_toys - 1; i++) {
		for (int j = i + 1; j < num_toys; j++) {
			if (toys[i].name > toys[j].name) {
				swap(toys[i], toys[j]);
			}
		}
	}
}



void sortByPrice(shoes* toys, int num_toys) {
	for (int i = 0; i < num_toys - 1; i++) {
		for (int j = 0; j < num_toys - i - 1; j++) {
			if (toys[j].price > toys[j + 1].price) {
				// Swap shoes[j] and shoes[j+1]
				shoes temp = toys[j];
				toys[j] = toys[j + 1];
				toys[j + 1] = temp;
			}
		}
	}
}



void sortByQuantity(shoes* shoes, int num_shoes) {
	for (int i = 0; i < num_shoes - 1; i++) {
		for (int j = 0; j < num_shoes - i - 1; j++) {
			if (shoes[j].quantity > shoes[j + 1].quantity) {
				swap(shoes[j], shoes[j + 1]);
			}
		}
	}
}



void searchByName(shoes* shoes, int num_shoes)
{
	string searchName;
	bool found = false;

	cout << "Введите название обуви которую желаете найти: ";
	getline(cin, searchName);
	searchName = '\n' + searchName;
	cout << endl << endl;



	for (int i = 0; i < num_shoes; i++) {
		if (shoes[i].name == searchName) {
			if (!found) {
				cout << left << setw(40) << "Название" << '|'
					<< setw(10) << "Цена" << '|'
					<< setw(15) << "Производитель" << '|'
					<< setw(10) << "Количество" << '|'
					<< setw(19) << "размер обуви" << '|' << endl;
				cout << setfill('-') << setw(98) << '-' << setfill(' ');
				found = true;
			}
			cout << left << setw(40) << shoes[i].name << '|'
				<< setw(10) << shoes[i].price << '|'
				<< setw(15) << shoes[i].manufacturer << '|'
				<< setw(10) << shoes[i].quantity << '|'
				<< setw(19) << shoes[i].size << '|' << endl;
			cout << setfill('-') << setw(98) << '-' << setfill(' ');
		}
	}
	if (!found) {

		cout << "Обувь с таким именем не найдена." << endl;
	}

}

void searchShoesBySize(shoes* toys, int num_toys) {
	double min_size, max_size;

	cout << "Введите минимальный размер: ";
	cin >> min_size;
	cout << "Введите максимальный размер: ";
	cin >> max_size;
	cout << endl << endl;

	cout << left << setw(40) << "Название" << '|'
		<< setw(10) << "Цена" << '|'
		<< setw(15) << "Производитель" << '|'
		<< setw(10) << "Количество" << '|'
		<< setw(19) << "размер обуви" << '|' << endl;
	cout << setfill('-') << setw(98) << '-' << setfill(' ');

	for (int i = 0; i < num_toys; i++) {
		if (toys[i].size >= min_size && toys[i].size <= max_size) {
			cout << left << setw(40) << toys[i].name << '|'
				<< setw(10) << toys[i].price << '|'
				<< setw(15) << toys[i].manufacturer << '|'
				<< setw(10) << toys[i].quantity << '|'
				<< setw(19) << toys[i].size << '|' << endl;
			cout << setfill('-') << setw(98) << '-' << setfill(' ');
		}
	}
	getchar();
	DeleteConsole();

}

void filterShoesByPrice(shoes* toys, int num_toys) {
	double min_price, max_price;

	cout << "Введите минимальную цену: ";
	cin >> min_price;
	cout << "Введите максимальную цену: ";
	cin >> max_price;
	cout << endl << endl;

	cout << left << setw(40) << "Название" << '|'
		<< setw(10) << "Цена" << '|'
		<< setw(15) << "Производитель" << '|'
		<< setw(10) << "Количество" << '|'
		<< setw(19) << "размер обуви" << '|' << endl;
	cout << setfill('-') << setw(98) << '-' << setfill(' ');

	for (int i = 0; i < num_toys; i++) {
		if (toys[i].price >= min_price && toys[i].price <= max_price) {
			cout << left << setw(40) << toys[i].name << '|'
				<< setw(10) << toys[i].price << '|'
				<< setw(15) << toys[i].manufacturer << '|'
				<< setw(10) << toys[i].quantity << '|'
				<< setw(19) << toys[i].size << '|' << endl;
			cout << setfill('-') << setw(98) << '-' << setfill(' ');
		}
	}
	getchar();
	DeleteConsole();

}

void filterShoesByQuantity(shoes* toys, int num_toys) {
	int min_quantity, max_quantity;
	cout << "Введите минимальное количество: ";
	cin >> min_quantity;
	cout << "Введите максимальное количество: ";
	cin >> max_quantity;
	cout << endl << endl;

	cout << left << setw(40) << "Название" << '|'
		<< setw(10) << "Цена" << '|'
		<< setw(15) << "Производитель" << '|'
		<< setw(10) << "Количество" << '|'
		<< setw(19) << "размер обуви" << '|' << endl;
	cout << setfill('-') << setw(98) << '-' << setfill(' ');

	for (int i = 0; i < num_toys; i++) {
		if (toys[i].quantity >= min_quantity && toys[i].quantity <= max_quantity) {
			cout << left << setw(40) << toys[i].name << '|'
				<< setw(10) << toys[i].price << '|'
				<< setw(15) << toys[i].manufacturer << '|'
				<< setw(10) << toys[i].quantity << '|'
				<< setw(19) << toys[i].size << '|' << endl;
			cout << setfill('-') << setw(98) << '-' << setfill(' ');
		}
	}
	getchar();
	DeleteConsole();
}


bool authenticateAdmin() {
	User person;
	string username, password;
	int attempts = 0;
	bool authenticated = false;
	bool fileIsAdmin, fileIsBanned;

	// Запрос логина
	cout << "Введите логин: ";
	getline(cin, person.login);

	// Проверка правильности логина
	ifstream inputFile1("admin.txt");
	string fileUsername, filePassword;
	bool validUsername = false;
	while (inputFile1 >> fileUsername >> filePassword >> fileIsAdmin >> fileIsBanned) {
		if (fileUsername == person.login) {
			validUsername = true;
			break;
		}
	}
	inputFile1.close();

	if (!validUsername) {
		cout << "Логин неверный. Аутентификация невозможна." << endl;
		DeleteConsole();
		return authenticated;
	}

	// Проверка блокировки аккаунта
	if (fileIsBanned) {
		cout << "Ваш аккаунт заблокирован." << endl;
		DeleteConsole();
		return authenticated;
	}

	while (attempts < MAX_ATTEMPTS) {
		// Запрос пароля
		cout << "Введите пароль: ";
		getline(cin, person.password);

		// Проверка правильности пароля
		ifstream inputFile2("admin.txt");
		while (inputFile2 >> fileUsername >> filePassword >> fileIsAdmin >> fileIsBanned) {
			if (fileUsername == person.login && filePassword == person.password) {
				person.isAdmin = fileIsAdmin;
				person.isBanned = fileIsBanned;

				if (person.isBanned == 0) {
					cout << "Аутентификация успешна." << endl;
					authenticated = true;
					DeleteConsole();
					break;
				}
				else {
					cout << "Ваш аккаунт заблокирован." << endl;
					DeleteConsole();
					return authenticated;
					break;
				}
			}
		}

		inputFile2.close();

		// Закрытие цикла при успешной аутентификации
		if (authenticated) {
			break;
		}
		else {
			attempts++;
			cout << "Пароль неверный. Пожалуйста, повторите попытку." << endl;
			DeleteConsole();
		}
	}

	// Проверка превышения количества попыток
	if (attempts == MAX_ATTEMPTS) {
		cout << "Превышено максимальное количество попыток. Аутентификация невозможна." << endl;
		DeleteConsole();
	}

	return authenticated;
}

bool authenticateUser() {
	User person;
	string username, password;
	int attempts = 0;
	bool authenticated = false;
	bool fileIsAdmin, fileIsBanned;
	float fileMoney;

	// Запрос логина
	cout << "Введите логин: ";
	getline(cin, person.login);

	// Проверка правильности логина
	ifstream inputFile1("users.txt");
	string fileUsername, filePassword;
	bool validUsername = false;
	while (inputFile1 >> fileUsername >> filePassword >> fileIsAdmin >> fileIsBanned >> fileMoney) {
		if (fileUsername == person.login) {
			validUsername = true;
			break;
		}
	}
	inputFile1.close();

	if (!validUsername) {
		cout << "Логин неверный. Аутентификация невозможна." << endl;
		DeleteConsole();
		return authenticated;
	}

	// Проверка блокировки аккаунта
	if (fileIsBanned) {
		cout << "Ваш аккаунт заблокирован." << endl;
		DeleteConsole();
		return authenticated;
	}

	while (attempts < MAX_ATTEMPTS) {
		// Запрос пароля
		cout << "Введите пароль: ";
		getline(cin, person.password);

		// Проверка правильности пароля
		ifstream inputFile2("users.txt");
		while (inputFile2 >> fileUsername >> filePassword >> fileIsAdmin >> fileIsBanned >> fileMoney) {
			if (fileUsername == person.login && filePassword == person.password) {
				person.isAdmin = fileIsAdmin;
				person.isBanned = fileIsBanned;

				if (person.isBanned == 0) {
					cout << "Аутентификация успешна." << endl;
					authenticated = true;
					DeleteConsole();
					break;
				}
				else {
					cout << "Ваш аккаунт заблокирован." << endl;
					DeleteConsole();
					return authenticated;
					break;
				}
			}
		}

		inputFile2.close();

		// Закрытие цикла при успешной аутентификации
		if (authenticated) {
			break;
		}
		else {
			attempts++;
			cout << "Пароль неверный. Пожалуйста, повторите попытку." << endl;
			DeleteConsole();
		}
	}

	// Проверка превышения количества попыток
	if (attempts == MAX_ATTEMPTS) {
		cout << "Превышено максимальное количество попыток. Аутентификация невозможна." << endl;
		DeleteConsole();
	}

	return authenticated;
}

void registerUser() {
	string username, password;
	bool isAdmin = 0, isBanned = 0;
	float money = 2000;

	// Запрос логина и пароля
	cout << "Введите логин: ";
	getline(cin, username);

	// Проверка на наличие пробелов в логине
	if (username.find(' ') != string::npos) {
		cout << "Логин не должен содержать пробелы." << endl;
		DeleteConsole();
		return;
	}
	else {
		cout << "Введите пароль: ";
		getline(cin, password);

		// Проверка длины пароля
		if (password.length() < 8) {
			cout << "Пароль должен состоять не менее чем из 8 символов." << endl;
			DeleteConsole();
			return;
		}
	}
	// Проверка наличия логина в файле
	ifstream inputFile("users.txt");
	string fileUsername, filePassword;
	bool usernameExists = false;
	while (inputFile >> fileUsername >> filePassword) {
		if (fileUsername == username) {
			usernameExists = true;
			break;
		}
	}
	inputFile.close();

	// Регистрация нового пользователя или сообщение об ошибке, если логин уже существует
	if (!usernameExists) {
		ofstream outputFile("users.txt", ios::app);
		outputFile << username << " " << password << " " << isAdmin << " " << isBanned << " " << money << endl;
		outputFile.close();
		cout << "Пользователь зарегистрирован." << endl; DeleteConsole();
	}
	else {
		cout << "Пользователь с таким логином уже существует." << endl;
		DeleteConsole();
	}
}

int main()
{


	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool authenticated0 = false;
	bool authenticated1 = false;


	int attempts = 0; // Количество попыток аутентификации
	char choice1, choice2, choice3, choice4, choice5, choice6;
	int a = 0, b = 0, c = 0, d = 0, e = 0;
	do
	{
		a = 0;
		cout << "Выберите пункт\n1.Зарегистрироваться\n2.Войти\n3.Просмотреть каталог\n0.Закончить\nВведите цифру:\n";
		cin >> choice1;
		system("cls");
		if (!isdigit(choice1)) {
			cout << "Ошибка: пожалуйста, введите число." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			DeleteConsole();
			continue;
		}


		getchar();
		switch (choice1) {

		case '1': {
			registerUser();

			break;
		}
		case '2': {
			do {
				cout << "1.Войти как администратор\n2.Войти как пользователь\n0.Назад\n";
				cin >> choice2;
				system("cls");
				if (!isdigit(choice2)) {
					cout << "Ошибка: пожалуйста, введите число." << endl;
					cin.clear();
					cin.ignore(10000, '\n');
					DeleteConsole();
					continue;
				}



				getchar();
				switch (choice2)
				{

				case '1': {
					authenticated1 = authenticateAdmin();
					if (authenticated1) {
						do {
							cout << "1.Заблокировать пользователя\n2.Удалить пользователя\n3.Разблокировать пользователя\n4.Просмотреть всех пользователей\n0.Назад\n";
							cin >> choice3;
							system("cls");
							if (!isdigit(choice3)) {
								cout << "Ошибка: пожалуйста, введите число." << endl;
								cin.clear();
								cin.ignore(10000, '\n');
								DeleteConsole();
								continue;
							}



							switch (choice3) {

							case '1': {
								banUser();

								break;

							}
							case '2': {
								deleteUser();

								break;
							}
							case '3': {
								unblockUser();

								break;
							}
							case '4': {
								viewUsers();
								DeleteConsole();

								break;
							}

							case '0': {

								break;
							}
							default:
							{
								cout << "\nНет такого варианта, введите заново:\n";
								DeleteConsole();

							}

							}
						} while (choice3 != '0');
					}
					break;

				}

				case '2': {
					authenticated0 = authenticateUser();

					if (authenticated0) {


						do {

							cout << "1.Просмотреть каталог обуви\n2.Отсортировать каталог обуви по какому-либо параметру\n3.Найти обувь по какому-либо параметру\n0.Назад\n";
							cin >> choice4;
							system("cls");
							if (!isdigit(choice4)) {
								cout << "Ошибка: пожалуйста, введите число." << endl;
								cin.clear();
								cin.ignore(10000, '\n');
								DeleteConsole();
								continue;
							}

							getchar();
							switch (choice4) {

							case '1': {
								int numToys;
								shoes* toys = readShoesFromFile("shoes.txt", numToys);
								if (toys != nullptr) {
									displayshoes(toys, numToys);
									delete[] toys;
								}
								break;

							}
							case '2': {
								do {

									cout << "1.Сортировать по имени\n2.Сортировать по цене\n3.Сортировать по кол-ву\n0.Назад\n";
									cin >> choice5;
									system("cls");
									if (!isdigit(choice5)) {
										cout << "Ошибка: пожалуйста, введите число." << endl;
										cin.clear();
										cin.ignore(10000, '\n');
										DeleteConsole();
										continue;
									}

									getchar();
									switch (choice5) {

									case '1': {
										int numToys;
										shoes* toys = readShoesFromFile("shoes.txt", numToys);
										if (toys != nullptr) {
											sortShoesByName(toys, numToys);
											displayshoes(toys, numToys);
											delete[] toys;
										}
										break;

									}
									case '2': {
										int numToys;
										shoes* toys = readShoesFromFile("shoes.txt", numToys);
										if (toys != nullptr) {
											sortByPrice(toys, numToys);
											displayshoes(toys, numToys);
											delete[] toys;
										}

										break;
									}
									case '3': {
										int numToys;
										shoes* toys = readShoesFromFile("shoes.txt", numToys);
										if (toys != nullptr) {
											sortByQuantity(toys, numToys);
											displayshoes(toys, numToys);
											delete[] toys;
										}

										break;
									}
									case '0': {
										d = 1;
										break;
									}
									default:
									{
										cout << "\nНет такого варианта, введите заново:\n";

									}

									}




								} while (choice5 != '0');

								break;
							}
							case '3': {
								do {

									cout << "1.Поиск по имени\n2.Фильтровать по ценовому промежутку\n3.Фильтровать по кол-ву\n4.Фильтровать по размеру\n0.Назад\n";
									cin >> choice6;
									system("cls");
									if (!isdigit(choice6)) {
										cout << "Ошибка: пожалуйста, введите число." << endl;
										cin.clear();
										cin.ignore(10000, '\n');
										DeleteConsole();
										continue;
									}


									getchar();
									switch (choice6) {

									case '1': {
										int numToys;
										shoes* toys = readShoesFromFile("shoes.txt", numToys);
										if (toys != nullptr) {
											searchByName(toys, numToys);
											DeleteConsole();
											delete[] toys;
										}
										break;

									}
									case '2': {
										int numToys;
										shoes* toys = readShoesFromFile("shoes.txt", numToys);
										if (toys != nullptr) {
											filterShoesByPrice(toys, numToys);

											delete[] toys;
										}

										break;
									}
									case '3': {
										int numToys;
										shoes* toys = readShoesFromFile("shoes.txt", numToys);
										if (toys != nullptr) {
											filterShoesByQuantity(toys, numToys);

											delete[] toys;
										}

										break;
									}
									case '4': {
										int numToys;
										shoes* toys = readShoesFromFile("shoes.txt", numToys);
										if (toys != nullptr) {
											searchShoesBySize(toys, numToys);

											delete[] toys;
										}

										break;
									}
									case '0': {

										break;
									}
									default:
									{
										cout << "\nНет такого варианта, введите заново:\n";
										DeleteConsole();

									}

									}



								} while (choice6 != '0');

								break;
							}
							case '0': {
								c = 1;
								break;
							}
							default:
							{
								cout << "\nНет такого варианта, введите заново:\n"; DeleteConsole();

							}

							}




						} while (choice4 != '0');
					}
				}
				case '0': {
					a = 1;
					break;
				}
				default:
				{
					cout << "\nНет такого варианта, введите заново:\n"; DeleteConsole();

				}

				}

			} while (choice2 != '0');
		}
				break;
		case '3': {
			int numToys;
			shoes* toys = readShoesFromFile("shoes.txt", numToys);
			if (toys != nullptr) {
				displayshoes(toys, numToys);
				delete[] toys;
			}
			break;

		}
		case '0': {
			return 0;
			break;
		}
		default:
		{
			cout << "\nНет такого варианта, введите заново:\n";
			DeleteConsole();
		}

		}
	} while (choice1 != '0');





}



