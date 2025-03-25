#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"


class clsWithdrawScreen :protected clsScreen
{
private:
	static void _PrintClientCard(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << client.FirstName;
		cout << "\nLastName    : " << client.LastName;
		cout << "\nFull Name   : " << client.FullName();
		cout << "\nEmail       : " << client.Email;
		cout << "\nPhone       : " << client.Phone;
		cout << "\nAcc. Number : " << client.AccountNumber();
		cout << "\nPassword    : " << client.PinCode;
		cout << "\nBalance     : " << client.AccountBalance;
		cout << "\n___________________\n";

	}
public:
	static void ShowWithdrawScreen()
	{

		clsScreen::_DrawScreenHeader("\t  Withdraw Screen");
		string AccountNumber = "";
		cout << "Please Enter Account Number ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Don't Exist,Enter  An Other One ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClientCard(Client);

		cout << "\nEnter How Much Money You Want To Withdraw ";
		double Amount = clsInputValidate::ReadDblNumber();

		
		cout << "\nAre you sure you want to withdraw this amount y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (Client.Withdraw(Amount))
			{
				cout << "\nWithdraw successfully";
				cout << "\nYour Balance Is: " << Client.AccountBalance << "($)";
			}
			else
			{
				cout << "\nWithdraw Faild";
			}
			
			
		}


	}

};

