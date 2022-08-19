#include "Game.h"
#include<ctime>
#include<Windows.h>
#include<SFML/Graphics.hpp>
#include<iostream>

int main()
{
	/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 30);
	system("CLS");
	SetConsoleTextAttribute(hConsole, 2);

	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")*/

	srand(static_cast<unsigned int>(time(0)));

	//create game object
	Game game_;

	//run the game
	game_.Run_();








}