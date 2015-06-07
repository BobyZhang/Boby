
#include <algorithm>
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
		if (_s[i] <= 0 || _s[i] >= 255)
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