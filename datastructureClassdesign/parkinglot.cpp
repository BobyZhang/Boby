
#include <algorithm>
#include <cstdlib>
#include <cstdlib>
#include "parkinglot.h"


Input_inf handleInput(string _s)
{
	// store input inf
	// default input is valid
	Input_inf result;

	string pure_s; // no Chinese

	// Frist, transfer chinese char to english char
	for (int i = 0; i < _s.size(); ++i)
	{
		string t;
		// if the char is 0 - 255
		if (_s[i] > 0 && _s[i] < 255)
		{
			t = _s[i];
		}
		else
		{
			t = _s.substr(i, 2);
			++i;
		}

		// swich not support string
		// translate Chinese char to English char
		if (t == "£¨") {
			pure_s.append("(");
		}
		else if (t == "£©") {
			pure_s.append(")");
		}
		else if (t == "¡®") {
			pure_s.append("'");
		}
		else if (t == "¡¯") {
			pure_s.append("'");
		}
		else if (t == "£¬") {
			pure_s.append(",");
		}
		else {
			pure_s.append(t);
		}
	}

	// if also have other char beyong 0 - 255, it's valid
	for (int i = 0; i < pure_s.size(); ++i)
	{
		if (pure_s[i] < 0 || pure_s[i] > 255)
		{
			result.setValid(false);
			return result;
		}
	}

	// remove all space
	pure_s.erase(remove_if(pure_s.begin(), pure_s.end(), isspace), pure_s.end());  // isspace judge wether space

	// tarnsfer lower char to upper
	for (int i = 0; i < pure_s.size(); ++i)
	{
		if (pure_s[i] >= 'a' && pure_s[i] <= 'z') pure_s[i] -= 32;
	}

	
	vector<string> split_v;  // use to split the String

	// judge start and end
	if (pure_s[0] != '(' || pure_s[pure_s.size() - 1] != ')')
	{
		// if strat or end is invalid, return invalid inf
		result.setValid(false);
		return result;
	}

	// remove start and end
	pure_s = pure_s.substr(1, pure_s.size() - 2);

	// split the string
	int index = 0;          // mark postion of the Vector
	split_v.push_back("");
	for (int i = 0; i < pure_s.size(); ++i)
	{
		if (pure_s[i] == ',')
		{
			split_v.push_back("");
			++index;
		}
		else
		{
			split_v[index] += pure_s[i];
		}
	}

	// if the number of split isn't 3, it's invalid input
	if (split_v.size() != 3)
	{
		result.setValid(false);
		return result;
	}

	// judge Left or Arrive statu
	if (split_v[0][0] != '\'' || split_v[0][2] != '\'')
	{
		// if the start and end isn't '\'', it's invalid input
		result.setValid(false);
		return result;
	}
	// remove '\''
	split_v[0] = split_v[0].substr(1, split_v[0].size() - 2);
	// if statu content is invalid
	if (split_v[0].size() != 1 ||
		(split_v[0][0] != 'A' && split_v[0][0] != 'D' && split_v[0][0] != 'E'))
	{
		result.setValid(false);
		return result;
	}
	// if statu content is valid, set result's value
	else
	{
		result.setStatu(split_v[0][0]);
	}

	// judge car's plate
	for (int i = 0; i < split_v[1].size(); ++i)
	{
		// constraint the plate is digit and letter
		if (split_v[1][i] >= 48 && split_v[1][i] <= 57
			|| split_v[1][i] >= 65 && split_v[1][i] <= 90)
		{
			continue;
		}
		else
		{
			result.setValid(false);
			return result;
		}
	}
	// car's plate is valid, set value
	result.setPlate(split_v[1]);

	// judge time
	// constraint time just have 9 digit
	if (split_v[2].size() > 9)
	{
		result.setValid(false);
		return result;
	}
	// whether digit valid
	for (int i = 0; i < split_v[2].size(); ++i)
	{
		// constraint the time is diget
		if (split_v[2][i] >= '0' && split_v[2][i] <= '9')
		{
			continue;
		}
		else
		{
			result.setValid(false);
			return result;
		}
	}
	// set time
	int time = atoi(split_v[2].c_str());	// transfer to int
	result.setTime(time);

	// input is valid
	result.setValid(true);

	return result;
}



//
//
//
Car::Car(Input_inf _input)
{
	plate = _input.getPlate();
	arriveTime = _input.getTime();
	// default
	parkedTime = -1;
	parked = false;
}

// default constriant
Car::Car()
{
	plate = "";
	arriveTime = -1;
	parkedTime = -1;
	parked = false;
}

//
Car Car::parkedSuccess(int _parkTime)
{
	parkedTime = _parkTime;
	parked = true;
	return *this;
}

//
int Car::parkDuration(int _leftTime)
{
	// if the car had in parking lot 
	if (isParkedSuccess()) 
	{
		return _leftTime - parkedTime;
	}
	else
	{
		cout << "This car didn't park!" << endl;
		return -1;
	}
}

//
//
//

