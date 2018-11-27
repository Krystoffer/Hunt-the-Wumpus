#include "Game.h"

// Initialize game running variables
bool titleRunning = true;
bool gameRunning = false;
string death = "";
bool winGame = false;

// Initialize player and wumpus object
Player player(0);
Wumpus wumpus;

// Create rooms and items vectors
vector<Room> rooms;
vector<Item> items;

// Create counter and treshold for wumpus to wake up
const int wakeupTreshold = 4;
int wakeupCounter = 0;
int counterIncrement = 4;	// 4 for normal gun, 2 with silencer on

// Create array to contain the adjacent rooms
int adjacent[3];

// Create output variable
stringstream output;

Game::Game()
	{
	};

void Game::startGame()
	{
		// Set the current time as a RNG seed
		srand(time(NULL));

		// Display splash screen
		printFile("splash.txt");
		cout << endl;
		system("pause");

		// Display title screen
		while (titleRunning)
			{
				titleScreen();
			};

		// Load the necessary game data
		loadRoom();
		loadItem();

		system("CLS");

		// Game Loop
		while (gameRunning)
			{
				if (wumpus.getSleeping() == false)
					{
						int wumpusAction = rand() % 100;

						if (wumpusAction < 75)		// 75% chance for the wumpus to move to a connecting room
							{
								int nextRoom = rooms[wumpus.getLocation()].getRandomIndex();
								wumpus.setLocation(nextRoom);
							}
						else		// 25% chance for the wumpus to sleep again
							{
								wumpus.setSleeping(true);
							}
					}
				printCPL();			// Print current player location
				cout << output.str() << endl;
				output.str("");
				inGameInput();
			};

		system("CLS");
		if (winGame)
			{
				cout << "Congratulations! You have killed the wumpus and you have been given the title \"Hero\" by the villagers." << endl << endl;
			}
		else		// If the player loses or quit, print out the corresponding message
			{
				if (death == "pit")
					{
						cout << "You slipped and fell into a bottomless pit!" << endl;
					}
				else if (death == "wumpus")
					{
						cout << "You made contact with the wumpus and got turned into a golden statue!" << endl;
					}
				else if (death == "battery")
					{
						cout << "You ran out of battery and are trapped inside the cave as you can't see anything" << endl;
					}
				else if (death == "ammo")
					{
						cout << "You ran out of bullets and can't fend yourslef off from the wumpus" << endl;
					}
				else
					{
						cout << "Too bad... The wumpus is still alive and is scheming to turn the whole world into gold" << endl << endl;
					};
			};
		system("pause");
	};

Game::~Game()
	{
	};

void loadRoom()
	{
		ifstream file;
		string line;
		string name;
		string description;
		string direction1, direction2, direction3;
		int target1, target2, target3;
		int position;

		file.open("roomData.txt");
		while (getline(file, line))
			{
				name = line;

				getline(file, line);
				description = line;

				getline(file, line);
				position = line.find(' ');
				direction1 = line.substr(0, position);
				target1 = stoi(line.substr(position + 1));	

				getline(file, line);
				position = line.find(' ');
				direction2 = line.substr(0, position);
				target2 = stoi(line.substr(position + 1));	

				getline(file, line);
				position = line.find(' ');
				direction3 = line.substr(0, position);
				target3 = stoi(line.substr(position + 1));	

				rooms.push_back(Room(name, description, direction1, target1, direction2, target2, direction3, target3));
				
				getline(file, line);
			};
		file.close();

		// Setting up the hazards (bat & pit) at 4 different rooms
		int hazards[4];
		int index;
		bool indexAllowed = false;
		for (int i = 0; i < 4; i++)
			{
				do
					{
						index = (rand() % 19) + 1;			// The starting room will have no hazards
						for (int j = 0; j <= i; j++)
							{
								if (index == hazards[j])	// If the room is already listed in the array above, find another room
									{
										indexAllowed = false;
									}
								else
									{
										indexAllowed = true;
									}
							}
					}
				while (!indexAllowed);

				hazards[i] = index;
			};

		rooms[hazards[0]].setHazard("pit");
		rooms[hazards[1]].setHazard("pit");
		rooms[hazards[2]].setHazard("bat");
		rooms[hazards[3]].setHazard("bat");
		
		// Set a random location for the wumpus (not the starting location)
		wumpus.setLocation((rand() % 19) + 1);
	}

