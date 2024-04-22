#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "tunnels.h"
using namespace std;

// Class DECLARATIONS for the room (vertex) here

class room {
public:
	string name;
	bool hasBats;
	bool hasPit;
	bool hasWumpus;
	bool hasArrow;
	int numArrows;
	tunnels* tunnels;
	room* next;
	bool arrowVisited = false;

	// Constructor & destructor
	room(string name) : name(name), hasBats(false), hasPit(false), hasWumpus(false), hasArrow(false), arrowVisited(false),
		next(nullptr), tunnels(nullptr), numArrows(0) {}
	~room() {}
};

#endif
