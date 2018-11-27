#pragma once

// Include libraries
#include <string>
#include <vector>
#include <iostream>

// Include classes
#include "Item.h"

using namespace std;

class Room
	{
		private:
		string name;
		string description;
		string hazard;
		vector<Item*> objects;
		string direction[3];
		int target[3];

		public:
		Room(string roomName, string roomDescription, string direction1, int target1, string direction2, int target2, string direction3, int target3);
		string getName();
		string getDescription();
		void getAdjacent(int *arr, int size);
		string getDirection();
		int getRoomIndex(string targetDirection);
		int getRandomIndex();
		string getHazard();
		void setHazard(string newHazard);
		int getItemCount();
		void addItem(Item* object);
		Item* removeFirstItem();
		~Room();
	};