void loadItem()
	{
		ifstream file;
		string line;
		string name;
		char category;
		int value;

		file.open("itemData.txt");
		while (getline(file, line))
			{
				name = line;

				getline(file, line);
				category = line[0];

				getline(file, line);
				value = stoi(line);

				items.push_back(Item(name, category, value));

				getline(file, line);
			};
		file.close();

		int roomIndex;
		for (size_t i = 0; i < items.size(); i++)
			{
				roomIndex = rand() % 20;
				while (rooms[roomIndex].getHazard() != "")
					{
						roomIndex = rand() % 20;
					};
				rooms[roomIndex].addItem(&items[i]);
			};
	};

// A function to print everything that is in a file
void printFile(string filename)
	{
		system("CLS");

		string line;
		ifstream file;
		file.open (filename);
		while(getline(file, line))
			{
				cout << line << endl;
			};
		file.close();
		
		cout << endl;
	}

// A function to show the title screen
void titleScreen()
	{
		system("CLS");
		printFile("title.txt");

		string outGameInput;
		getline(cin,outGameInput);									// Prompt user for the next action
		for (unsigned int i = 0; i < outGameInput.length(); i++)	// Make user input into capital letters to remove case-sensitiveness
			{
				outGameInput[i] = toupper(outGameInput[i]);
			};

		if (outGameInput == "START")
			{
				titleRunning = false;
				gameRunning = true;
			}
		else if (outGameInput == "HELP")
			{
				helpScreen();
			}
		else if (outGameInput == "QUIT")
			{
				titleRunning = false;
			}
		else
			{
				system("CLS");
			}
	};

// A function to print the help screen
void helpScreen()
	{
		printFile("help.txt");

		if (!gameRunning)
			{
				cout << endl << endl << "Press any key to go back to the title screen" << endl;
				system("pause");
			}
		else
			{
				cout << endl << endl << "Press any key to back to the game" << endl;
				system("pause");
				system("CLS");
			}
	};

// A function to print the player's current location
void printCPL()
	{
		cout << "*************************************************" << endl;
		cout << "You are currently in the " << rooms[player.getLocation()].getName() << endl;
		cout << "Battery: " << player.getBattery() << "% \t" << "Ammo: " << player.getAmmo() << endl;
		cout << "*************************************************" << endl;		
		cout << rooms[player.getLocation()].getDescription() << endl << endl;

		// Get information regarding the hazards around the room
		rooms[player.getLocation()].getAdjacent(adjacent, 3);
		bool hazards[3] = {false, false, false};	 // 0 for bat, 1 for pit, 2 for wumpus

		for (int i = 0; i < 3; i++)
			{
				if (rooms[adjacent[i]].getHazard() == "bat")
					{
						hazards[0] = true;
					}
				else if (rooms[adjacent[i]].getHazard() == "pit")
					{
						hazards[1] = true;
					};
				
				if (adjacent[i] == wumpus.getLocation())
					{
						hazards[2] = true;
					}
			};

		// Print messages regarding the hazards around the room
		if (hazards[0] == true)
			{
				cout << "Super Bats: a colony of these bats makes an awful racket and are very protective of their" << endl;
				cout << "domain. If you happen to wander into their cave, they’ll swam you and carry you off to some" << endl;
				cout << "random cave within the caverns." << endl << endl;
			};
		if (hazards[1] == true)
			{
				cout << "Bottomless Pits: they tend to be drafty, very deep and easy to fall into! They will just kill you" << endl;
				cout << "outright, should you fall into one. So, watch your step!" << endl << endl;
			};
		if (hazards[2] == true)
			{
				cout << "Wumpus: a greedy beast that thinks of nothing but gold. It sleeps a lot and won't wake up without" << endl;
				cout << "much noise. If it is awake and you're in the same room, you'll be turned into a golden statue. It is" << endl;
				cout << "physically five times stronger than a human, therfore it can fight against bats and jumo over pits." << endl << endl;
			};

		cout << rooms[player.getLocation()].getDirection();
		cout << endl << endl;
	};

// A function to take in user input
void inGameInput()
	{	
		string action;
		
		cout << "What do you want to do?" << endl;
		getline(cin, action);
		for (unsigned int i = 0; i < action.length(); i++)	//
			{												// Make the user input into upper case to
				action[i] = toupper(action[i]);				// prevent code from not recognizing the command
			};												//

		string verb;
		string noun;
		int position;

		position = action.find(' ');				//
		verb = action.substr(0, position);			// Break the user input into VERB and NOUN
		noun = action.substr(position + 1);			//

		system("CLS");

		playerCommand(verb, noun);					// Call another function to further process the user input
	};

void playerCommand(string command, string target)
	{
		vector<string> commandList = {"QUIT", "HELP", "GO", "SHOOT", };
		// Use the index of the value from the array above and parse it in as an input for a switch case
		
		int commandIndex = 100;							// Initialize the value as 100 so that if the command doesn't exist it will go to default
		for (size_t i = 0; i < commandList.size(); i++)
			{
				if (command == commandList[i])
					{
						commandIndex = i;
					};
			};

		switch (commandIndex)
			{
				case 0:
					gameRunning = false;
					break;
				case 1:
					helpScreen();
					break;
				case 2:
					go(target);
					break;
				case 3:
					shoot(target);
					break;
			};
	};	

