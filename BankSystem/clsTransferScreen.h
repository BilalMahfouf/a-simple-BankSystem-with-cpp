#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include"clsTransferLogScreen.h"


class clsTransferScreen :protected clsScreen
{
private:
	static void _PrintClientCard(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << client.FullName();
		cout << "\nAcc. Number : " << client.AccountNumber();
		cout << "\nBalance     : " << client.AccountBalance;
		cout << "\n___________________\n";

	}
public:
	static void ShowTransferScreen()
	{

		clsScreen::_DrawScreenHeader("\t  Transfer Screen");
		string AccountNumber = "";
		cout << "Please Enter Account Number To Transfer From ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Don't Exist,Enter  An Other One ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClientCard(Client);

		string AccountNumber1 = "";
		cout << "Please Enter Account Number To Transfer To ";
		AccountNumber1 = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber1))
		{
			cout << "\nAccount Number Don't Exist,Enter  An Other One ";
			AccountNumber1 = clsInputValidate::ReadString();
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber1);
		_PrintClientCard(Client1);

		cout << "\nEnter How Much Money You Want To Transfer ";
		double Amount = clsInputValidate::ReadDblNumberBetween(0, Client.AccountBalance,
			"Amount Exceeds the available balance,Please enter an other amount");
		cout << "\nAre you sure you want to transfer this amount y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			if (Client.Transfer(Amount, Client1))
			{
				

				cout << "\t transfer  successfully";
				_PrintClientCard(Client);
				_PrintClientCard(Client1);
			}
			else
			{
				cout << "\n Transfer Failed";
			}

		}


	}

};

