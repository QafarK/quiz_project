#pragma once
string _username;
void Menu()
{

#pragma region Admin_Account
	ofstream admin;
	admin.open("..\\admin.txt");
	admin << "username: admin\npassword: admin123";
	admin.close();
#pragma endregion

	string choice;
	while (true)
	{
		cout << "1. Sign In" << endl;
		cout << "2. Sign Up" << endl;
		cin >> choice;
		if (choice == "1")
			Sign_in();
		else if (choice == "2")
			Sign_up();
		else
			cout << endl << "Wrong choice" << endl << endl;
	}
}

void Sign_in()
{
	string username;
	string password;

	cout << "username:";
	cin >> username;

	cout << "password:";
	cin >> password;
	cout << endl;

	ifstream file;
	string data;

#pragma region Sign_in_Admin
	file.open("..\\admin.txt");
	file.seekg(0, ios::beg);
	while (!file.eof())
	{
		file >> data;
		if (data == "username:")
		{
			file >> data;
			if (data == username)
			{
				file >> data >> data;
				if (data == password)
				{
					file.close();
					_username = username;
					Admin_Menu();
				}
				else
				{
					cout << "Password is incorrect" << endl << endl;
					file.close();
					Sign_in();
				}
			}
		}
	}
	file.close();
#pragma endregion


#pragma region Sign_in_User
	file.open("..\\users.txt");
	file.seekg(0, ios::beg);
	while (!file.eof())
	{
		file >> data;
		if (data == "username:")
		{
			file >> data;
			if (data == username)
			{
				file >> data >> data;
				if (data == password)
				{
					file.close();
					_username = username;
					User_Menu();
				}
				else
				{
					cout << "Password is incorrect" << endl << endl;
					file.close();
					Sign_in();
				}
			}
		}
	}
	file.close();
#pragma endregion

	cout << "Username not founded" << endl << endl;
	Menu();
}

void Sign_up()
{
	string username;
	string password;
	ifstream usercheck;
	usercheck.open("..\\users.txt");
	string data;
	cout << endl << "Note: Username characters must be Alphabets and Numbers (first character must be Alphabet)." << endl << endl;
	bool check = false;
	bool let = false;
	while (!let)
	{
		cout << "Create username:";
		cin >> username;

		if ((username[0] >= 65 && username[0] <= 90) || (username[0] >= 97 && username[0] <= 122))
		{
			for (size_t i = 1; i < username.length(); i++)
			{
				if ((username[i] >= 65 && username[i] <= 90) || (username[i] >= 97 && username[i] <= 122) ||
					(username[i] >= 48 && username[i] <= 57))
				{
					if (i == username.length() - 1)
					{
						usercheck.seekg(0, ios::beg);
						while (!usercheck.eof())
						{
							usercheck >> data;
							if (data == "username:")
							{
								usercheck >> data;
								if (data == username)
								{
									cout << "This username already exists" << endl;
									check = false;
									break;
								}
								else
									check = true;
							}
						}
						if (check) let = true;
					}
				}
				else
				{
					cout << "characters must be Alphabets and Numbers in Username" << endl;
					break;
				}
			}
		}
		else
			cout << "First character must be Alphabet in Username" << endl;
	}
	cout << endl << "Note: Password characters must be Alphabets and Numbers." << endl << endl;
	let = false;
	while (!let)
	{
		cout << "Create password:";
		cin >> password;
		for (size_t i = 0; i < password.length(); i++)
		{
			if ((password[i] >= 65 && password[i] <= 90) || (password[i] >= 97 && password[i] <= 122) ||
				(password[i] >= 48 && password[i] <= 57))
			{
				if (i == password.length() - 1) { let = true; }
			}
			else
			{
				cout << "characters must be Alphabets and Numbers in Password" << endl;
				break;
			}
		}
	}

	ofstream user;
	user.open("..\\users.txt", ios::app);
	user << "username: " << username << "\n";
	user << "password: " << password << "\n";
	user.close();
}

