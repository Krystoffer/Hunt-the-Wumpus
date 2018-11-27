#pragma once

// Include libraries
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

// Include classes
#include "Player.h"
#include "Wumpus.h"
#include "Room.h"

using namespace std;

// Declare functions
void loadRoom();
void loadItem();
void printFile(string filename);
void titleScreen();
void helpScreen();
void printCPL();
void inGameInput();
void playerCommand(string command, string target);
void go(string targetDirection);
void shoot(string targetDirection);
void takeItem(Item *loot);

class Game
	{
		private:


		public:
		Game();
		void startGame();
		~Game();
	};

