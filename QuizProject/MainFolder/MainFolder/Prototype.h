#pragma once

void Menu();

void Sign_in();
void Sign_up();

void Admin_Menu();
void Create_Quiz();

void User_Menu();
void Start_Quiz();
void AddLeaderBoard(short duz, short sehv, short bosh);
void LeaderBoard();
//-----------
short QuizCount(string quizname);
void Result(char* quizforend, short quizcount, short duz, short sehv, short bosh);