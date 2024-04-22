#ifndef GRAPH_H
#define GRAPH_H

#include "room.h"
#include "tunnels.h"
#include <random>

// Class DECLARATIONS for graph here

class graph {
public:
	room* start;

	// Functions
	void addRoom(string name);
    void addTunnel(string from, string to);
    room* find(string name);
    bool hasEdge(string from, string to);
    void outEdges(string data);
    void inEdges(string data);
    
	// Constructor
	graph();
	// Destructor
	~graph();
};

#endif