// constructor
Parkinglot::Parkinglot(int _size, float _charge)
{
	maxSize = _size;
	perMuch = _charge;
	currTime = 0;
	parkLot = new AStack<Car>(_size);
	tempLot = new AStack<Car>(_size);
	queuing = new LQueue<Car>;

	// print the parkinglosts information
	cout << "Welcome to ParkingLot!" << endl
		<< "Here a total of " << _size << " empty place." << endl
		<< "Cost " << _charge << " per duration." << endl << endl;
}

// open a business
void Parkinglot::openBusiness()
{
	// get the first input information
	Input_inf inputInf = input();

	// input.statu = 'E', means quit the system
	while (inputInf.getStatu() != 'E')
	{
		// handle base on input.statu
		switch (inputInf.getStatu())
		{
		case 'A':
			settleArrive(inputInf);
			break;
		case 'D':
			settleLeft(inputInf);
			break;
		default:
			break;
		}

		// continue to input
		inputInf = input();
	}

	// shot down a business
	cout << endl << "Close down!" << endl;
}

// input information
Input_inf Parkinglot::input()
{
	string inputStr;
	//cin >> inputStr;
	cout << "Please input: ";
	getline(cin, inputStr);
	
	Input_inf handledInf = handleInput(inputStr);

	while (!handledInf.isValid() || handledInf.getTime() < currTime)
	{
		// make sure input is valid
		if (!handledInf.isValid())
		{
			// input is invalid
			cout << "The information your input is invalid!" 
				<< endl << endl
				<< "Please input again as requeted: ";
		}
		// make sure the time is new
		if (handledInf.getTime() < currTime && handledInf.getStatu() != 'E') 
		{
			cout << "The time you input is not right!" 
				<< endl << endl
				<< "Please input the newest car: ";
		}
		// input again!
		getline(cin, inputStr);
		// handle again!
		handledInf = handleInput(inputStr);
	}

	// update the newest time
	currTime = handledInf.getTime();

	return handledInf;
}

// arrange car's arrive
void Parkinglot::settleArrive(Input_inf _inf)
{
	// it's a new car
	Car car(_inf);

	// first get parkinglot inf, judge whether has empty place
	// if has empty place
	if (parkLot->length() < maxSize)
	{
		car.parkedSuccess(_inf.getTime());    // mark this car has parked success
		parkLot->push(car);                   // push the car to parkLot
		cout << endl
			<< "    *************************************" << endl
			<< "    * Parked success!" << endl
			<< "    * " << car.getPlate() << " at parking space No." << parkLot->length() << endl
			<< "    *************************************" << endl
			<< endl;
	}
	// if there has no empty place
	else
	{
		queuing->enqueue(car);
		cout << endl
			<< "    *************************************" << endl
			<< "    * No more park space, queuing." << endl
			<< "    * " << car.getPlate() << " at queuing space No." << queuing->length() << endl
			<< "    *************************************" << endl
			<< endl;
	}

	// print current parkinglot's condition
	printParkinglot();
}

// arrange car's left
void Parkinglot::settleLeft(Input_inf _inf)
{
	// it's a new car
	Car car(_inf);
	bool flag = false;     // mark whether has this car
	int duringTime;        // record the duration of the car in parkinglot

	// find the car, will be left
	while (parkLot->length() > 0 && flag == false)
	{
		Car temp = parkLot->pop();
		// if find this car
		if (temp.getPlate() == car.getPlate())
		{
			flag = true;     // mark the car has got away success
			duringTime = temp.parkDuration(_inf.getTime());  // record the duration
		}
		else
		{
			tempLot->push(temp);
		}
	}

	// move templot's car to parkinglot
	while (tempLot->length() > 0)
	{
		// pop from tempLot, and push to parkLot
		parkLot->push(tempLot->pop());
	}

	// if get away success
	if (flag == true)
	{
		float totalCost = duringTime * perMuch;
		cout << endl
			<< "    ************************************" << endl
			<< "    * " << car.getPlate() << " leave success!" << endl
			<< "    * Total charge: " << totalCost << endl
			<< "    *************************************" << endl
			<< endl;
	}
	// if don't exsit this car
	else
	{
		cout << endl
			<< "    There doesn't have this car in parking space!" << endl
			<< endl;
	}

	// if there have empty place now
	if (parkLot->length() < maxSize)
	{
		// make sure, there has car in queuing
		if (queuing->length() > 0)
		{
			// dequeue the car in the queuing
			Car temp = queuing->dequeue();
			temp.parkedSuccess(_inf.getTime());    // record successful parked time
			// push the car to parkinglot
			parkLot->push(temp);
			// print statu
			cout << endl
				<< "    ************************************" << endl
				<< "    * " << temp.getPlate() << " Parked success!" << endl
				<< "    * Parking at space No." << parkLot->length() << endl
				<< "    *************************************" << endl
				<< endl;
		}
	}

	// print current parkinglot's condition
	printParkinglot();
}

// print parking information
void Parkinglot::printParkinglot()
{
	cout << endl
		<< "    -------------------------------------" << endl
		<< "    | There are " << maxSize - parkLot->length() << " empty place." << endl
		<< "    -------------------------------------" << endl
		<< "    | There are " << queuing->length() << " car be in queuing." << endl
		<< "    -------------------------------------" << endl
		<< endl;
}