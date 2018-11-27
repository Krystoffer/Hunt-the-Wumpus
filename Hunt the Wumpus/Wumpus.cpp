#include "Wumpus.h"



Wumpus::Wumpus()
	{
	}

int Wumpus::getLocation()
	{
		return location;
	};

void Wumpus::setLocation(int newLocation)
	{
		location = newLocation;
	};

bool Wumpus::getSleeping()
	{
		return sleeping;
	};

void Wumpus::setSleeping(bool newStatus)
	{
		sleeping = newStatus;
	};


Wumpus::~Wumpus()
	{
	}
