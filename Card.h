#ifndef CARD_H
#define CARD_H
#include<iostream>
#include<vector>
#include <random>

using namespace std;

class Card {
	private:
		int* cardType; // Stores the type of the card as a pointer Type
	public:
		enum cardType {
			bomb = 1,
			reinforcement,
			blockade,
			airlift,
			diplomacy
		};

		Card() {
			this->cardType = new int(5);
		}
		Card(int cardType) {
			this->cardType = new int(cardType);
		}
		string getCardTypeName() const {
			switch (*cardType) {
			case bomb:
				return "Bomb";
			case reinforcement:
				return "Reinforcement";
			case blockade:
				return "Blockade";
			case airlift:
				return "Airlift";
			case diplomacy:
				return "Diplomacy";
			default:
				return "Unknown";
			}
		}

		// Destructor implementation
		~Card() {
			delete cardType;
		  //  cout << "Card object destroyed." << endl;
		}
		// clone method
		Card(const Card& other) {
			cardType = new int(*(other.cardType)); // Allocate memory and copy the value // Copy the card type from the other object
			cout << "Copy constructor called. Card type: " << cardType << endl;
		}
		// Asinment Operator
		Card& operator=(const Card& other) {
			if (this != &other) {
				delete cardType; // Clean up the old memory
				cardType = new int(*(other.cardType)); // Allocate new memory and copy the value
			}
			return *this;
		}

		// stream insertion operator
		friend ostream& operator<<(ostream& out, const Card& card) {
			out << "Card type: " << card.getCardTypeName();
			return out;
		}

		// Getter for card type
		int getCardType() const {
			return *cardType; // Return the dereferenced value of the pointer
		}
		// Method to play the card
		void play() {
			cout << "Playing card of type: " << getCardTypeName() << endl;
		}
};

class Deck {
	private:
		vector<Card*> mainDeck;
		
	public:
		Deck() {
			for (int i = 0; i < 5; ++i) {
				mainDeck.push_back(new Card(Card::bomb));
				mainDeck.push_back(new Card(Card::reinforcement));
				mainDeck.push_back(new Card(Card::diplomacy));
				mainDeck.push_back(new Card(Card::airlift));
				mainDeck.push_back(new Card(Card::blockade));
			}
			shuffle();
		}
		
		~Deck() {
			for (int i = 0; i < mainDeck.size(); i++) {
				delete mainDeck[i];
			}
			mainDeck.clear();
		};
		
		Deck(const Deck& other) {
			for (Card* card : other.mainDeck) {
				mainDeck.push_back(new Card(*card)); // Deep copy each Card in the vector
			}
		}

		Deck& operator=(const Deck& other) {
			if (this != &other) {
				mainDeck.clear();

				for (Card* card : other.mainDeck) {
					mainDeck.push_back(new Card(*card)); // Create a new Card for each element
				}
			}
			return *this;
		}
		
		void shuffle() {
			random_device dev;
			mt19937 rng(dev());
			
			int totalSize = mainDeck.size();
			vector<Card*> temp;
			int randomNum;
			for (int i = 0; i < totalSize; i++) {
				uniform_int_distribution<mt19937::result_type> dist(0, mainDeck.size() - (i + 1));
				randomNum = dist(rng);
				temp.push_back(mainDeck[randomNum]);
				removeCard(randomNum);
			}
			mainDeck = temp;
		}
		
		void removeCard(int index) {
			vector<Card*> temp;
			int tIndex = 0;
			for (int i = 0; i < mainDeck.size(); i++) {
				if (i == index) {
					delete mainDeck[i];
					continue;
				}
				temp.push_back(mainDeck[i]);
				tIndex++;
			}
			mainDeck = temp;
		}

		Card* draw() {
			if (!mainDeck.empty()) {
				Card* drawnCard = mainDeck.back();  // Draw from the top (end of vector)
				mainDeck.pop_back();                // Remove it from the deck
				return drawnCard;                   // Return the drawn card
			}
			return nullptr;  // Return blank card if the deck is empty
		}

		void addCard(Card* card) {
			mainDeck.push_back(card);
		}
		
		friend ostream& operator<<(ostream& out, const Deck& deckObj) {
			out << "Deck contains: " << endl;
			for (Card* card : deckObj.mainDeck) {
				out << card << endl; // Use the stream insertion operator from the Card class
			}
			return out;
		}
};

class Hand {
	private:
		vector<Card*> handCards;  // Cards in the hand
		Deck& sharedDeck; 
		
	public:
		Hand(Deck& deck) : sharedDeck(deck) {}

		// Copy constructor (deep copy of handCards, but sharedDeck remains a reference)
		Hand(const Hand& other) : sharedDeck(other.sharedDeck) {
			for (Card* card : other.handCards) {
				handCards.push_back(new Card(*card)); // Deep copy each card
			}
		}

		// Assignment operator (deep copy)
		Hand& operator=(const Hand& other) {
			if (this != &other) {
				// Clear existing hand
				for (Card* card : handCards) {
					delete card;
				}
				handCards.clear();

				// Deep copy the handCards from other
				for (Card* card : other.handCards) {
					handCards.push_back(new Card(*card)); // Deep copy each card
				}

				// Reference to the shared deck remains unchanged (sharedDeck is not reassigned)
			}
			return *this;
		}

		// Destructor (clean up the dynamically allocated cards)
		~Hand() {
			for (Card* card : handCards) {
				delete card;
			}
			handCards.clear();
		}

		// Draws a card from the shared Deck and adds it to the hand
		void drawCard() {
			Card* drawnCard = new Card(*sharedDeck.draw());
			if (drawnCard != nullptr) {
				handCards.push_back(drawnCard);
				cout << "Card drawn and added to hand." << *drawnCard << endl;
			}
			else {
				cout << "The deck is empty, no card drawn." << endl;
			}
		}

		// Plays a card from the hand at the specified index
		void playCard(int index) {
			if (index >= 0 && index < handCards.size()) {
				Card* cardToPlay = handCards.at(index);

				// Play the card (assuming the Card class has a `play` method)
				cardToPlay->play();

				// Remove the card from the hand
				handCards.erase(handCards.begin() + index);

				// Add the played card back to the deck
				sharedDeck.addCard(cardToPlay);

				cout << "Card played and added back to the deck." << endl;
			}
			else {
				cout << "Invalid index. No card played." << endl;
			}
		}

		// Display the cards in the hand
		void showHand() const {
			cout << "Hand contains: " << endl;
			for (int i = 0; i < handCards.size(); ++i) {
				cout << i << ": " << *handCards[i] << endl;  // Assuming Card class has a stream operator defined
			}
		}

		// Stream insertion operator to display hand contents
		friend ostream& operator<<(ostream& out, const Hand& hand) {
			out << "Hand contains: " << endl;
			for (Card* card : hand.handCards) {
				out << *card << endl; // Use the stream insertion operator from Card class
			}
			return out;
		}
};

#endif // CARD_H