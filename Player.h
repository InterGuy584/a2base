#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "Map.h"
#include "Card.h"
#include "Order.h"

using namespace std;

class Player {
	
	int* territoriesCount = new int(0);
	int* handCount = new int(0);
	int* orderListCount = new int(0);
	
	public:
		string name;                     // Player's name as a regular string
		string* territories;             // Dynamic array of owned string names
		string* hand;                    // Dynamic array of card types
		string* orderList;               // Dynamic array of order types
		
		// Constructors
		Player() {
			name = "Unnamed Player";
			territories = new string[0];      // Initialize empty vector for territories
			hand = new string[0];             // Initialize empty vector for cards
			orderList = new string[0];        // Initialize empty vector for orders
		}
		
		// Assume that the arrays were made to populaate this class'
		//   attributes, and can simply be pointed to.
		Player(string name, string* tList, string* cList, string* oList) {
			name = name; 
			territories = tList;
			hand = cList;
			orderList = oList;
		}
		
		Player(const Player& rhs) {
			Player& crhs = const_cast <Player&>(rhs);
			
			name = string(crhs.name);

			// Deep copies of all of the lists' elements
			territories = new string[crhs.getTerritoriesCount()];
			for (int i = 0; i < crhs.getTerritoriesCount(); i++) {
				appendstring(string(crhs.territories[i]));  // Deep copy of each string
			}

			hand = new string[crhs.getHandCount()];
			for (int i = 0; i < crhs.getHandCount(); i++) {
				appendToHand(string(crhs.hand[i]));  // Deep copy of each string
			}

			orderList = new string[crhs.getOrderListCount()];
			for (int i = 0; i < crhs.getOrderListCount(); i++) {
				appendOrder(string(crhs.orderList[i]));  // Deep copy of each string
			}
		}

		// Assignment operator (Deep Copy)
		Player& operator=(const Player& rhs) {
			if (this != &rhs) {
				Player& crhs = const_cast <Player&>(rhs);
				
				name = string(crhs.name);

				// Deep copies of all of the lists' elements
				territories = new string[crhs.getTerritoriesCount()];
				for (int i = 0; i < crhs.getTerritoriesCount(); i++) {
					appendstring(string(crhs.territories[i]));  // Deep copy of each string
				}

				hand = new string[crhs.getHandCount()];
				for (int i = 0; i < crhs.getHandCount(); i++) {
					appendToHand(string(crhs.hand[i]));  // Deep copy of each string
				}

				orderList = new string[crhs.getOrderListCount()];
				for (int i = 0; i < crhs.getOrderListCount(); i++) {
					appendOrder(string(crhs.orderList[i]));  // Deep copy of each string
				}
			}
			
			return *this;
		}
		
		// Destructor
		~Player() {
			delete territoriesCount;
			delete [] territories;
			delete handCount;
			delete [] hand;
			delete orderListCount;
			delete [] orderList;
		};

		// Methods to return certain player properties
		
		// This deep copies the entire list for now
		string* territoriesToAttack() {
			int len = ttaCount();
			string* atList = new string[len];
			for (int i = 0; i < len; i++) {
				atList[i] = string(territories[i]);
			}
			return atList;
		}
		int ttaCount() {
			return *territoriesCount;  // Placeholder, returns the list length
		}
		
		string* territoriesToDefend() {
			int len = ttdCount();
			string* dtList = new string[len];
			for (int i = 0; i < len; i++) {
				dtList[i] = string(territories[i]);
			}
			return dtList;
		}
		int ttdCount() {
			return *territoriesCount;  // Placeholder, returns the list length
		}

		void issueOrder(string order) {
			appendOrder(order);  // Adds an order to the list
		}

		string* getOrderList() {
			return orderList;  // Returns order list
		}
		
		// array methods
		int getTerritoriesCount() {
			return *territoriesCount;
		}
		
		void appendstring(string t) {
			string* temp = new string[*territoriesCount + 1];
			for (int i = 0; i < *territoriesCount; i++) {
				temp[i] = territories[i];
			}
			temp[*territoriesCount] = string(t);
			territories = temp;
			*territoriesCount = *territoriesCount + 1;
		}
		
		int getHandCount() {
			return *handCount;
		}
		
