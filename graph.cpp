#include "graph.h"
#include <iostream>
#include <string>

// Class DEFINITIONS for graph here

// Default constructor
graph::graph() : start(nullptr) {}
// Destructor
graph::~graph() {}

// Functions
// add a vertex to the graph
void graph::addRoom(string name) {
    room* newRoom = new room(name);
    if (start == nullptr) {
        start = newRoom;
        //cout << "Room " << newRoom->name << " added to graph!" << endl; debug
        return;
    }
    room* current = start;
    while (current->next) {
        current = current->next;
    }
    current->next = newRoom;

    //cout << "Room " << newRoom->name << " added to graph!" << endl; debug
}

// add a directed edge from, to
void graph::addTunnel(string from, string to) {
    room* fromRoom = find(from);
    if (fromRoom) {
        tunnels* newTunnel = new tunnels(to);
        newTunnel->next = fromRoom->tunnels;
        fromRoom->tunnels = newTunnel;
    }

    //cout << "Tunnel from " << from << " to " << to << " added to graph!" << endl; debug
}

room* graph::find(string name) {
    room* current = start;
    while (current) {
        if (current->name == name)
            return current;
        current = current->next;
    }
    return nullptr;
}

// check if an edge exists between two vertices
bool graph::hasEdge(string from, string to) { // change to be undirected
    room* fromRoom = find(from);
    if (fromRoom) {
        tunnels* currentTunnel = fromRoom->tunnels;
        while (currentTunnel) {
            if (currentTunnel->roomName == to)
                return true;
            currentTunnel = currentTunnel->next;
        }
    }
    return false;
}

// print out tunnels of a room
void graph::outEdges(string name) {
    room* room = find(name);
    if (room) {
        //cout << "Out edges of vertex " << name << ": ";
        tunnels* currentTunnel = room->tunnels;
        while (currentTunnel) {
            cout << currentTunnel->roomName << " ";
            currentTunnel = currentTunnel->next;
        }
        cout << endl;
    }
    else {
        cout << "Vertex not found!" << endl;
    }
}

// print in tunnels of a room
void graph::inEdges(string name) {
    if (find(name) == nullptr) {
        cout << "Vertex not found!" << endl;
        return;
    }

    cout << "\nRooms connected to " << name << ": ";
    room* current = start;
    while (current) {
        tunnels* currentTunnel = current->tunnels;
        while (currentTunnel) {
            if (currentTunnel->roomName == name)
                cout << current->name << " ";
            currentTunnel = currentTunnel->next;
        }
        current = current->next;
    }
    //cout << endl;
}