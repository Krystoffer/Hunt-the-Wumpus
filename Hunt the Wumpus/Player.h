#pragma once

// Include libraries
#include <vector>

// Include classes
#include "Item.h"

using namespace std;

class Player
	{
		private:
		int location;
		int battery = 100;
		int ammo = 5;
		vector<Item*> inventory;

		public:
		Player(int startLocation);
		int getLocation();
		void setLocation(int newLocation);
		int getBattery();
		void setBattery(int newBattery);
		int getAmmo();
		void setAmmo(int newAmmo);
		bool haveItem(string itemName);
		void addItem(Item* object);
		void removeItem(Item* object);
		~Player();
	};