void Admin_Menu()
{
	string choice;

	while (true)
	{
		cout << "1. Start Quiz" << endl;
		cout << "2. Leader Board" << endl;
		cout << "3. Create Quiz" << endl;
		cout << "0. Exit" << endl;
		cin >> choice;
		if (choice == "1")
		{
			Start_Quiz();
		}
		else if (choice == "2")
		{
			LeaderBoard();
		}
		else if (choice == "3")
		{
			Create_Quiz();
		}
		else if (choice == "0")
		{
			cout << endl;
			Menu();
		}
		else
			cout << endl << "Wrong choice" << endl << endl;
	}

}

//short quiz_count = 0;
int quizrows[5]{};
short QuizCount(string quizname)
{
	string data;
	short num = 0;
	ifstream quiznumber;
	quiznumber.open(quizname, ios::in);
	quiznumber.seekg(0, ios::beg);
	int current = 0;
	short i = 0;

	while (!quiznumber.eof())
	{
		quiznumber >> data;
		if (data.length() <= 6)
		{
			if (data[0] == 'Q' && data[1] == 'u' && data[2] == 'i' && data[3] == 'z' && data[5] == ':')
			{
				current = quiznumber.tellg();
				current -= 6;
				quizrows[i++] = current;
				char ch_data = data[4];
				if ((int(ch_data) - 48) > num)
				{
					num = int(ch_data) - 48;
				}
			}
		}
	}
	quiznumber.close();
	return num;
}

void Create_Quiz()
{
	string input;
#pragma region Quizname
	cout << "Enter quiz name:";
	cin >> input;
	string quizname = "..\\" + input + ".txt";
#pragma endregion

#pragma region QuizNameFiles
	ofstream quiztopic;
	quiztopic.open("..\\QuizFilesNames.txt", ios::app);
	quiztopic << quizname << "-";
	quiztopic.close();
#pragma endregion

	ofstream quiz;
	quiz.open(quizname, ios::app);
#pragma	region Quiz_Number
	short num = 0;
	num = QuizCount(quizname);
#pragma endregion

	int sayi = 1;
	while (sayi <= 5 && num < 5)
	{
		num++;
		char* sual = new char[50] {};
		cout << "Write question (" << char(sayi + 48) << "):";
		cin.ignore();
		cin.getline(sual, 50);

		quiz << "Quiz" << char(num + 48) << ": ";

		for (size_t i = 0; i < 50; i++)
		{
			if (sual[i] != NULL) { quiz << sual[i]; }
			else { break; }
		}
		quiz << "\n";
		delete[] sual;

		cout << endl << "Enter answers" << endl;
		cout << "A: ";
		cin >> input;
		quiz << "A: " << input << "\n";

		cout << "B: ";
		cin >> input;
		quiz << "B: " << input << "\n";

		cout << "C: ";
		cin >> input;
		quiz << "C: " << input << "\n";

		cout << "D: ";
		cin >> input;
		quiz << "D: " << input << "\n";

		cout << "Write correct answer:";
		cin >> input;
		quiz << "Correct: " << input << "\n";
		sayi++;
		cout << endl;
	}

	quiz.close();
}

void User_Menu()
{
	string choice;

	while (true)
	{
		cout << "1. Start Quiz" << endl;
		cout << "2. Leader Board" << endl;
		cout << "0. Exit" << endl;
		cin >> choice;
		if (choice == "1")
		{
			Start_Quiz();
		}
		else if (choice == "2")
		{
			LeaderBoard();
		}
		else if (choice == "0")
		{
			cout << endl;
			Menu();
		}
		else
			cout << endl << "Wrong choice" << endl << endl;
	}
}

