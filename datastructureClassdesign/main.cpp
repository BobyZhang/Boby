
#include "parkinglot.h"

int main()
{
	string b = "£¨¡®A¡¯£¬ºÍ 1f24   , 999999)";

	Input_inf a = handleInput(b);

	if (a.isValid())
	{
		cout << a.getStatu() << endl
			<< a.getPlate() << endl
			<< a.getTime() << endl;
	}
	else
	{
		cout << "Input is invalid";
	}
	return 0;
}