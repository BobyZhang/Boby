
#pragma once
#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <iostream>
#include <string>
#include <vector>
#include "linkstack.h"
#include "linkqueue.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::wstring;
using std::vector;

class Input_inf
{
private:
	char statu;          // car's inf, Left or Arrive
	string plate;        // the car's plate
	int time;            // car's Left time or Arrive time
	bool valid;          // input whether valid

public:
	// constructor
	// default the input is valid
	Input_inf() { valid = true; time = 999999999; };

	// get inputed information
	char getStatu() { return statu; }
	string getPlate() { return plate; }
	int getTime() { return time; }
	bool isValid() { return valid; }

	// set value
	void setStatu(const char _statu) { statu = _statu; }
	void setPlate(const string _plate) { plate = _plate; }
	void setTime(const int _t) { time = _t; }
	void setValid(const bool _v) { valid = _v; }
};

class Car
{
private:
	string plate;        // the car's plate
	int arriveTime;      // the time of car arrive
	int parkedTime;      // the time of car park success
	bool parked;         // mark the car whether find a park lot

public:
	// constructor
	Car();
	Car(Input_inf);

	// get car's plate
	string getPlate() { return plate; }

	bool isParkedSuccess() { return parked; }

	// if parked success, set parked time and return this car
	Car parkedSuccess(int _parkTime);

	// left and resolution of billing
	int parkDuration(int _leftTime);
};

class Parkinglot
{
private:
	int maxSize;                // the Parking lot's capacity
	float perMuch;              // how much per priod
	int currTime;               // restric the input time, must be new

	AStack<Car> *parkLot;       // 
	AStack<Car> *tempLot;       //
	LQueue<Car> *queuing;       //

public:
	// constructor
	Parkinglot(int _size, float _charge);

	// open a business
	void openBusiness();

	// input information
	Input_inf input();

	// arrange car's arrive
	void settleArrive(Input_inf _inf);

	// arrange car's left
	void settleLeft(Input_inf _inf);

	// print parking information
	void printParkinglot();
};

// handle input information
Input_inf handleInput(string _s);

#endif