void Start_Quiz()
{
	string data;
#pragma region QuizTopics
	ifstream quiztopic;
	quiztopic.open("..\\QuizFilesNames.txt", ios::beg);
	while (!quiztopic.eof())
	{
		quiztopic >> data;
		for (size_t i = 0; i < data.length(); i++)
		{
			if (data[i] != '-')
				cout << data[i];
			else
				cout << endl;
		}
	}
	quiztopic.close();
	string quizname;
	cout << "Choose quiz name:";
	cin >> data;
#pragma endregion
	ifstream question;
	quizname = "..\\" + data + ".txt";
	question.open(quizname);
	question.seekg(0, ios::beg);
	string a;
	string b;
	string c;
	string d;
	bool back = false;
	int current = 0;
	short row = 1;// 1den bashlayir
	char ch_data;

	short quiz_count = QuizCount(quizname);

	char* quiz_for_end = new char [quiz_count] {};//quiz_for_end 0dan bashlayir
	for (size_t i = 0; i < quiz_count; i++)
	{
		quiz_for_end[i] = '-';
	}
	short duz = 0;
	short sehv = 0;
	short bosh = 0;
	bool stop = false;

	string variants[4]{};
	string choose;
	short arr[5]{ 1,2,3,4,5 };
	srand(time(NULL));
	random_shuffle(begin(arr), end(arr));
	row = arr[0];
	short sira = 0;
	short after;

	while (!stop)
	{
		if (quiz_for_end[row - 1] == '-')
		{
			question.seekg(quizrows[row - 1], ios::beg);

			while (data != "Correct:")
			{
				question >> data;

				if (data[0] == 'Q' && data[1] == 'u' && data[2] == 'i' && data[3] == 'z' && data[5] == ':')
				{
					ch_data = data[4];
					row = int(ch_data) - 48;
					question >> data;
					cout << endl;
					while (!(data[0] == 'A' && data[1] == ':'))
					{
						cout << data << " ";
						question >> data;
					}
					cout << endl;
				}
				if (data == "A:")
				{
					question >> data;
					variants[0] = data;
				}
				else if (data == "B:")
				{
					question >> data;
					variants[1] = data;
				}
				else if (data == "C:")
				{
					question >> data;
					variants[2] = data;
				}
				else if (data == "D:")
				{
					question >> data;
					variants[3] = data;
				}
			}

			random_shuffle(begin(variants), end(variants));
			cout << "A:" << variants[0] << endl;
			cout << "B:" << variants[1] << endl;
			cout << "C:" << variants[2] << endl;
			cout << "D:" << variants[3] << endl;
			a = variants[0];
			b = variants[1];
			c = variants[2];
			d = variants[3];
			while (true)
			{
				cout << endl << "1 : new" << endl;
				cout << "2 : back" << endl;
				cout << "3 : save" << endl;
				cout << "Choose answer (A, B, C, D or 1, 2, 3):";
				cin >> choose;
				if (choose == "A" || choose == "B" || choose == "C" || choose == "D" || choose == "1" || choose == "2" || choose == "3")
				{
					if (choose == "1")
					{
						while (true)
						{
							if (sira == 4)
							{
								after = arr[0];
								row = after;
								sira = 0;
							}
							else
							{
								for (size_t i = 0; i < 4; i++)
								{
									if (arr[i] == row)
									{
										after = arr[i + 1];
										sira = i + 1;
										row = after;

										break;
									}
								}
							}
							if (quiz_for_end[after - 1] == '-')
							{
								data = "";
								break;
							}
							else
							{
								if (sira != 4)
								{
									sira++;
								}
								else
								{
									sira = 0;
								}
							}
						}
					}
					if (choose == "2")
					{
						while (true)
						{
							if (sira == 0)
							{
								after = arr[4];
								row = after;
								sira = 4;
							}
							else
							{
								for (size_t i = 1; i < 5; i++)
								{
									if (arr[i] == row)
									{
										after = arr[i - 1];
										sira = i - 1;
										row = after;

										break;
									}
								}
							}
							if (quiz_for_end[after - 1] == '-')
							{
								data = "";
								break;
							}
							else
							{
								if (sira != 0)
								{
									sira--;
								}
								else
								{
									sira = 4;
								}
							}
						}
					}
					else if (choose == "3")
					{
						Result(quiz_for_end, quiz_count, duz, sehv, bosh);
						question.close();
						return;
					}
					else if (choose == "A" || choose == "B" || choose == "C" || choose == "D")
					{
						question >> data;

						if (choose == "A")
						{
							if (data == a)
							{
								cout << endl << "TRUE" << endl << endl;
								quiz_for_end[row - 1] = 'T';
							}
							else
							{
								cout << endl << "FALSE" << endl << endl;
								quiz_for_end[row - 1] = 'F';
							}
						}
						else if (choose == "B")
						{
							if (data == b)
							{
								cout << endl << "TRUE" << endl << endl;
								quiz_for_end[row - 1] = 'T';
							}
							else
							{
								cout << endl << "FALSE" << endl << endl;
								quiz_for_end[row - 1] = 'F';
							}
						}
						else if (choose == "C")
						{
							if (data == c)
							{
								cout << endl << "TRUE" << endl << endl;
								quiz_for_end[row - 1] = 'T';
							}
							else
							{
								cout << endl << "FALSE" << endl << endl;
								quiz_for_end[row - 1] = 'F';
							}
						}
						else if (choose == "D")
						{
							if (data == d)
							{
								cout << endl << "TRUE" << endl << endl;
								quiz_for_end[row - 1] = 'T';
							}
							else
							{
								cout << endl << "FALSE" << endl << endl;
								quiz_for_end[row - 1] = 'F';
							}
						}
					}
					break;
				}
				else { cout << endl << "You must choose A, B, C, D or 1, 2, 3" << endl << endl; choose.clear(); }
			}
			a.clear();
			b.clear();
			c.clear();
			d.clear();

			if (question.eof()) { question.seekg(0, ios::beg); }

		}
		else
		{
			if (sira == 4)
			{
				after = arr[0];
				row = after;
				sira = 0;
			}
			else
			{
				for (size_t i = 0; i < 4; i++)
				{
					if (arr[i] == row)
					{
						after = arr[i + 1];
						sira = i + 1;
						row = after;

						break;
					}
				}
			}
		}

		stop = true;
		for (size_t i = 0; i < quiz_count; i++)
		{
			if (quiz_for_end[i] == '-') { stop = false; break; }
		}
	}


	Result(quiz_for_end, quiz_count, duz, sehv, bosh);
	question.close();
}