		void appendToHand(string c) {
			string* temp = new string[*handCount + 1];
			for (int i = 0; i < *handCount; i++) {
				temp[i] = hand[i];
			}
			temp[*handCount] = string(c);
			hand = temp;
			*handCount = *handCount + 1;
		}
		
		int getOrderListCount() {
			return *orderListCount;
		}
		
		void appendOrder(string o) {
			string* temp = new string[*orderListCount + 1];
			for (int i = 0; i < *orderListCount; i++) {
				temp[i] = orderList[i];
			}
			temp[*orderListCount] = string(o);
			orderList = temp;
			*orderListCount = *orderListCount + 1;
		}
		
		friend ostream& operator<<(ostream& out, const Player& P) {
			Player& cP = const_cast <Player&>(P);
			
			out << "Player Name: " << cP.name << endl;

			out << "Territories owned: ";
			for (int i = 0; i < cP.getTerritoriesCount(); i++) {
				if (i != 0) { out << ", "; }
				out << cP.territories[i];
			}
			out << endl;

			out << "Orders: ";
			for (int i = 0; i < cP.getOrderListCount(); i++) {
				if (i != 0) { out << ", "; }
				out << cP.orderList[i];  // Get the order type (they will likely be stored by type(?))
			}
			out << endl;

			// TO-DO: Find out what cards are and what they do
			out << "Cards: ";
			for (int i = 0; i < cP.getHandCount(); i++) {
				if (i != 0) { out << ", "; }
				out << cP.hand[i];  // Get the card type (they will likely be stored by type(?))
			}
			out << endl;

			return out;
		}
};

class PlayerDriver {
	public:
		static Player* makeThreePlayers() {
			Player p1 = Player();
			p1.name = "Alice";
			p1.appendstring("The North");
			p1.appendstring("The South-West");
			p1.appendToHand("4 of hearts");
			p1.appendToHand("7 of clubs");
			p1.appendOrder("Attack");
			p1.appendOrder("Defend");
			
			Player p2 = Player();
			p2.name = "Bob";
			p2.appendstring("The North-East");
			p2.appendstring("The South-East");
			p2.appendToHand("Jack of spadess");
			p2.appendToHand("10 of spadess");
			p2.appendOrder("Attack");
			p2.appendOrder("Defend");
			p2.appendOrder("Defend");
			
			Player p3 = Player();
			p3.name = "Charlie";
			p3.appendstring("The North-West");
			p3.appendstring("The South");
			p3.appendToHand("2 of clubs");
			p3.appendToHand("6 of diamonds");
			p3.appendOrder("Defend");
			p3.appendOrder("Attack");
			p3.appendOrder("Defend");
			
			Player* pList = new Player[3];
			pList[0] = p1;
			pList[1] = p2;
			pList[2] = p3;
			
			return pList;
		};
		
		// Assumes there are 3 players in the list
		static string testPlayers(Player* pList) {
			string toReturn = "";
			toReturn = toReturn + "Testing player actions...\n";
			
			toReturn = toReturn + "\nGetting territories to attack from p1...\n- ";
			string* attackT = pList[0].territoriesToAttack();
			int atCount = pList[0].ttaCount();
			for (int i = 0; i < atCount; i++) {
				if (i != 0) { toReturn = toReturn + ", "; }
				toReturn = toReturn + attackT[i];
			}
			delete [] attackT;
			
			toReturn = toReturn + "\n\nGetting territories to defend from p2...\n- ";
			string* defendT = pList[1].territoriesToDefend();
			int dtCount = pList[1].ttdCount();
			for (int i = 0; i < dtCount; i++) {
				if (i != 0) { toReturn = toReturn + ", "; }
				toReturn = toReturn + defendT[i];
			}
			delete [] defendT;
			
			toReturn = toReturn + "\n\np3's current orders are...\n- ";
			for (int i = 0; i < pList[2].getOrderListCount(); i++) {
				if (i != 0) { toReturn = toReturn + ", "; }
				toReturn = toReturn + pList[2].orderList[i];
			}
			toReturn = toReturn + "\nissuing an extra \"Attack\" order to p3...";
			pList[2].issueOrder("Attack");
			toReturn = toReturn + "\np3's current orders are...\n- ";
			for (int i = 0; i < pList[2].getOrderListCount(); i++) {
				if (i != 0) { toReturn = toReturn + ", "; }
				toReturn = toReturn + pList[2].orderList[i];
			}
			
			return toReturn;
		}
};

#endif // PLAYER_H