// A function to move the player to another adjacent room
void go(string targetDirection)
	{
		int nextRoom;

		nextRoom = rooms[player.getLocation()].getRoomIndex(targetDirection);
		if (nextRoom < 0)
			{
				output << "That direction leads to a wall" << endl;
			}
		else
			{
				player.setBattery(player.getBattery() - 2);
				
				if (player.getBattery() <= 0)
					{
						gameRunning = false;
						death = "battery";
					}

				// Reduce the wake up counter of the wumpus as you walk
				if (wakeupCounter > 0)
					{
						wakeupCounter--;
					};
				player.setLocation(nextRoom);

				// Check if the room has a hazard
				if (rooms[nextRoom].getHazard() == "pit")
					{
						// Check if the player has a grappling hook upon falling into a pit
						if (player.haveItem("Grappling Hook"))
							{
								player.removeItem(&items[6]);
								output << "Lucky you have a grappling hook, you were just saved by your quick reflex" << endl;
							}
						else
							{
								gameRunning = false;
								death = rooms[nextRoom].getHazard();
							};
					}
				else if (rooms[nextRoom].getHazard() == "bat")
					{
						// Check if the player has a bat whistle upon encountering bats
						if (player.haveItem("Bat Whistle"))
							{
								player.removeItem(&items[5]);
								output << "Lucky you have a bat whistle, the bats were annoyed by the sound and left the cave" << endl;
							}
						else
							{
								// Send the player to a random room
								player.setLocation(rand() % 20);

								// Check if the place the player is dropped is a pit
								if (rooms[player.getLocation()].getHazard() == "pit")
									{
										// Check again if the player has a grappling hook
										if (player.haveItem("Grappling Hook"))
											{
												player.removeItem(&items[6]);
												output << "Lucky you have a grappling hook, you were just saved by your quick reflex" << endl;
											}
										else
											{
												gameRunning = false;
												death = rooms[nextRoom].getHazard();
											};
									}
								// Check if the player is dropped on the wumpus
								else if (wumpus.getLocation() == player.getLocation())
									{
										gameRunning = false;
										death = "wumpus";
									}
							};
					}
				else if (wumpus.getLocation() == player.getLocation())
					{
						gameRunning = false;
						death = "wumpus";
					}
				// If there is no hazard or wumpus, check for loots and automatically have the player obtain it
				else
					{
						Item *loot;
						string itemName;
						size_t batteryFound;
						size_t ammoFound;

						int itemCount = rooms[player.getLocation()].getItemCount();
						for (int i = 0; i < itemCount; i++)
							{
								loot = rooms[player.getLocation()].removeFirstItem();

								itemName = loot -> getName();
								output << "Found " << itemName << endl;

								batteryFound = itemName.find("Batteries");
								ammoFound = itemName.find("Bullets");

								// Check if the item name contains the word "batteries"
								if (batteryFound != string::npos)
									{
										player.setBattery(player.getBattery() + loot -> getValue());
									}
								// Check if the item name contains the word bullets"
								else if (ammoFound != string::npos)
									{
										player.setAmmo(player.getAmmo() + loot -> getValue());
									}
								// Check if hte item found is a silencer
								else if (itemName == "Silencer")
									{
										player.addItem(loot);
										counterIncrement = 2;
									}
								else
									{
										player.addItem(loot);
									}
							};
					};
			};	
	};

// A function to shoot a bullet towards a direction
void shoot(string targetDirection)
	{
		int nextRoom;

		player.setAmmo(player.getAmmo() - 1);

		// Get the room index of the direction the player is shooting to, if there is no room in that direction it will return -1
		nextRoom = rooms[player.getLocation()].getRoomIndex(targetDirection);

		// Upon shooting to a wall, have the bullet enter a random room
		if (nextRoom < 0)
			{
				nextRoom = rooms[player.getLocation()].getRandomIndex();
			};

		// If the bullet hits the wumpus, the player wins
		if (wumpus.getLocation() == nextRoom)
			{
				gameRunning = false;
				winGame = true;
			}
		else
			{
				if (player.getAmmo() <= 0)
					{
						gameRunning = false;
						death = "ammo";
					}
				else
					{
						// Increment the wake-up counter and check if the wumpus is awake
						wakeupCounter += counterIncrement;
						if (wakeupCounter >= wakeupTreshold)
							{
								wumpus.setSleeping(false);
							}
					};
			};
	}