void Result(char* quizforend, short quizcount, short duz, short sehv, short bosh)
{
	for (size_t i = 0; i < quizcount; i++)
	{
		if (quizforend[i] == 'T') { duz++; }
		if (quizforend[i] == 'F') { sehv++; }
		if (quizforend[i] == '-') { bosh++; }
	}
	cout << endl << "----TOTAL----" << endl;
	cout << "TRUE:" << duz << endl;
	cout << "FALSE:" << sehv << endl;
	cout << "EMPTY:" << bosh << endl << endl << endl;
	AddLeaderBoard(duz, sehv, bosh);
	if (quizforend) { delete[] quizforend; }
}


void AddLeaderBoard(short duz, short sehv, short bosh)
{
	ofstream board;
	board.open("..\\addLeaderBoard.txt", ios::app);
	board << "username: " << _username << " duz: " << duz << " sehv: " << sehv << " bosh: " << bosh << "\n";
	board.close();
}

void LeaderBoard()
{
	string data;
	ifstream board;
	board.open("..\\addLeaderBoard.txt");
	int current;
	string username;
	int sayi = 10;
	while (sayi)
	{
		board >> data;
		if (data == "username:")
		{
			current = board.tellg();
			board >> data;
			username = data;
			while (data != "duz:")
			{
				board >> data;
			}
			board >> data;

			while (sayi)
			{
				current -= 9;
				board.seekg(current, ios::beg);
				while (data != "bosh:")
				{
					board >> data;
					cout << data << " ";
				}
				board >> data;
				cout << data << endl;
				sayi--;
				break;
			}
		}
	}
	board.close();
}

