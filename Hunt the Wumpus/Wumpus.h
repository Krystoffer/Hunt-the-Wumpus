#pragma once

// Include libraries

// Include classes

using namespace std;

class Wumpus
	{
		private:
		int location;
		bool sleeping = true;

		public:
		Wumpus();
		int getLocation();
		void setLocation(int newLocation);
		bool getSleeping();
		void setSleeping(bool newStatus);		
		~Wumpus();
	};

