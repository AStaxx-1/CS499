//============================================================================
// Name        : LinkedList.cpp
// Author      : Angelica Strack
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
	//creates a new structure for a node in a list - the structure is made of a bid, and the pointer to the next node in the list
	struct listNode {
		 Bid bid;
		 listNode* next;
	// default constructor for this internal structure - automatically initializes an empty struct with the next pointer to be null
	listNode() {
		next = nullptr;
	}

	//initialize a node with a bid in it
	listNode(Bid aBid){
		bid = aBid;
		next = nullptr;
	}
	};


	 listNode* head;
	 listNode* tail;
	 int size =0;



public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
    void insertionSort();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
	//ensures when the list is initialized it is created with a head & tail node - gives a default value of null for both because the list is empty
	head = nullptr;
	tail = nullptr;

}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
	listNode* newNode = new listNode(bid);

	if (head == nullptr) {
		head = newNode; //because the list was empty this assigns both the head and the tail to the newNode in the list
		tail = newNode;
	}

	else {
			tail -> next = newNode; //if the list is not empty, the current tail sets its "next" pointer to the newest node in the list
			tail = newNode; //the new node becomes the tail of the list
		}
	size += 1; //increases the size of the list
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
	listNode* newNode = new listNode(bid);

	//if the list is empty the newNode becomes both the tail and the head
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	//if the list is not empty, the next pointer for this node is set to the current head of the list and the head of the list becomes the new node
	else {
		newNode -> next = head;
		head = newNode;

	}

	size += 1; //increase the size of the list
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
	listNode* curNode = head;

	//if we were to just print curNode it would print the location in memory, not the contents. This ensure it prints each part of the bid structure stored in this node
	while (curNode != nullptr){
		cout << curNode->bid.bidId << ":" << curNode->bid.title << " | " << curNode->bid.amount << " | " << curNode->bid.fund << endl;
		curNode = curNode -> next;
	}

}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
	string key = bidId;
	listNode* curNode = head; //current node
	listNode* sucNode = curNode->next; //look ahead node (successor node)

	//need to make sure the current node (head) isn't the one we are trying to remove
	if(curNode->bid.bidId == key){ //if the current node matches the searched bidId
		delete curNode; //delete the current node
		head = sucNode; //make the head of the list the successor node - the next pointer for this node should be fine so we don't need to change next
		return;
	}

	while (curNode != nullptr){
		//if the head node was not the one we were trying to delete then we go to this loop
		if (sucNode->bid.bidId == key){ //looks at the successor node to try to match with our "to-delete" bidId
			listNode* tmpNode = sucNode->next; //assigns a temporary node to the value after our successor node
			curNode->next = tmpNode; //assigns the value that follows curNod to our temp value
			delete sucNode;	//deletes the successor node that matches our search key
			size-= 1; //decreases the size of the list
			return;

		}
		curNode = curNode->next;//increments our current node we are looking at
		sucNode = curNode->next;//increments the successor node we are looking at
	}

}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
	listNode* curNode = head;
	string key = bidId;
	Bid bid; //initializes an empty bid


	while (curNode != nullptr){
		if (curNode->bid.bidId == key){ //if the current nodes bidId matches what we are looking for, returns the bid from the current node
			return curNode->bid;
		}
		curNode = curNode->next; //increments the current node we are looking at
	}
	//if the while loop reaches the end of the list without finding the selected bidId, method returns an empty bid otherwise the program would hang if not found
	return bid;
}


/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

void LinkedList::insertionSort(){
	listNode* curr_node;
	listNode* curr_node_previous;
	listNode* right;
	listNode* right_previous = head;
	listNode* next_node = head->next;

	if (!head && !head->next){
		return;
	}

	while (next_node) { // continues to iterate through the linked list as long as the next node isn't empty
		curr_node = head;
		right = next_node;
		next_node = right->next;
		if (right->bid.bidId.compare(head->bid.bidId) < 0){ //if the node to the right of the head is lower, that node becomes the head
			head = right;
		}
		else{
			while (curr_node->next && (curr_node->bid.bidId.compare(right->bid.bidId)<0)){ //while there are nodes to compare and the node current node is lower than the next keep iterating
				curr_node_previous = curr_node; // shifts the "previous node" variable to our current node
				curr_node = curr_node->next; //shifts the current node variable to the next node
			}
			curr_node_previous->next = right;
			if (right_previous->bid.bidId.compare(right->bid.bidId)<0){ // makes sure the nodes on the right stay in order
				right_previous = right;
			}

		}
		right->next = curr_node; // continues shifting our variable down the list
		right_previous-> next = next_node;
	}
	tail = right_previous;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  6. Sort Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:

        	cout << "Enter ID of Bid to delete: ";
        	cin >> bidKey;

            bidList.Remove(bidKey);

            break;

        case 6:
        	bidList.insertionSort();
        	bidList.PrintList();
        	break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
