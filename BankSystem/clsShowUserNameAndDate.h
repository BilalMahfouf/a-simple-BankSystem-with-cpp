#pragma once
#include<iostream>
#include"Global.h"
#include"clsDate.h"
#include"iomanip"
class clsShowUserNameAndDate
{
public:
	static void ShowUserNameAndCurrentDate()
	{
		cout << "\t\t\t\t\t\t"  << "User: " << CurrentUser.UserName << endl;
		clsDate CurrentDate;
		cout << "\t\t\t\t\t\tDate: "; 
		CurrentDate.Print();
		cout << "\n";
	}
};

