#include "Item.h"



Item::Item(string itemName, char itemCategory, int itemValue)
	{
		name = itemName;
		category = itemCategory;
		value = itemValue;
	};

string Item::getName()
	{
		return name;
	};

int Item::getValue()
	{
		return value;
	};

Item::~Item()
	{
	}
