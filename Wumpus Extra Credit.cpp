#include <iostream>
#include <string>
#include <random>
#include <vector>

#include "Player.h"
#include "graph.h"
#include "tunnels.h"
#include "room.h"

using namespace std;

// Function to get a random room name, from "B" to "T", so that we can assign the three features
string assignRandomRoom() {
	random_device random;
	mt19937 gen(random());
	uniform_int_distribution<> dis(2, 20); // Numbers corresponding to B to T
	char letter = dis(gen) + 'A' - 1;
	return string(1, letter);
}
// Function to check if a room has been visited
bool isRoomVisited(const vector<string>& traveledTo, const string& room) {
	return find(traveledTo.begin(), traveledTo.end(), room) != traveledTo.end();
}
// Above functions obtained from ChatGPT

// random room assignment for after the player has left the starting room to ensure the inclusion of A
string assignRandomRoomAfter() {
	random_device random;
	mt19937 gen(random());
	uniform_int_distribution<> dis(1, 20); // Numbers corresponding to A to T
	char letter = dis(gen) + 'A' - 1;
	return string(1, letter);
}

// Game interactions (main) here
int main() {
	// create instance of graph
	graph rooms;
	// create instance of player
	Player player;
	// add all vertices to graph (20 total)
	rooms.addRoom("A"); // starting room
	rooms.start = rooms.find("A");
	rooms.addRoom("B");
	rooms.addRoom("C");
	rooms.addRoom("D");
	rooms.addRoom("E");
	rooms.addRoom("F");
	rooms.addRoom("G");
	rooms.addRoom("H");
	rooms.addRoom("I");
	rooms.addRoom("J");
	rooms.addRoom("K");
	rooms.addRoom("L");
	rooms.addRoom("M");
	rooms.addRoom("N");
	rooms.addRoom("O");
	rooms.addRoom("P");
	rooms.addRoom("Q");
	rooms.addRoom("R");
	rooms.addRoom("S");
	rooms.addRoom("T");
	// make connections (tunnels) between vertices (rooms)
	rooms.addTunnel("A", "B");
	rooms.addTunnel("A", "F");
	rooms.addTunnel("B", "G");
	rooms.addTunnel("B", "C");
	rooms.addTunnel("C", "D");
	rooms.addTunnel("C", "H");
	rooms.addTunnel("D", "E");
	rooms.addTunnel("D", "I");
	rooms.addTunnel("E", "J");
	rooms.addTunnel("F", "G");
	rooms.addTunnel("F", "K");
	rooms.addTunnel("G", "H");
	rooms.addTunnel("G", "L");
	rooms.addTunnel("H", "I");
	rooms.addTunnel("H", "M");
	rooms.addTunnel("I", "J");
	rooms.addTunnel("I", "N");
	rooms.addTunnel("J", "O");
	rooms.addTunnel("K", "P");
	rooms.addTunnel("K", "L");
	rooms.addTunnel("L", "Q");
	rooms.addTunnel("L", "M");
	rooms.addTunnel("M", "R");
	rooms.addTunnel("M", "N");
	rooms.addTunnel("N", "S");
	rooms.addTunnel("N", "O");
	rooms.addTunnel("O", "T");
	rooms.addTunnel("P", "Q");
	rooms.addTunnel("Q", "R");
	rooms.addTunnel("R", "S");
	rooms.addTunnel("S", "T");

	/* Diagram of cave system:
	  A - B - C - D - E
	  |   |   |   |   |
	  F - G - H - I - J
	  |   |   |   |   |
	  K - L - M - N - O
	  |   |   |   |   |
	  P - Q - R - S - T      */

	// randomly assign the wumpus, bats, and pit to one room (not starting)
	string wumpusStart = assignRandomRoom();
	string bats = assignRandomRoom();
	string pit = assignRandomRoom();
	
	// this block is used to set the values of has(blank) to true for the rooms with the three features
	room* hasWumpus = rooms.find(wumpusStart);
	hasWumpus->hasWumpus = true;
	room* hasBats = rooms.find(bats);
	hasBats->hasBats = true;
	room* hasPit = rooms.find(pit);
	hasPit->hasPit = true;

/////////////////////////////////////////////////////////////////////////////////////////
	// debugging
	//cout << "Wumpus room " << wumpusStart << endl;
	//cout << "Bats room " << bats << endl; 
	//cout << "Pit room " << pit << endl;

	//cout << "Room with wumpus: " << hasWumpus->name << endl;
	//cout << "Room with bats: " << hasBats->name << endl;
	//cout << "Room with pit: " << hasPit->name << endl;

	//cout << "Wumpus room true or false: " << hasWumpus->hasWumpus << endl;
/////////////////////////////////////////////////////////////////////////////////////////

	// player interaction
	int choice = 0;
	room* currentRoom = rooms.start;
	bool gameEnd = false;

	cout << "*********************** GAME START ***********************" << endl;

	do {
		cout << "\nHow would you like to proceed?" << endl;
		cout << "1. Go through a tunnel" << endl; // done
		cout << "2. Attack a connected room using an arrow (" << player.numArrows << " arrows remaining)" << endl; // done
		cout << "3. Observe tunnels" << endl; // done
		cout << "4. See what room you are in" << endl; // done
		cout << "5. See room layout" << endl; // done
		cout << "6. Exit" << endl; // done

		cin >> choice;

		if (choice == 1) {
			string toRoom = "";
			cout << "\nWhich tunnel would you like to go through?" << endl;
			rooms.inEdges(currentRoom->name);
			rooms.outEdges(currentRoom->name);
			cin >> toRoom;

			if (currentRoom->name == toRoom) {
				cout << "\nYou are currently in this room!" << endl;
			}
			if (rooms.hasEdge(currentRoom->name, toRoom) || rooms.hasEdge(toRoom, currentRoom->name)) {
				cout << "\nEntering the tunnel to room " << toRoom << "..." << endl;
				currentRoom = rooms.find(toRoom); // update current room
			}
			else {
				cout << "\nThis room does not exist or is not connected to your current room!" << endl;
			}
			if (currentRoom->hasPit) {
				gameEnd = true;
				cout << "\nOh no! You've fallen into a pit! Game over. :(" << endl;
			}
			else if (currentRoom->hasBats) {
				cout << "\nOh no! You ran into a colony of bats that disoriented you! You've stumbled into a random room!" << endl;
				string temp = assignRandomRoomAfter();
				while (!((rooms.hasEdge(temp, currentRoom->name) || rooms.hasEdge(currentRoom->name, temp)))) {
					temp = assignRandomRoomAfter();
				}
				currentRoom = rooms.find(temp);
			}
			else if (currentRoom->hasWumpus) {
				cout << "\nOh no! You ran into the Wumpus!" << endl;
				if (player.numArrows == 0) {
					gameEnd = true;
					cout << "\nYou were out of arrows, so you lost to the Wumpus! Game over. :(" << endl;
				}
				else {
					cout << "\nYou shot an arrow at the Wumpus causing him to flee to a different room!" << endl;
					player.numArrows--;
					cout << "-1 arrows. You now have " << player.numArrows << " arrow(s)." << endl;
					string temp = wumpusStart;
					wumpusStart = assignRandomRoomAfter();
					hasWumpus = rooms.find(wumpusStart);
					while (wumpusStart == temp) {
						wumpusStart = assignRandomRoomAfter();
						hasWumpus->name = wumpusStart;
					}
					room* tempRoom;
					tempRoom = rooms.find(temp);
					tempRoom->hasWumpus = false;
					hasWumpus->hasWumpus = true;
					// debug
					//cout << "Wumpus room: " << hasWumpus->name << endl;
				}
			}
			else if (currentRoom->hasArrow) {
				cout << "\nYou found one or more of your lost arrows!" << endl;
				player.numArrows += currentRoom->numArrows;
				cout << "+" << currentRoom->numArrows << " arrows. You now have " << player.numArrows << " arrows." << endl;
				currentRoom->numArrows = 0;
				currentRoom->hasArrow = false;
			}
		}
		else if (choice == 2) {
			player.numArrows--; // take away an arrow

			bool hitBats = false;
			bool hitPit = false;
			bool hitWumpus = false;

			int iterations = 0;
			string toRoom = "";
			room* shotRoom;
			vector<string> traveledTo; // vector to keep track of rooms the arrow has been to

			cout << "\nChoose a tunnel to aim your bow at: " << endl;
			rooms.inEdges(currentRoom->name);
			rooms.outEdges(currentRoom->name);
			cin >> toRoom;
			shotRoom = rooms.find(toRoom);
			traveledTo.push_back(toRoom);

			iterations++;
			if (currentRoom->name == toRoom) {
				cout << "\nYou are currently in this room!" << endl;
				continue;
			}
			if (rooms.hasEdge(currentRoom->name, toRoom) || rooms.hasEdge(toRoom, currentRoom->name)) {
				cout << "\nShooting an arrow at " << toRoom << "..." << endl; // add sleep timer
			}
			else {
				cout << "\nThis room does not exist or is not connected to your current room!" << endl;
				continue;
			}
			// checks for bats pit or wumpus in the room
			if (shotRoom->hasPit) {
				hitPit = true;
				//debug
				//cout << "Arrow landed in a pit" << endl;
				continue; // do nothing, arrow is gone forever
			}
			else if (shotRoom->hasBats) {
				//debug
				//cout << "Arrow landed in a bat colony" << endl;
				hitBats = true;
				continue; // do nothing, arrow is gone forever
			}
			else if (shotRoom->hasWumpus) {
				cout << "\nYour arrow has hit the Wumpus!! You win!" << endl;
				gameEnd = true;
				hitWumpus = true;
				continue;
			}

			do {
				string temp = "";
				do {
					temp = assignRandomRoomAfter();
				} while (isRoomVisited(traveledTo, temp) || (!(rooms.hasEdge(shotRoom->name, temp) || rooms.hasEdge(temp, shotRoom->name))));
				
				shotRoom = rooms.find(temp);
				traveledTo.push_back(temp);
				//debug
				//cout << "Traveling to room " << temp << endl;

				if (shotRoom->hasPit) {
					hitPit = true;
					//debug
					//cout << "Arrow landed in a pit" << endl;
					continue; // do nothing, arrow is gone forever
				}
				else if (shotRoom->hasBats) {
					hitBats = true;
					//debug
					//cout << "Arrow landed in a bat colony" << endl;
					continue; // do nothing, arrow is gone forever
				}
				else if (shotRoom->hasWumpus) {
					cout << "\nYour arrow has hit the Wumpus!! You win!" << endl;
					gameEnd = true;
					hitWumpus = true;
					continue;
				}
				iterations++;
				//cout << iterations << endl; debug
			} while (!(iterations == 4) && !(hitWumpus || hitBats || hitPit));
			shotRoom->hasArrow = true;
			shotRoom->numArrows++;

			if (hitWumpus == false) { // move wumpus to random room where the player is not and where he wasn't before
				string temp = wumpusStart;
				wumpusStart = assignRandomRoomAfter();
				hasWumpus = rooms.find(wumpusStart);
				while ((wumpusStart == temp) || (wumpusStart == currentRoom->name)) {
					wumpusStart = assignRandomRoomAfter();
					hasWumpus->name = wumpusStart;
				}
				room* tempRoom;
				tempRoom = rooms.find(temp);
				tempRoom->hasWumpus = false;
				hasWumpus->hasWumpus = true;
				// debug
				//cout << "Wumpus room: " << hasWumpus->name << endl;
			}
			//debug
			//cout << "End shot room " << shotRoom->name << " has arrows " << shotRoom->hasArrow << " num arrows " << shotRoom->numArrows << endl;
		}
		else if (choice == 3) {
			if (rooms.hasEdge(hasWumpus->name, currentRoom->name) || rooms.hasEdge(currentRoom->name, hasWumpus->name)) {
				cout << "\nYou smell an animal smell in the air... The wumpus is nearby!" << endl;
				continue;
			}
			if (rooms.hasEdge(hasBats->name, currentRoom->name) || rooms.hasEdge(currentRoom->name, hasBats->name)) {
				cout << "\nYou hear a screeching noise... A colony of bats is nearby!" << endl;
				continue;
			}
			if (rooms.hasEdge(hasPit->name, currentRoom->name) || rooms.hasEdge(currentRoom->name, hasPit->name)) {
				cout << "\nYou feel a breeze... A pit is nearby!" << endl;
				continue;
			}
			cout << "\nYou notice nothing special." << endl;
		}
		else if (choice == 4) {
			cout << "\nThe room you are currently in is: Room " << currentRoom->name << endl;
		}
		else if (choice == 5) {
			cout << "\nA - B - C - D - E\n" <<
				"|   |   |   |   |\n" <<
				"F - G - H - I - J\n" <<
				"|   |   |   |   |\n" <<
				"K - L - M - N - O\n" <<
				"|   |   |   |   |\n" <<
				"P - Q - R - S - T\n";
		}
		else if (choice == 6) {
			cout << "\nGame ended manually. Goodbye!" << endl;
		}
	} while (choice != 6 && gameEnd == false);
}