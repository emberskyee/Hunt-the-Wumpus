#ifndef TUNNELS_H
#define TUNNELS_H

//#include "room.h"
#include <iostream>
#include <string>
using namespace std;

// Class DECLARATIONS for the tunnels (edges) here

class tunnels {
public:
	string roomName;
	tunnels* next;

	// Constructor & destructor
	tunnels(string roomName) : roomName(roomName), next(nullptr) {};
	~tunnels() {};
};

#endif
