#include "Player.h"



Player::Player(int startLocation)
	{
		location = startLocation;
	}

int Player::getLocation()
	{
		return location;
	};

void Player::setLocation(int newLocation)
	{
		location = newLocation;
	};

int Player::getBattery()
	{
		return battery;
	};

void Player::setBattery(int newBattery)
	{
		battery = newBattery;
		if (battery > 100)
			{
				battery = 100;
			};
	};

int Player::getAmmo()
	{
		return ammo;
	};

void Player::setAmmo(int newAmmo)
	{
		ammo = newAmmo;
	};

// A function to check if an item is in the player's inventory
bool Player::haveItem(string itemName)
	{
		bool itemInInventory = false;

		for (size_t i = 0; i < inventory.size(); i++)
			{
				if (inventory[i]->getName() == itemName)
					{
						itemInInventory = true;
					}
			}

		return itemInInventory;
	};

// A function to add an item to the player's inventory
void Player::addItem(Item* object)
	{
		inventory.push_back(object);
	};

// A function to remove an item from the player's inventory
void Player::removeItem(Item* object)
	{
		for (unsigned int i = 0; i < inventory.size(); i++)
			{
				if (inventory[i] == object)
					{
						inventory.erase(inventory.begin() + i);
					};
			};
	};


Player::~Player()
	{
	}
