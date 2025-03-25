#pragma once

#include <iostream>
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


class clsDeleteClientScreen :protected clsScreen
{
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
    static void DeleteClient()
    {
        if (!CheckAccessRights(clsBankUsers::pDeleteClient))
        {
            return;
        }


        string AccountNumber = "";
        string Title = "\t  Delete Client Screen";
        clsScreen::_DrawScreenHeader(Title);

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client1);

        cout << "\nAre you sure you want to delete this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {


            if (Client1.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";

                _PrintClientCard(Client1);

            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }
        }
    }

};



