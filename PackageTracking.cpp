//
//  PackageTracking.cpp
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#include "PackageTracking.h"

using namespace std;

PackageTracking::PackageTracking(const string& strnum) {
	package = strnum;//Works with or without x)
	head = NULL;
	currentPointer = NULL;
}

// add a new update
void PackageTracking::m_addUpdate( const string& status, const string& location, const time_t& timeUpdated){
	ShippingStatus* temp = new ShippingStatus(status, location, timeUpdated);
	if (head == NULL) {
		head = temp;
		currentPointer = temp;
	}
	else {
		ShippingStatus* current = head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = temp;
		temp->prev = current;
		currentPointer = temp;
	}
	
}

bool PackageTracking::m_moveBackward()//move iterator one step earlier in time
{
	if (currentPointer == NULL) {
		return false;
	}
	if (currentPointer->prev == NULL) {
		return false;
	}
	currentPointer = currentPointer->prev;
	return true;
}

bool PackageTracking::m_moveForward()//move iterator one step forward in time
{
	if (currentPointer == NULL) {
		return false;
	}
	if (currentPointer->next == NULL) {
		return false;
	}
	currentPointer = currentPointer->next;
	return true;
}

string PackageTracking::m_getLocation()//return the location of the current update
{
	return currentPointer->m_getLocation();
}

time_t PackageTracking::m_getTime()//return the time of the current update
{
	return currentPointer->m_getTime();
}

string PackageTracking::m_getStatus()//return the status of the current update
{
	return currentPointer->m_getStatus();
}

int PackageTracking::m_getNumofUpdate() const // get the total numbers of shipping status updates
{
	int total = 0;
	ShippingStatus* temp = head;
	while (temp != NULL) {
		total++;
		temp = temp->next;
	}
	return total;
}

void PackageTracking::m_printPreviousUpdates() //print all previous updates in the shipping chain when the package was shipped, all the way up to (but not including) the current update you are viewing (may not be the most recent update)
{	
	ShippingStatus* temp = head;
	while (temp != currentPointer) {
		temp->printShippingStatus();
		temp = temp->next;
	}
}

//print all updates from the current update you are viewing to the last update in the tracking chain
void PackageTracking::m_printFollowingUpdates()
{
	ShippingStatus* temp = currentPointer;
	while (temp != NULL) {
		temp->printShippingStatus();
		temp = temp->next;
	}
}

void PackageTracking::m_printFullTracking()//print all the updates in the tracking chain.
{
	ShippingStatus* temp = head;
	while (temp != NULL) {
		temp->printShippingStatus();
		temp = temp->next;
	}
}

bool PackageTracking::m_setCurrent(const time_t& timeUpdated)//view an update.
{
	ShippingStatus* temp = head;
	while (temp != NULL) {
		if (temp->m_getTime() == timeUpdated) {
			currentPointer = temp;
			return true;
		}
		temp = temp->next;
	}
	return false;
}


bool PackageTracking::m_readTrackingFile(string fileName) {
	ifstream inputFile;
	inputFile.open(fileName.c_str());
	string temp;
	if (inputFile.is_open()) {
		while (!inputFile.eof()) {
			getline(inputFile, temp);
			if (temp == "new") {
				getline(inputFile, temp);
				int f = temp.find(";");
				string tempStatus = temp.substr(0, f);
				int s = temp.find(";", f + 1);
				string tempLocation = temp.substr(f + 1, s);
				string tempTime = temp.substr(s + 1);
				time_t tTime = time(tempTime);
				m_addUpdate(tempStatus, tempLocation, tTime);
			}
			else if (temp == "back") {
				m_moveBackward();
			}
			else if (temp == "forward") {
				m_moveForward();
			}
		}
	}
	else {
		return false;
	}
	return true;
}

time_t PackageTracking::time(string strTime) {
	long total = 0;
	for (size_t i = 0; i<strTime.size(); i++) {
		total *= 10;
		total += strTime[i] - '0';
	}
	time_t temp = total;
	return temp;
}
