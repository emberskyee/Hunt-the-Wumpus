#ifndef PLAYER_H
#define PLAYER_H

// Player class DECLARATIONS here

class Player {
public:
	int numArrows;
	bool hasArrows;

	// Constructor
	Player() : numArrows(3), hasArrows(true) {}
	// Destructor
	~Player() {}
};

#endif
