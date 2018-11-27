#pragma once

// Include libraries
#include <string>

// Include classes

using namespace std;

class Item
	{
		private:
		string name;
		char category; // C for consumable (instant use), E for equipment (use when event trigerred)
		int value;

		public:
		Item(string itemName, char itemCategory, int itemValue);
		string getName();
		int getValue();
		~Item();
	};

