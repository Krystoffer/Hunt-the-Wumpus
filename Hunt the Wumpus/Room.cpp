#include "Room.h"



Room::Room(string roomName, string roomDescription, string direction1, int target1, string direction2, int target2, string direction3, int target3)
	{
		name = roomName;
		description = roomDescription;
		direction[0] = direction1;
		direction[1] = direction2;
		direction[2] = direction3;
		target[0] = target1;
		target[1] = target2;
		target[2] = target3;
	};

string Room::getName()
	{
		return name;
	};

string Room::getDescription()
	{
		return description;
	};

// A function to fill an array with the adjacent room indexes
void Room::getAdjacent(int *arr, int size)
	{
		for (int i = 0; i < size; i++)
			{
				*(arr + i) = target[i];
			};
	};

// A function to print out the possible directions that a player can go
string Room::getDirection()
	{
		string output;

		//cout << "You can go " << direction[0] << ", " << direction[1] << ", or" << direction[2] << endl;
		output = "You can go " + direction[0] + ", " + direction[1] + ", or " + direction[2];

		return output;
	};

// A function to return the room index of an adjacent room in the specified direction. If there is no room in that direction it will return -1
int Room::getRoomIndex(string targetDirection)
	{
		int roomIndex = -1;
		for (size_t i = 0; i < 3; i++)
			{
				if (direction[i] == targetDirection)
					{
						roomIndex = target[i];
					};
			}

		return roomIndex;
	};

// A function to get choose a random room index from the 3 adjacent rooms
int Room::getRandomIndex()
	{
		return target[rand() % 3];
	};

string Room::getHazard()
	{
		return hazard;
	};

void Room::setHazard(string newHazard)
	{
		hazard = newHazard;
	};

int Room::getItemCount()
	{
		return objects.size();
	};

// A function to add an item into the room
void Room::addItem(Item* object)
	{
		objects.push_back(object);
	};

// A function to remove the first item from the room's item vector
Item* Room::removeFirstItem()
	{
		Item *firstItem;
		firstItem = objects[0];

		objects.erase(objects.begin());

		return firstItem;
	};

Room::~Room()
	{
	}
