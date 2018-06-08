//
//  ShippingStatus.cpp
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#include "ShippingStatus.h"
#include <string>
#include <iostream>

using namespace std;

ShippingStatus::ShippingStatus() {
	next = NULL;
	prev = NULL;
}

ShippingStatus::ShippingStatus(const string& status, const string& location, const time_t& timeUpdated) {
	this->status = status;
	this->location = location;
	this->timeUpdated = timeUpdated;
	/*next = NULL;
	prev = NULL;*/
}

string ShippingStatus::m_getStatus(){
	return status;
}

string ShippingStatus::m_getLocation(){
	return location;
}

time_t ShippingStatus::m_getTime() {
	return timeUpdated;
}

void ShippingStatus::printShippingStatus() {
	cout << "Status: " << status << endl;
	cout << "Location: " << location << endl;
	cout << "Time Updated: " << timeUpdated << endl;
}